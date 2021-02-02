# Disassembly

Here's a deeper look into ```main()```.
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

Here's a deeper look into ```test()```.
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
   0x08048759 <+18>:	mov    %eax,-0xc(%ebp)                             ; number = 322424845 - input
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

Here's a deeper look into ```decrypt()```.
```
(gdb) disas decrypt
Dump of assembler code for function decrypt:

   0x08048660 <+0>:	push   %ebp
   0x08048661 <+1>:	mov    %esp,%ebp
   
   0x08048663 <+3>:	push   %edi
   0x08048664 <+4>:	push   %esi
   0x08048665 <+5>:	sub    $0x40,%esp                                  ; allocates 64 bytes on stack for local variables
   
   0x08048668 <+8>:	mov    %gs:0x14,%eax                               ; read 4 bytes into eax from memory at address gs:0x14
   0x0804866e <+14>:	mov    %eax,-0xc(%ebp)                             ; local variable esp-0xc
   0x08048671 <+17>:	xor    %eax,%eax                                   ; sets eax to zero (the most efficient way)
   
   0x08048673 <+19>:	movl   $0x757c7d51,-0x1d(%ebp)                     ; "Q}|u`sfg~sf{}|a"
   0x0804867a <+26>:	movl   $0x67667360,-0x19(%ebp)                     ; "`sfg~sf{}|a"
   0x08048681 <+33>:	movl   $0x7b66737e,-0x15(%ebp)                     ; "~sf{}|a"
   0x08048688 <+40>:	movl   $0x33617c7d,-0x11(%ebp)                     ;  "}|a"
   0x0804868f <+47>:	movb   $0x0,-0xd(%ebp)                             ; "\0"
   0x08048693 <+51>:	push   %eax
   
   0x08048694 <+52>:	xor    %eax,%eax                                   ; sets eax to zero
   0x08048696 <+54>:	je     0x804869b <decrypt+59>
   
   0x08048698 <+56>:	add    $0x4,%esp                                   ; add 4 empty bytes "" to esp ?
   0x0804869b <+59>:	pop    %eax
   0x0804869c <+60>:	lea    -0x1d(%ebp),%eax                            ; load "Q}|u`sfg~sf{}|a3" into eax
   0x0804869f <+63>:	movl   $0xffffffff,-0x2c(%ebp)                     ; alignment?
   0x080486a6 <+70>:	mov    %eax,%edx                                   ; load 0xffffffff into edx
   0x080486a8 <+72>:	mov    $0x0,%eax
   0x080486ad <+77>:	mov    -0x2c(%ebp),%ecx                            ; load 0xffffffff into ecx
   0x080486b0 <+80>:	mov    %edx,%edi                                   ; load "Q}|u`sfg~sf{}|a3" into edi
   0x080486b2 <+82>:	repnz scas %es:(%edi),%al                          ; strlen("Q}|u`sfg~sf{}|a3")
   0x080486b4 <+84>:	mov    %ecx,%eax
   0x080486b6 <+86>:	not    %eax
   0x080486b8 <+88>:	sub    $0x1,%eax
   0x080486bb <+91>:	mov    %eax,-0x24(%ebp)                            ; size_t len = strlen("Q}|u`sfg~sf{}|a3")
   0x080486be <+94>:	movl   $0x0,-0x28(%ebp)                            ; int i = 0
   0x080486c5 <+101>:	jmp    0x80486e5 <decrypt+133>
   
   0x080486c7 <+103>:	lea    -0x1d(%ebp),%eax                         ; "Q}|u`sfg~sf{}|a3"
   0x080486ca <+106>:	add    -0x28(%ebp),%eax                         ; 32 bytes? index?
   0x080486cd <+109>:	movzbl (%eax),%eax                              ; return string[index] ... return ("Q}|u`sfg~sf{}|a3"[index])
   0x080486d0 <+112>:	mov    %eax,%edx
   
   0x080486d2 <+114>:	mov    0x8(%ebp),%eax                           ; input?
   0x080486d5 <+117>:	xor    %edx,%eax
   0x080486d7 <+119>:	mov    %eax,%edx
   0x080486d9 <+121>:	lea    -0x1d(%ebp),%eax
   0x080486dc <+124>:	add    -0x28(%ebp),%eax
   0x080486df <+127>:	mov    %dl,(%eax)
   0x080486e1 <+129>:	addl   $0x1,-0x28(%ebp)
   0x080486e5 <+133>:	mov    -0x28(%ebp),%eax
   0x080486e8 <+136>:	cmp    -0x24(%ebp),%eax
   0x080486eb <+139>:	jb     0x80486c7 <decrypt+103>
   
   0x080486ed <+141>:	lea    -0x1d(%ebp),%eax                            ; buf
   0x080486f0 <+144>:	mov    %eax,%edx
   0x080486f2 <+146>:	mov    $0x80489c3,%eax                             ; "Congratulations!"
   0x080486f7 <+151>:	mov    $0x11,%ecx                                  ; value of 17
   0x080486fc <+156>:	mov    %edx,%esi
   0x080486fe <+158>:	mov    %eax,%edi
   0x08048700 <+160>:	repz cmpsb %es:(%edi),%ds:(%esi)                   ; strncmp - loops comparing values in ES:EDI and DS:ESI, continues until ECX is zero or a mismatching byte is found
   0x08048702 <+162>:	seta   %dl                                         ; sets DL if previous comparison results in >
   0x08048705 <+165>:	setb   %al                                         ; sets AL if previous comparison results in <
   0x08048708 <+168>:	mov    %edx,%ecx
   0x0804870a <+170>:	sub    %al,%cl
   0x0804870c <+172>:	mov    %ecx,%eax
   0x0804870e <+174>:	movsbl %al,%eax
   0x08048711 <+177>:	test   %eax,%eax                                   ; if (strncmp(buf, "Congratulations",17) == 0)
   0x08048713 <+179>:	jne    0x8048723 <decrypt+195>
   
   0x08048715 <+181>:	movl   $0x80489d4,(%esp)                           ; "/bin/sh"
   0x0804871c <+188>:	call   0x80484e0 <system@plt>                      ; system("/bin/sh")
   
   0x08048721 <+193>:	jmp    0x804872f <decrypt+207>
   
   0x08048723 <+195>:	movl   $0x80489dc,(%esp)
   0x0804872a <+202>:	call   0x80484d0 <puts@plt>                        ; puts("\nInvalid Password")
   
   0x0804872f <+207>:	mov    -0xc(%ebp),%esi
   0x08048732 <+210>:	xor    %gs:0x14,%esi
   0x08048739 <+217>:	je     0x8048740 <decrypt+224>
   0x0804873b <+219>:	call   0x80484c0 <__stack_chk_fail@plt>
   0x08048740 <+224>:	add    $0x40,%esp
   0x08048743 <+227>:	pop    %esi
   0x08048744 <+228>:	pop    %edi
   0x08048745 <+229>:	pop    %ebp
   0x08048746 <+230>:	ret
```
