# OverRide

Explore disassembly, binary exploitation & reverse-engineering through 10 little challenges.

In the folder for each level you will find:

* *flag* - password for next level

* *README.md* - how to find password

* *source.c* - the reverse engineered binary

* *dissasembly_notes.md* - notes on asm 

See the [subject](https://github.com/anyashuka/Override/blob/main/subject.pdf) for more details.


#### Final Score 125/100


## Getting Started

First download from 42 [*OverRide.iso*](https://projects.intra.42.fr/uploads/document/document/2096/OverRide.iso).

### Virtual Machine setup

On Mac OSX, install [VirtualBox](https://www.virtualbox.org/).

In VirtualBox create a new VM (click new).

* Name and operating system - Type: Linux, Version: (Oracle 64-bit)

Continue through all the next steps with the default settings:

* Memory size: 4MB
* Hard disk: Create a disk now
* Hard disk file type: VDI(VirtualBox Disk Image)
* Storage on physical hard disk: Dynamically allocated
* File size: 12,00GB

Next click Settings > Network > Adapter 1 > Attached to: Bridged Adapter.

Still in settings click Storage > Right of "Controller: IDE" there is a CD icon with a + sign (add optical drive).
Click Add Disk Image, and select *OverRide.iso*.

Click Start to start the VM, once runnning it should show the VM IP address and prompt user to login.

### SSH connect

Log in from a separate shell as user *level00* with password *level00*.

```ssh level00@{VM_IP} -p 4242```

<img src="https://github.com/anyashuka/Override/blob/main/img/ssh.png" width="800">

### Level Up

As user *level00* the goal is to read the password for user *level01*, found at */home/users/level01/.pass*. However, user *level00* does not have permissions to read this file.

In the home folder for user *level00* is a binary *level00* with SUID set and owner *level01*.

<img src="https://github.com/anyashuka/Override/blob/main/img/suid.png" width="400">

This means when we execute the binary *level00*, we do so with the permissions of user *level01*.

We must find a vulnerability in the binary *level00* with gdb. Then exploit the vulnerability to run *system("/bin/sh")*, opening a shell as user *level01* where we have permissions to read the password.

```cat /home/users/level01/.pass```

Then log in as user *level01*.

```su level01```

<img src="https://github.com/anyashuka/Override/blob/main/img/su.png" width="330">

Repeat for each level.


## Reverse-engineered binary

For each level, we reverse engineered the original *source.c* by examining the gdb disassembly of the binary.


## Levels Overview

* [0](https://github.com/anyashuka/Override/tree/main/level00) - Hardcoded password

* [1](https://github.com/anyashuka/Override/tree/main/level01) - Ret2Libc attack

* [2](https://github.com/anyashuka/Override/tree/main/level02) - printf() format string attack

* [3](https://github.com/anyashuka/Override/tree/main/level03) - Brute force password

* [4](https://github.com/anyashuka/Override/tree/main/level04) - gets() stack overflow + Return-to-libc attack

* [5](https://github.com/anyashuka/Override/tree/main/level05) - Shellcode in env variable + printf() format string attack

* [6](https://github.com/anyashuka/Override/tree/main/level06) - Hash value discoverable with gdb

* [7](https://github.com/anyashuka/Override/tree/main/level07) - Ret2Libc Attack on unprotected data table

* [8](https://github.com/anyashuka/Override/tree/main/level08) - Binary backs up password via symlink

* [9](https://github.com/anyashuka/Override/tree/main/level09) - Off-by-one error

## Team

I wrote this project in a team with the awesome [@dfinnis](https://github.com/dfinnis).
