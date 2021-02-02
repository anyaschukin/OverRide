# Level 6

## Vulnerability



## Context

We find a binary with owner ```level07``` and SUID.
```
level06@OverRide:~$ ls -l
-rwsr-s---+ 1 level07 users 7907 Sep 10  2016 level06
```

When run it prompts user for *Login* and *Serial*, reading from stdin. It then exits.
```
-rwsr-s---+ 1 level07 users 7907 Sep 10  2016 level06
level06@OverRide:~$ ./level06
***********************************
*		level06		  *
***********************************
-> Enter Login: Me!
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: Cornflakes!
level06@OverRide:~$
```

## Solution

### main() overview

First ```main()``` prompts user for *Login* and *Serial*, reading from stdin.

Next ```main()``` calls ```auth()``` which performs a hashing algorithm on *Login*, then compares the computed hash with *Serial*.

Finally, if ```auth()``` validates the *Login* and *Serial*, ```system()``` opens a shell.

See [disassembly notes](https://github.com/anyashuka/Override/blob/main/level06/Ressources/disassembly_notes.md) for detailed gdb assembly breakdown.

### Find Serial with gdb

Using gdb we can look for the computed hash value (*Serial*) for a given *Login*.

However, we can't go directly to the computed hash because ptrace() detects tampering. First we have to put in a break point and modify it's return to 0 to pass.

Then we can proceed to a second break point when the computed hash is compared with the *Serial*, here we can print the value of the computed hash. Let's try to find the *Serial* for *Login* ```username```.
```
level06@OverRide:~$ gdb -q level06
...
(gdb) break *0x080487ba                           // ptrace() return
Breakpoint 1 at 0x80487ba
(gdb) break *0x08048866                           // compare hash and serial
Breakpoint 2 at 0x8048866
(gdb) run
Starting program: /home/users/level06/level06
***********************************
*		level06		  *
***********************************
-> Enter Login: username                          // username (could be any printable string > 5 bytes long)
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 42                               // whatever

Breakpoint 1, 0x080487ba in auth ()
(gdb) set $eax=0                                  // override detect tampering
(gdb) c
Continuing.

Breakpoint 2, 0x08048866 in auth ()
(gdb) x/d $ebp-0x10                               // print hash in decimal
0xffffd658:	6234463                               // 6234463
```

### Input Serial & Login

So lets try the *Serial* ```6234463``` with *Login* ```username```.
```
level06@OverRide:~$ ./level06
***********************************
*		level06		  *
***********************************
-> Enter Login: username
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6234463
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```

## Recreate Exploited Binary


