# Level 3

## Vulnerability



## Context

We find a binary with owner ```level03``` and SUID.
```
level03@OverRide:~$ ls -l
-rwsr-s---+ 1 level04 users 7677 Sep 10  2016 level03
```

When run, it prompts for a password and then immediately quits. 
```
level03@OverRide:~$ ./level03
***********************************
*		level03		**
***********************************
Password:hello

Invalid Password
```

## Solution

### main() overview

Let's take a deeper look at the program. See [dissasembly notes](https://github.com/anyashuka/Override/blob/main/level03/Ressources/disassembly_notes.md) for detailed gdb assembly breakdown.

Main() prompts for a password with ```printf()``` and reads from the stdin with ```scanf()```.

It then calls a function ```test()```, with the user input and the number 322424845. 
```test()``` then makes the following calculation: ```322424845 - user input```. 
```test()``` then calls decrypt: with the result if it's less than 21, else with a random number. 

The function ```decrypt()``` then passes a crypt over the parameter. 
If the initial user inputted password is correct, ```decrypt()``` prints "Congratulations!" and calls ```system("/bin/sh")```.

### Build exploit



## Recreate Exploited Binary


