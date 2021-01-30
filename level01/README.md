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


Using our trusty [pattern generator + EIP offset tool](https://projects.jason-rush.com/tools/buffer-overflow-eip-offset-string-generator/), we crash the program and find we can overwrite the EIP at offset 80.
```
(gdb) r
Starting program: /home/users/level01/level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
```


### Build exploit



## Recreate Exploited Binary


