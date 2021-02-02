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



### Build exploit



## Recreate Exploited Binary


