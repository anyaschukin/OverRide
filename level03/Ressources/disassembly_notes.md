# Disassembly

```
(gdb) disas main
Dump of assembler code for function main:

   0x0804885a <+0>:	push   %ebp
   0x0804885b <+1>:	mov    %esp,%ebp
   
   0x0804885d <+3>:	and    $0xfffffff0,%esp                ; align the stack 
   0x08048860 <+6>:	sub    $0x20,%esp
   0x08048863 <+9>:	push   %eax
   0x08048864 <+10>:	xor    %eax,%eax                                ; sets eax to zero 
   0x08048866 <+12>:	je     0x804886b <main+17>
   0x08048868 <+14>:	add    $0x4,%esp                                ; 4 bytes... size of an int?
   0x0804886b <+17>:	pop    %eax
   
   0x0804886c <+18>:	movl   $0x0,(%esp)
   0x08048873 <+25>:	call   0x80484b0 <time@plt>
   
   0x08048878 <+30>:	mov    %eax,(%esp)
   0x0804887b <+33>:	call   0x8048500 <srand@plt>
   0x08048880 <+38>:	movl   $0x8048a48,(%esp)
   0x08048887 <+45>:	call   0x80484d0 <puts@plt>
   0x0804888c <+50>:	movl   $0x8048a6c,(%esp)
   0x08048893 <+57>:	call   0x80484d0 <puts@plt>
   0x08048898 <+62>:	movl   $0x8048a48,(%esp)
   0x0804889f <+69>:	call   0x80484d0 <puts@plt>
   
   0x080488a4 <+74>:	mov    $0x8048a7b,%eax
   0x080488a9 <+79>:	mov    %eax,(%esp)
   0x080488ac <+82>:	call   0x8048480 <printf@plt>
   
   0x080488b1 <+87>:	mov    $0x8048a85,%eax                          ; %d
   0x080488b6 <+92>:	lea    0x1c(%esp),%edx                          ; input
   0x080488ba <+96>:	mov    %edx,0x4(%esp)                           ; set argument 2, esp+4: input
   0x080488be <+100>:	mov    %eax,(%esp)                           ; set argument 1, esp: %d
   0x080488c1 <+103>:	call   0x8048530 <__isoc99_scanf@plt>
   
   0x080488c6 <+108>:	mov    0x1c(%esp),%eax                       ; return of scanf: input
   0x080488ca <+112>:	movl   $0x1337d00d,0x4(%esp)                 ; set argument 2, esp+4: value 322424845
   0x080488d2 <+120>:	mov    %eax,(%esp)                           ; set argument 1, esp: unput
   0x080488d5 <+123>:	call   0x8048747 <test>                      ; test(number, 322424845);
   0x080488da <+128>:	mov    $0x0,%eax
   
   0x080488df <+133>:	leave
   0x080488e0 <+134>:	ret
```
