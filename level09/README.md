# Level 9

## Vulnerability



## Context

We find a binary with owner ```end``` and SUID.
```
level09@OverRide:~$ ls -l
-rwsr-s---+ 1 end users 12959 Oct  2  2016 level09
```

When run it prompts user for a username, and a message which is then sent to *Unix-Dude*.
```
level09@OverRide:~$ ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: Drew
>: Welcome, Drew
>: Msg @Unix-Dude
>>: Dear Unix-Dude, lots of love, Drew
>: Msg sent!
level09@OverRide:~$
```

## Solution



### Build exploit



## Recreate Exploited Binary


