# Level 7

## Vulnerability



## Context

We find a binary with owner ```level0X!!!``` and SUID.
```

```

When run ...!!!!!
```

```

## Solution

- program creates a table, in which it stores values at indexes
- some indexes (index % 3 == 0) are protected
- going to overwrite EIP at table index, for ret2libc

1) find table index of EIP (answer is 114)
2) index 114 is protected. Need to use maxint overflow to access
3) find the address of bin/sh
4) exploit by inputting malicious number + index to running program




### Build exploit



## Recreate Exploited Binary


