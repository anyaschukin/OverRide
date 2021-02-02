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

### Build exploit



## Recreate Exploited Binary


