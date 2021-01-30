# Level 2

## Vulnerability

printf() format string attack, read password on stack

## Context

We find a binary with owner ```level03``` and SUID.
```
level02@OverRide:~$ ls -l
-rwsr-s---+ 1 level03 users 9452 Sep 10  2016 level02
```

When run it prompts user to log in with username and password. It exits if given incorrect password.
```
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: me!
--[ Password: mine!
*****************************************
me! does not have access!
```

## Solution

### main() overview

Investigating with gdb we find no other functions apart from ```main()```.

First ```main()``` reads the correct password for user ```level03```, from the ```/home/users/level03/.pass``` file, into a variable on the stack.

Then ```main()``` prompts user for username and password, reading from stdin.

Finally ```strncmp()``` compares the password input by user with the correct password. If the password is correct ```system("/bin/sh")``` opens a shell.

See [disassembly notes](https://github.com/anyashuka/Override/blob/main/level02/Ressources/disassembly_notes.md) for detailed gdb assembly breakdown.

### Exploit

The key vulnerability is the username provided is then printed with ```printf()```. So we can use the format string attack to print what is on the stack, where the password is stored.


## Recreate Exploited Binary


