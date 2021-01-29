# Level 0

## Vulnerability



## Context

We find a binary with owner ```level01``` and SUID.
```
level00@OverRide:~$ ls -l
-rwsr-s---+ 1 level01 users 7280 Sep 10  2016 level00
```

When run it prompts user for password, then exits given invalid password.
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



### Build exploit



## Recreate Exploited Binary


