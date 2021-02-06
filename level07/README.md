# Level 7

## Vulnerability



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

Protects Against:
- arguments to the program
- environment variables
The program erases arguments to it and environment variables, which means we can't pass a shellcode as argument or store one in an environment variable. 

Vulnerability: no check performed on the index and unsigned int table is stored on the stack. This means we can read or store in stack memory. 

- program creates a table, in which it stores values at indexes
- some indexes (index % 3 == 0) are protected
- going to overwrite EIP at table index, for ret2libc

1) find table index of EIP (answer is 114)
2) index 114 is protected. Need to use maxint overflow to access
3) find the address of bin/sh
4) exploit by inputting malicious number + index to running program




### Build exploit



## Recreate Exploited Binary


