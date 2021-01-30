

```
(gdb) disas main
Dump of assembler code for function main:
   0x080484d0 <+0>:	push   %ebp
   0x080484d1 <+1>:	mov    %esp,%ebp
   
   0x080484d3 <+3>:	push   %edi
   0x080484d4 <+4>:	push   %ebx
   0x080484d5 <+5>:	and    $0xfffffff0,%esp
   0x080484d8 <+8>:	sub    $0x60,%esp
   0x080484db <+11>:	lea    0x1c(%esp),%ebx
   0x080484df <+15>:	mov    $0x0,%eax
   0x080484e4 <+20>:	mov    $0x10,%edx
   0x080484e9 <+25>:	mov    %ebx,%edi
   0x080484eb <+27>:	mov    %edx,%ecx
   0x080484ed <+29>:	rep stos %eax,%es:(%edi)
   0x080484ef <+31>:	movl   $0x0,0x5c(%esp)
   0x080484f7 <+39>:	movl   $0x80486b8,(%esp)                ;  "********* ADMIN LOGIN PROMPT *********"
   0x080484fe <+46>:	call   0x8048380 <puts@plt>
   
   0x08048503 <+51>:	mov    $0x80486df,%eax                  ; 	 "Enter Username: "
   0x08048508 <+56>:	mov    %eax,(%esp)
   0x0804850b <+59>:	call   0x8048360 <printf@plt>
   
   0x08048510 <+64>:	mov    0x804a020,%eax                   ; user input, <stdin@@GLIBC_2.0>:	 ""
   0x08048515 <+69>:	mov    %eax,0x8(%esp)                   ; set argument 3
   0x08048519 <+73>:	movl   $0x100,0x4(%esp)                 ; set argument 2, value 256
   0x08048521 <+81>:	movl   $0x804a040,(%esp)                ; set argument 1, <a_user_name>:	 ""
   0x08048528 <+88>:	call   0x8048370 <fgets@plt>            ; fgets(esp, esp+4, esp+8) ... fgets(a_user_name, user input)
   0x0804852d <+93>:	call   0x8048464 <verify_user_name>
   
   0x08048532 <+98>:	mov    %eax,0x5c(%esp)
   0x08048536 <+102>:	cmpl   $0x0,0x5c(%esp)                  ; compare input to username in memory
   0x0804853b <+107>:	je     0x8048550 <main+128>             ; jump if not equal
   0x0804853d <+109>:	movl   $0x80486f0,(%esp)                ; set argument 1, "nope, incorrect username...\n"
   0x08048544 <+116>:	call   0x8048380 <puts@plt>             ; puts("nope, incorrect username...\n")
   
   0x08048549 <+121>:	mov    $0x1,%eax
   0x0804854e <+126>:	jmp    0x80485af <main+223>
   0x08048550 <+128>:	movl   $0x804870d,(%esp)                ; set argument 1, "Enter Password: "
   0x08048557 <+135>:	call   0x8048380 <puts@plt>             ; puts("Enter Password: ")
   0x0804855c <+140>:	mov    0x804a020,%eax                   ; user input, <stdin@@GLIBC_2.0>:	 ""
   
   0x08048561 <+145>:	mov    %eax,0x8(%esp)                   ; set argument 3
   0x08048565 <+149>:	movl   $0x64,0x4(%esp)                  ; set argument 2, value 100
   0x0804856d <+157>:	lea    0x1c(%esp),%eax
   0x08048571 <+161>:	mov    %eax,(%esp)                      ; set argument 1
   0x08048574 <+164>:	call   0x8048370 <fgets@plt>            ; fgets(esp, esp+4, esp+8) ... fgets(password, 100, user input)
   0x08048579 <+169>:	lea    0x1c(%esp),%eax
   0x0804857d <+173>:	mov    %eax,(%esp)
   0x08048580 <+176>:	call   0x80484a3 <verify_user_pass>     ; verify user password
   
   0x08048585 <+181>:	mov    %eax,0x5c(%esp)
   0x08048589 <+185>:	cmpl   $0x0,0x5c(%esp)                  ; compare input to password in memory
   0x0804858e <+190>:	je     0x8048597 <main+199>             ; jump if not equal
   0x08048590 <+192>:	cmpl   $0x0,0x5c(%esp)
   0x08048595 <+197>:	je     0x80485aa <main+218>
   0x08048597 <+199>:	movl   $0x804871e,(%esp)                ; "nope, incorrect password...\n"
   0x0804859e <+206>:	call   0x8048380 <puts@plt>             ; puts("nope, incorrect password...\n")
   0x080485a3 <+211>:	mov    $0x1,%eax
   0x080485a8 <+216>:	jmp    0x80485af <main+223>
   0x080485aa <+218>:	mov    $0x0,%eax
   0x080485af <+223>:	lea    -0x8(%ebp),%esp
   0x080485b2 <+226>:	pop    %ebx
   0x080485b3 <+227>:	pop    %edi
   0x080485b4 <+228>:	pop    %ebp
   0x080485b5 <+229>:	ret
```
