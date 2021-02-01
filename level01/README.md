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
See [dissasembly notes](https://github.com/anyashuka/Override/blob/main/level01/Ressources/disassembly_notes.md) for detailed gdb assembly breakdown.

First ```main()``` prompts for a username, reading from stdin with ```fgets()```, and then calls ```verify_user_name()```.

Then ```main()``` prompts for a password, reading from stdin with ```fgets()```, and then calls ```verify_user_pass()```.

In both cases, user input for username and password is compared with a hard value in memory and jumps to exit if not equal. 

In ```verify_user_name()```, we see that the username must be "dat_wil".

In ```verify_user_pass()```, we see that the password must be "admin".

However, when we try these values the program still quits. 
```
level01@OverRide:~$ ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
admin
nope, incorrect password...

```


Using our trusty [pattern generator and EIP offset tool](https://projects.jason-rush.com/tools/buffer-overflow-eip-offset-string-generator/), we crash the program and find we can overwrite the EIP at offset 80.

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


So finally our attack payload will be : “padding –> address of system() –> address of exit() –> /bin/sh“


### Build exploit



## Recreate Exploited Binary


