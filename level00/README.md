# Level 0

## Vulnerability

Hardcoded password, discoverable with gdb

## Context

Let's start by logging in from a separate shell.
```
>$ ssh level00@{VM_IP} -p 4242
...
level00@192.168.0.21's password: level00
```

We find a binary with owner ```level01``` and SUID.
```
level00@OverRide:~$ ls -l
-rwsr-s---+ 1 level01 users 7280 Sep 10  2016 level00
```

When run it prompts user for password, then exits if given invalid password.
```
level00@OverRide:~$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password: Please!

Invalid Password!
level00@OverRide:~$
```

## Solution

Investigating with ```gdb``` we find no other functions apart from ```main()```. ```main()``` calls ```scanf()``` to read the password from stdin, then compares given password with value ```0x149c``` (5276 in decimal). If given password = 5276, a call to ```system()``` opens a shell. See [disassembly notes](https://github.com/anyashuka/Override/blob/main/level00/disassembly_notes.md) for detailed gdb assembly breakdown.

Using password 5276:
```
level00@OverRide:~$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ whoami
level01
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```

Exit the shell and log in to level01.
```
$ exit
level00@OverRide:~$ su level01
Password: uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```
