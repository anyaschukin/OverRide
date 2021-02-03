# Level 8

## Vulnerability



## Context

We find a binary ```level08``` and a directory ```backups``` containing ```.log```, all with owner ```level09``` and SUID.
```
level08@OverRide:~$ ls -l
...
drwxrwx---+ 1 level09 users    60 Oct 19  2016 backups
-rwsr-s---+ 1 level09 users 12975 Oct 19  2016 level08
level08@OverRide:~$ ls -la backups/
...
-rwxrwx---+ 1 level09 users     0 Oct 19  2016 .log
```

When run without arguments its prints ```Usage: ./level08 filename```. When run with a file as argument it prints ```ERROR: Failed to open``` and exits.
```
level08@OverRide:~$ ./level08
Usage: ./level08 filename
ERROR: Failed to open (null)
level08@OverRide:~$ ./level08 backups/.log
ERROR: Failed to open ./backups/backups/.log
level08@OverRide:~$
```

## Solution



### Build exploit



## Recreate Exploited Binary


