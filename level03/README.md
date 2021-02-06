# Level 3

## Vulnerability



## Context

We find a binary with owner ```level04``` and SUID.
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

If the initial user-inputted password is correct, ```decrypt()``` prints "Congratulations!" and calls ```system("/bin/sh")```.

### Build exploit

The calculation in ```test()```
```
322424845 - user input
if result < 21
``` 
... indicates that there are 21 potential passwords. Let's try them out!

Let's construct our payload.
```
322424845 - 21 = 322424824
for i in range {322424824..322424845}; do (echo $i; cat -) | ./level03 ; done
```
And test!
```
level03@OverRide:~$ for i in range {322424824..322424845}; do (echo $i; cat -) | ./level03 ; echo "Trying $((i+1))..."; done
[... press 'enter' until you can type 'whoami' ...]
Trying 322424827...
***********************************
*		level03		**
***********************************
whoami
level04
cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```
