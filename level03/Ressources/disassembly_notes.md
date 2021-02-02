# Disassembly

```
(gdb) disas main
Dump of assembler code for function main:

   0x0804885a <+0>:	push   %ebp
   0x0804885b <+1>:	mov    %esp,%ebp
   
   0x0804885d <+3>:	and    $0xfffffff0,%esp                         ; align the stack on 16 bytes
   0x08048860 <+6>:	sub    $0x20,%esp                               ; allocates 32 bytes on stack for local variables
   0x08048863 <+9>:	push   %eax
   0x08048864 <+10>:	xor    %eax,%eax                                ; sets eax to zero (the most efficient way)
   0x08048866 <+12>:	je     0x804886b <main+17>
   0x08048868 <+14>:	add    $0x4,%esp                                ; 4 bytes... size of an int?
   0x0804886b <+17>:	pop    %eax
   
   0x0804886c <+18>:	movl   $0x0,(%esp)                              ; load value of 0
   0x08048873 <+25>:	call   0x80484b0 <time@plt>                     ; time(0)
   
   0x08048878 <+30>:	mov    %eax,(%esp)
   0x0804887b <+33>:	call   0x8048500 <srand@plt>                    ; srand(time(0))
   
   0x08048880 <+38>:	movl   $0x8048a48,(%esp)
   0x08048887 <+45>:	call   0x80484d0 <puts@plt>                     ; puts("***********************************");
   0x0804888c <+50>:	movl   $0x8048a6c,(%esp)
   0x08048893 <+57>:	call   0x80484d0 <puts@plt>                     ; puts("*\t\tlevel03\t\t**");
   0x08048898 <+62>:	movl   $0x8048a48,(%esp)
   0x0804889f <+69>:	call   0x80484d0 <puts@plt>                     ; puts("***********************************");
   0x080488a4 <+74>:	mov    $0x8048a7b,%eax
   0x080488a9 <+79>:	mov    %eax,(%esp)                              ; set argument 1, esp: "Password:"
   0x080488ac <+82>:	call   0x8048480 <printf@plt>                   ; printf("Password:");
   
   0x080488b1 <+87>:	mov    $0x8048a85,%eax                          ; %d
   0x080488b6 <+92>:	lea    0x1c(%esp),%edx                          ; input
   0x080488ba <+96>:	mov    %edx,0x4(%esp)                           ; set argument 2, esp+4: input
   0x080488be <+100>:	mov    %eax,(%esp)                              ; set argument 1, esp: %d
   0x080488c1 <+103>:	call   0x8048530 <__isoc99_scanf@plt>
   
   0x080488c6 <+108>:	mov    0x1c(%esp),%eax                          ; return of scanf: input
   0x080488ca <+112>:	movl   $0x1337d00d,0x4(%esp)                    ; set argument 2, esp+4: value 322424845
   0x080488d2 <+120>:	mov    %eax,(%esp)                              ; set argument 1, esp: input
   0x080488d5 <+123>:	call   0x8048747 <test>                         ; test(number, 322424845);
   0x080488da <+128>:	mov    $0x0,%eax
   
   0x080488df <+133>:	leave
   0x080488e0 <+134>:	ret
```

```
(gdb) disas test
Dump of assembler code for function test:
   0x08048747 <+0>:	push   %ebp
   0x08048748 <+1>:	mov    %esp,%ebp
   0x0804874a <+3>:	sub    $0x28,%esp                                  ; allocates 40 bytes on stack for local variables
   
   0x0804874d <+6>:	mov    0x8(%ebp),%eax                              ; ebp+8, DWORD PTR
   0x08048750 <+9>:	mov    0xc(%ebp),%edx                              ; ebp+0xc, DWORD PTR
   0x08048753 <+12>:	mov    %edx,%ecx
   0x08048755 <+14>:	sub    %eax,%ecx                                   ; 322424845 - input
   0x08048757 <+16>:	mov    %ecx,%eax
   0x08048759 <+18>:	mov    %eax,-0xc(%ebp)
   0x0804875c <+21>:	cmpl   $0x15,-0xc(%ebp)                            ; if number > 21
   0x08048760 <+25>:	ja     0x804884a <test+259>                        ; jump if above
   
   0x08048766 <+31>:	mov    -0xc(%ebp),%eax
   0x08048769 <+34>:	shl    $0x2,%eax                                   ; shift
   0x0804876c <+37>:	add    $0x80489f0,%eax
   0x08048771 <+42>:	mov    (%eax),%eax
   0x08048773 <+44>:	jmp    *%eax
   0x08048775 <+46>:	mov    -0xc(%ebp),%eax
   0x08048778 <+49>:	mov    %eax,(%esp)
   0x0804877b <+52>:	call   0x8048660 <decrypt>
   0x08048780 <+57>:	jmp    0x8048858 <test+273>
   0x08048785 <+62>:	mov    -0xc(%ebp),%eax
   0x08048788 <+65>:	mov    %eax,(%esp)
   0x0804878b <+68>:	call   0x8048660 <decrypt>
   0x08048790 <+73>:	jmp    0x8048858 <test+273>
[...]
   0x0804884a <+259>:	call   0x8048520 <rand@plt>                     ; number = rand()
   0x0804884f <+264>:	mov    %eax,(%esp)
   0x08048852 <+267>:	call   0x8048660 <decrypt>
   
   0x08048857 <+272>:	nop
   0x08048858 <+273>:	leave
   0x08048859 <+274>:	ret
```
