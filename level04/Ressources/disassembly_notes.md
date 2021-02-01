# Level 4 - Disassembly Notes

```
level04@OverRide:~$ gdb -q level04
...
(gdb) disas main
Dump of assembler code for function main:
   0x080486c8 <+0>:	push   %ebp
   0x080486c9 <+1>:	mov    %esp,%ebp
   0x080486cb <+3>:	push   %edi
   0x080486cc <+4>:	push   %ebx
   0x080486cd <+5>:	and    $0xfffffff0,%esp
   0x080486d0 <+8>:	sub    $0xb0,%esp             ; allocate 176 bytes on stack for local variables


#### Fork child process ####

   0x080486d6 <+14>:	call   0x8048550 <fork@plt>   ; fork() child process
   0x080486db <+19>:	mov    %eax,0xac(%esp)        ; int child_pid = fork()


#### Initialize local variables ####

   0x080486e2 <+26>:	lea    0x20(%esp),%ebx        ; char buffer[32]
   
   0x080486e6 <+30>:	mov    $0x0,%eax              ; 0
   0x080486eb <+35>:	mov    $0x20,%edx             ; 32
   0x080486f0 <+40>:	mov    %ebx,%edi              ; buffer[32]
   0x080486f2 <+42>:	mov    %edx,%ecx
   0x080486f4 <+44>:	rep stos %eax,%es:(%edi)      ; bzero(buffer, 32);
   
   0x080486f6 <+46>:	movl   $0x0,0xa8(%esp)        ; int ptrace_ret = 0;
   
   0x08048701 <+57>:	movl   $0x0,0x1c(%esp)        ; int status = 0;
   
   0x08048709 <+65>:	cmpl   $0x0,0xac(%esp)        ; child_pid = 0 ?
   0x08048711 <+73>:	jne    0x8048769 <main+161>   ; jump past gets(buffer)


#### Child return status to Parent process ####

   0x08048713 <+75>:	movl   $0x1,0x4(%esp)         ; load arg 2 - 1
   0x0804871b <+83>:	movl   $0x1,(%esp)            ; load arg 1 - 1
   0x08048722 <+90>:	call   0x8048540 <prctl@plt>  ; prctl(1, 1);
   
   0x08048727 <+95>:	movl   $0x0,0xc(%esp)         ; load arg 4 - 0
   0x0804872f <+103>:	movl   $0x0,0x8(%esp)         ; load arg 3 - 0
   0x08048737 <+111>:	movl   $0x0,0x4(%esp)         ; load arg 2 - 0
   0x0804873f <+119>:	movl   $0x0,(%esp)            ; load arg 1 - 0
   0x08048746 <+126>:	call   0x8048570 <ptrace@plt> ; ptrace(0, 0, 0, 0);


#### Read stdin to buffer ####

   0x0804874b <+131>:	movl   $0x8048903,(%esp)      ; "Give me some shellcode, k"
   0x08048752 <+138>:	call   0x8048500 <puts@plt>   ; puts("Give me some shellcode, k")
   
   0x08048757 <+143>:	lea    0x20(%esp),%eax        ; buffer[32]
   0x0804875b <+147>:	mov    %eax,(%esp)            ; load arg - buffer[32]
   0x0804875e <+150>:	call   0x80484b0 <gets@plt>   ; gets(buffer);
   
   0x08048763 <+155>:	jmp    0x804881a <main+338>   ; jump to return(0);


#### See child process exit status ####

   0x08048768 <+160>:	nop
   0x08048769 <+161>:	lea    0x1c(%esp),%eax        ; int status
   0x0804876d <+165>:	mov    %eax,(%esp)            ; load arg - status
   0x08048770 <+168>:	call   0x80484f0 <wait@plt>   ; wait(status);

   0x08048775 <+173>:	mov    0x1c(%esp),%eax        ; status
   0x08048779 <+177>:	mov    %eax,0xa0(%esp)        ; status
   0x08048780 <+184>:	mov    0xa0(%esp),%eax        ; status
   0x08048787 <+191>:	and    $0x7f,%eax             ; 127
   0x0804878a <+194>:	test   %eax,%eax              ; status = 127? WIFEXITED
   0x0804878c <+196>:	je     0x80487ac <main+228>   ; jump to "child is exiting..."

   0x0804878e <+198>:	mov    0x1c(%esp),%eax        ; status
   0x08048792 <+202>:	mov    %eax,0xa4(%esp)        ; status
   0x08048799 <+209>:	mov    0xa4(%esp),%eax        ; status
   0x080487a0 <+216>:	and    $0x7f,%eax             ; 127
   0x080487a3 <+219>:	add    $0x1,%eax              ; 1
   0x080487a6 <+222>:	sar    %al                    ; divide / 2
   0x080487a8 <+224>:	test   %al,%al                ; (((status & 127) + 1) / 2) > 0 ? WIFSIGNALED
   0x080487aa <+226>:	jle    0x80487ba <main+242>   ; jump past "child is exiting..."

   0x080487ac <+228>:	movl   $0x804891d,(%esp)      ; "child is exiting..."
   0x080487b3 <+235>:	call   0x8048500 <puts@plt>   ; puts("child is exiting...")
   0x080487b8 <+240>:	jmp    0x804881a <main+338>   ; jump to return(0)


#### ptrace() child process exec()? ####

   0x080487ba <+242>:	movl   $0x0,0xc(%esp)         ; load arg 4 - 0
   0x080487c2 <+250>:	movl   $0x2c,0x8(%esp)        ; load arg 3 - 44
   0x080487ca <+258>:	mov    0xac(%esp),%eax        ; child_pid
   0x080487d1 <+265>:	mov    %eax,0x4(%esp)         ; load arg 2 - child_pid
   0x080487d5 <+269>:	movl   $0x3,(%esp)            ; load arg 1 - 3 (PTRACE_PEEKUSR)
   0x080487dc <+276>:	call   0x8048570 <ptrace@plt> ; ptrace(PTRACE_PEEKUSR, child_pid, 44, 0
   0x080487e1 <+281>:	mov    %eax,0xa8(%esp)        ; load ptrace() return
   0x080487e8 <+288>:	cmpl   $0xb,0xa8(%esp)        ; ptrace() return = 11 (exec syscall)?
   0x080487f0 <+296>:	jne    0x8048768 <main+160>   ; jump back to start of loop


#### Kill child process ####

   0x080487f6 <+302>:	movl   $0x8048931,(%esp)      ; "no exec() for you"
   0x080487fd <+309>:	call   0x8048500 <puts@plt>   ; puts("no exec() for you")
   
   0x08048802 <+314>:	movl   $0x9,0x4(%esp)         ; 9 (non-catchable, non-ignorable kill signal)
   0x0804880a <+322>:	mov    0xac(%esp),%eax        ; child_pid
   0x08048811 <+329>:	mov    %eax,(%esp)            ; child_pid
   0x08048814 <+332>:	call   0x8048520 <kill@plt>   ; kill(child_pid, 9);
   0x08048819 <+337>:	nop


#### Return(0) ####

   0x0804881a <+338>:	mov    $0x0,%eax              ; load (0) for return(0)
   0x0804881f <+343>:	lea    -0x8(%ebp),%esp
   0x08048822 <+346>:	pop    %ebx
   0x08048823 <+347>:	pop    %edi
   0x08048824 <+348>:	pop    %ebp
   0x08048825 <+349>:	ret
End of assembler dump.
```

