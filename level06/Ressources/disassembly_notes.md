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

   0x08048889 <+16>:	mov    %gs:0x14,%eax                    ; canary value
   0x0804888f <+22>:	mov    %eax,0x4c(%esp)                  ; store canary value at end of stack

   0x08048893 <+26>:	xor    %eax,%eax                        ; canary value
   0x08048895 <+28>:	push   %eax                             ; save canary value
   0x08048896 <+29>:	xor    %eax,%eax                        ; canary value
   0x08048898 <+31>:	je     0x804889d <main+36>              ; jump past add 4 to esp
   0x0804889a <+33>:	add    $0x4,%esp                        ; add 4 to esp
   0x0804889d <+36>:	pop    %eax                             ; pop canary value


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


#### call auth() - Validate Serial ####

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


#### Return ####

   0x08048969 <+240>:	mov    $0x1,%eax                        ; load (1) for return(1)
   0x0804896e <+245>:	mov    0x4c(%esp),%edx                  ; stored canary value
   0x08048972 <+249>:	xor    %gs:0x14,%edx                    ; canary value correct?
   0x08048979 <+256>:	je     0x8048980 <main+263>             ; jump to return
   0x0804897b <+258>:	call   0x8048580 <__stack_chk_fail@plt> ; kill function if stack overflow
   0x08048980 <+263>:	leave
   0x08048981 <+264>:	ret
End of assembler dump.



#### ---- Auth() ----- ####

(gdb) disas auth
Dump of assembler code for function auth:
   0x08048748 <+0>:	push   %ebp
   0x08048749 <+1>:	mov    %esp,%ebp
   0x0804874b <+3>:	sub    $0x28,%esp                       ; allocate 40 bytes on stack for local variables


#### Null terminate login ####

   0x0804874e <+6>:	movl   $0x8048a63,0x4(%esp)             ; load arg 2 - "\n"
   0x08048756 <+14>:	mov    0x8(%ebp),%eax                   ; char *login
   0x08048759 <+17>:	mov    %eax,(%esp)                      ; load arg 1 - login
   0x0804875c <+20>:	call   0x8048520 <strcspn@plt>          ; strcspn(login, "\n")
   0x08048761 <+25>:	add    0x8(%ebp),%eax                   ; login
   0x08048764 <+28>:	movb   $0x0,(%eax)                      ; login[strcspn(login, "\n")] = 0;

#### len login ####

   0x08048767 <+31>:	movl   $0x20,0x4(%esp)                  ; load arg 2 - 32
   0x0804876f <+39>:	mov    0x8(%ebp),%eax                   ; login
   0x08048772 <+42>:	mov    %eax,(%esp)                      ; load arg 1 - login
   0x08048775 <+45>:	call   0x80485d0 <strnlen@plt>          ; strnlen(login, 32)
   0x0804877a <+50>:	mov    %eax,-0xc(%ebp)                  ; store strnlen() return

   0x0804877d <+53>:	push   %eax                             ; push strnlen() return
   0x0804877e <+54>:	xor    %eax,%eax                        ; xor strnlen() return
   0x08048780 <+56>:	je     0x8048785 <auth+61>              ; jump past add 4 to esp
   0x08048782 <+58>:	add    $0x4,%esp                        ; add 4 to esp
   0x08048785 <+61>:	pop    %eax                             ; pop strnlen() return


### Login > 5 bytes long ? ####

   0x08048786 <+62>:	cmpl   $0x5,-0xc(%ebp)                  ; login at least 5 bytes long?
   0x0804878a <+66>:	jg     0x8048796 <auth+78>              ; jump past return(1)

   0x0804878c <+68>:	mov    $0x1,%eax                        ; load (1) for return(1)
   0x08048791 <+73>:	jmp    0x8048877 <auth+303>             ; jump to return(1)


#### ptrace() detect tampering ####

   0x08048796 <+78>:	movl   $0x0,0xc(%esp)                   ; load arg 4 - 0
   0x0804879e <+86>:	movl   $0x1,0x8(%esp)                   ; load arg 3 - 1
   0x080487a6 <+94>:	movl   $0x0,0x4(%esp)                   ; load arg 2 - 0
   0x080487ae <+102>:	movl   $0x0,(%esp)                      ; load arg 1 - 0
   0x080487b5 <+109>:	call   0x80485f0 <ptrace@plt>           ; ptrace(0, 0, 1, 0)
   0x080487ba <+114>:	cmp    $0xffffffff,%eax                 ; ptrace() return -1 ?
   0x080487bd <+117>:	jne    0x80487ed <auth+165>             ; jump past "!! TAMPERING DETECTED !!"


#### Print TAMPERING DETECTED, return(1) ####

   0x080487bf <+119>:	movl   $0x8048a68,(%esp)                ; "\033[32m.", '-' <repeats 27 times>, "."
   0x080487c6 <+126>:	call   0x8048590 <puts@plt>             ; puts("\033[32m.----------------------------.");
   0x080487cb <+131>:	movl   $0x8048a8c,(%esp)                ; "\033[31m| !! TAMPERING DETECTED !!  |"
   0x080487d2 <+138>:	call   0x8048590 <puts@plt>             ; puts("\033[31m| !! TAMPERING DETECTED !!  |");
   0x080487d7 <+143>:	movl   $0x8048ab0,(%esp)                ; "\033[32m'", '-' <repeats 27 times>, "'"
   0x080487de <+150>:	call   0x8048590 <puts@plt>             ; puts("\033[32m'----------------------------'");

   0x080487e3 <+155>:	mov    $0x1,%eax                        ; load (1) for return(1)
   0x080487e8 <+160>:	jmp    0x8048877 <auth+303>             ; jump to return(1)


#### Seed Hash ####

   0x080487ed <+165>:	mov    0x8(%ebp),%eax                   ; login
   0x080487f0 <+168>:	add    $0x3,%eax                        ; login[3]
   0x080487f3 <+171>:	movzbl (%eax),%eax                      ; *login[3]
   0x080487f6 <+174>:	movsbl %al,%eax                         ; last 8 bits of eax
   0x080487f9 <+177>:	xor    $0x1337,%eax                     ; login[3] ^ 0x1337
   0x080487fe <+182>:	add    $0x5eeded,%eax                   ; (login[3] ^ 0x1337) + 0x5eeded
   0x08048803 <+187>:	mov    %eax,-0x10(%ebp)                 ; int nb = (login[3] ^ 4919) + 6221293


#### Initialize loop ####

   0x08048806 <+190>:	movl   $0x0,-0x14(%ebp)                 ; int i = 0;
   0x0804880d <+197>:	jmp    0x804885b <auth+275>             ; jump into while (i < len) loop


#### Check login is printable ####

   0x0804880f <+199>:	mov    -0x14(%ebp),%eax                 ; i
   0x08048812 <+202>:	add    0x8(%ebp),%eax                   ; login[i]
   0x08048815 <+205>:	movzbl (%eax),%eax                      ; *login[i]
   0x08048818 <+208>:	cmp    $0x1f,%al                        ; login[i] <= 31 ? (ascii printable)
   0x0804881a <+210>:	jg     0x8048823 <auth+219>             ; jump past return(1)
   0x0804881c <+212>:	mov    $0x1,%eax                        ; load (1) for return(1)
   0x08048821 <+217>:	jmp    0x8048877 <auth+303>             ; jump to return(1)




   0x08048823 <+219>:	mov    -0x14(%ebp),%eax
   0x08048826 <+222>:	add    0x8(%ebp),%eax
   0x08048829 <+225>:	movzbl (%eax),%eax
   0x0804882c <+228>:	movsbl %al,%eax
   0x0804882f <+231>:	mov    %eax,%ecx
   0x08048831 <+233>:	xor    -0x10(%ebp),%ecx
   0x08048834 <+236>:	mov    $0x88233b2b,%edx
   0x08048839 <+241>:	mov    %ecx,%eax
   0x0804883b <+243>:	mul    %edx
   0x0804883d <+245>:	mov    %ecx,%eax
   0x0804883f <+247>:	sub    %edx,%eax
   0x08048841 <+249>:	shr    %eax
   0x08048843 <+251>:	add    %edx,%eax
   0x08048845 <+253>:	shr    $0xa,%eax
   0x08048848 <+256>:	imul   $0x539,%eax,%eax
   0x0804884e <+262>:	mov    %ecx,%edx
   0x08048850 <+264>:	sub    %eax,%edx
   0x08048852 <+266>:	mov    %edx,%eax
   0x08048854 <+268>:	add    %eax,-0x10(%ebp)
   0x08048857 <+271>:	addl   $0x1,-0x14(%ebp)
   0x0804885b <+275>:	mov    -0x14(%ebp),%eax
   0x0804885e <+278>:	cmp    -0xc(%ebp),%eax
   0x08048861 <+281>:	jl     0x804880f <auth+199>
   0x08048863 <+283>:	mov    0xc(%ebp),%eax
   0x08048866 <+286>:	cmp    -0x10(%ebp),%eax
   0x08048869 <+289>:	je     0x8048872 <auth+298>
   0x0804886b <+291>:	mov    $0x1,%eax
   0x08048870 <+296>:	jmp    0x8048877 <auth+303>
   0x08048872 <+298>:	mov    $0x0,%eax
   0x08048877 <+303>:	leave
   0x08048878 <+304>:	ret
End of assembler dump.
```
