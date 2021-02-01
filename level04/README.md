# Level 4

## Vulnerability



## Context

We find a binary with owner ```level05``` and SUID.
```
level04@OverRide:~$ ls -l
-rwsr-s---+ 1 level05 users 7797 Sep 10  2016 level04
```

When run it gives us a hint, then reads from stdin, then exits.
```
level04@OverRide:~$ ./level04
Give me some shellcode, k
[... user input from stdin ...]
child is exiting...
level04@OverRide:~$
```

## Solution



### Build exploit



## Recreate Exploited Binary


