# Override

Explore gdb disassembly and binary exploitation through 10 little challenges

For each level:

* ```flag``` password for next level

* ```README.md``` how to find password for each level

* ```source``` the reverse engineered binary

## Levels Overview

* Level 0 - Hardcoded password

* Level 1 - 

* Level 2 - printf() format string attack

* Level 3 - 

* Level 4 - gets() stack overflow + Return-to-libc attack

* Level 5 - 

* Level 6 - Hash value discoverable with gdb

* Level 7 - 

* Level 8 - Binary backs up password via symlink

* Level 9 - Off-by-one error

## Virtual Machine setup

On Mac OSX, install VirtualBox and create a VM

> New VM - Type : Linux - Version : (Oracle 64-bit)

> New VM > settings > Network > Adapter 1 > Attached to: Bridged Adapter

Mount the SnowCrash.iso to the VM:

> New VM > settings > Storage > Under IDE Controller there is a CD icon with a + sign on it...

> click on the CD then select OverRide.iso
