# Level 6 - Disassembly Notes

```
(gdb) disas main
Dump of assembler code for function main:
   0x08048879 <+0>:	push   %ebp
   0x0804887a <+1>:	mov    %esp,%ebp
   0x0804887c <+3>:	and    $0xfffffff0,%esp


#### Initialize local variables ####

   0x0804887f <+6>:	sub    $0x50,%esp                       ; allocate 80 bytes on stack for local variables

   0x08048882 <+9>:	mov    0xc(%ebp),%eax                   ; argv[0]
   0x08048885 <+12>:	mov    %eax,0x1c(%esp)                  ; store argv[0] at esp+0x1c

   0x08048889 <+16>:	mov    %gs:0x14,%eax                    ; 20
   0x0804888f <+22>:	mov    %eax,0x4c(%esp)                  ; int var1 = 20

   0x08048893 <+26>:	xor    %eax,%eax
   0x08048895 <+28>:	push   %eax
   0x08048896 <+29>:	xor    %eax,%eax
   0x08048898 <+31>:	je     0x804889d <main+36>
   0x0804889a <+33>:	add    $0x4,%esp
   0x0804889d <+36>:	pop    %eax


#### Print Login prompt ####

   0x0804889e <+37>:	movl   $0x8048ad4,(%esp)                ; '*' <repeats 35 times>
   0x080488a5 <+44>:	call   0x8048590 <puts@plt>             ; puts("***********************************");
   0x080488aa <+49>:	movl   $0x8048af8,(%esp)                ; "*\t\tlevel06\t\t  *"
   0x080488b1 <+56>:	call   0x8048590 <puts@plt>             ; puts("*\t\tlevel06\t\t  *");
   0x080488b6 <+61>:	movl   $0x8048ad4,(%esp)                ; '*' <repeats 35 times>
   0x080488bd <+68>:	call   0x8048590 <puts@plt>             ; puts("***********************************");
   0x080488c2 <+73>:	mov    $0x8048b08,%eax                  ; "-> Enter Login: "
   0x080488c7 <+78>:	mov    %eax,(%esp)                      ; load arg - "-> Enter Login: "
   0x080488ca <+81>:	call   0x8048510 <printf@plt>           ; printf("-> Enter Login: ");


#### Read Login from stdin ####

   0x080488cf <+86>:	mov    0x804a060,%eax                   ; stdin
   0x080488d4 <+91>:	mov    %eax,0x8(%esp)                   ; load arg 3 - stdin
   0x080488d8 <+95>:	movl   $0x20,0x4(%esp)                  ; load arg 2 - 32
   0x080488e0 <+103>:	lea    0x2c(%esp),%eax                  ; char buffer[32];
   0x080488e4 <+107>:	mov    %eax,(%esp)                      ; load arg 1 - buffer[32]
   0x080488e7 <+110>:	call   0x8048550 <fgets@plt>            ; fgets(buffer, 32, stdin);


#### Print Serial prompt ####

   0x080488ec <+115>:	movl   $0x8048ad4,(%esp)                ; '*' <repeats 35 times>
   0x080488f3 <+122>:	call   0x8048590 <puts@plt>             ; puts("***********************************");
   0x080488f8 <+127>:	movl   $0x8048b1c,(%esp)                ; "***** NEW ACCOUNT DETECTED ********"
   0x080488ff <+134>:	call   0x8048590 <puts@plt>             ; puts("***** NEW ACCOUNT DETECTED ********");
   0x08048904 <+139>:	movl   $0x8048ad4,(%esp)                ; '*' <repeats 35 times>
   0x0804890b <+146>:	call   0x8048590 <puts@plt>             ; puts("***********************************");
   0x08048910 <+151>:	mov    $0x8048b40,%eax                  ; "-> Enter Serial: "
   0x08048915 <+156>:	mov    %eax,(%esp)                      ; load arg - "-> Enter Serial: "
   0x08048918 <+159>:	call   0x8048510 <printf@plt>           ; printf("-> Enter Serial: ");


#### Read Serial from stdin ####

   0x0804891d <+164>:	mov    $0x8048a60,%eax                  ; "%u"
   0x08048922 <+169>:	lea    0x28(%esp),%edx                  ; unsigned int serial
   0x08048926 <+173>:	mov    %edx,0x4(%esp)                   ; load arg 2 - serial
   0x0804892a <+177>:	mov    %eax,(%esp)                      ; load arg 1 - "%u"
   0x0804892d <+180>:	call   0x80485e0 <__isoc99_scanf@plt>   ; scanf("%u", &serial);


#### Validate password ####

   0x08048932 <+185>:	mov    0x28(%esp),%eax                  ; unsigned int serial
   0x08048936 <+189>:	mov    %eax,0x4(%esp)                   ; load arg 2 - serial
   0x0804893a <+193>:	lea    0x2c(%esp),%eax                  ; buffer[32]
   0x0804893e <+197>:	mov    %eax,(%esp)                      ; load arg 1 - buffer
   0x08048941 <+200>:	call   0x8048748 <auth>                 ; auth(buffer, serial)
   0x08048946 <+205>:	test   %eax,%eax                        ; password correct?
   0x08048948 <+207>:	jne    0x8048969 <main+240>             ; jump past system("/bin/sh")


#### Open shell ####

   0x0804894a <+209>:	movl   $0x8048b52,(%esp)                ; "Authenticated!"
   0x08048951 <+216>:	call   0x8048590 <puts@plt>             ; puts("Authenticated!");
   0x08048956 <+221>:	movl   $0x8048b61,(%esp)                ; "/bin/sh"
   0x0804895d <+228>:	call   0x80485a0 <system@plt>           ; system("/bin/sh");
   0x08048962 <+233>:	mov    $0x0,%eax                        ; load (0) for return(0)
   0x08048967 <+238>:	jmp    0x804896e <main+245>             ; jump to return(0)

   0x08048969 <+240>:	mov    $0x1,%eax                        ; load (1) for return(1)
   0x0804896e <+245>:	mov    0x4c(%esp),%edx
   0x08048972 <+249>:	xor    %gs:0x14,%edx                    ; var1
   0x08048979 <+256>:	je     0x8048980 <main+263>             ; jump to return
   0x0804897b <+258>:	call   0x8048580 <__stack_chk_fail@plt> ; kill function if stack overflow
   0x08048980 <+263>:	leave
   0x08048981 <+264>:	ret
```
