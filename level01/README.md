# Level 1

## Vulnerability



## Context

We find a binary with owner ```level01``` and SUID.
```
level01@OverRide:~$ ls -l
-rwsr-s---+ 1 level02 users 7360 Sep 10  2016 level01
```

When run, we see it prompts for a username (and probably later, a password).
```
level01@OverRide:~$ ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: POTUS
verifying username....

nope, incorrect username...
```

## Solution

Let's take a deeper look at the program. 
``
level01@OverRide:~$ gdb -q level01
(gdb) disas main
   0x0804852d <+93>:	call   0x8048464 <verify_user_name>
   0x08048580 <+176>:	call   0x80484a3 <verify_user_pass>
``

### Build exploit



## Recreate Exploited Binary


