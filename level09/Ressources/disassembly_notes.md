# Level 9 - Disassembly Notes

## Functions
```
level09@OverRide:~$ gdb -q level09
...
(gdb) info functions
All defined functions:

Non-debugging symbols:
0x00000000000006f0  _init
0x0000000000000720  strncpy
0x0000000000000720  strncpy@plt
0x0000000000000730  puts
0x0000000000000730  puts@plt
0x0000000000000740  system                ; secret_backdoor calls system()
0x0000000000000740  system@plt
0x0000000000000750  printf
0x0000000000000750  printf@plt
0x0000000000000760  __libc_start_main
0x0000000000000760  __libc_start_main@plt
0x0000000000000770  fgets
0x0000000000000770  fgets@plt
0x0000000000000780  __cxa_finalize
0x0000000000000780  __cxa_finalize@plt
0x0000000000000790  _start
0x00000000000007bc  call_gmon_start
0x00000000000007e0  __do_global_dtors_aux
0x0000000000000860  frame_dummy
0x000000000000088c  secret_backdoor       ; Uncalled secret_backdoor!!
0x00000000000008c0  handle_msg            ; called by main
0x0000000000000932  set_msg               ; called by handle_msg
0x00000000000009cd  set_username          ; called by handle_msg
0x0000000000000aa8  main                  ; main
0x0000000000000ad0  __libc_csu_init
0x0000000000000b60  __libc_csu_fini
0x0000000000000b70  __do_global_ctors_aux
0x0000000000000ba8  _fini
```

## main()
```
(gdb) disas main
Dump of assembler code for function main:
   0x0000000000000aa8 <+0>:	push   %rbp
   0x0000000000000aa9 <+1>:	mov    %rsp,%rbp
   0x0000000000000aac <+4>:	lea    0x15d(%rip),%rdi    # 0xc10 ; x/s 0x555555554c10
   0x0000000000000ab3 <+11>:	callq  0x730 <puts@plt>    ; puts('-' <repeats 44 times>, "\n|   ~Welcome to l33t-m$n ~    v1337        |\n", '-' <repeats 44 times>)
   0x0000000000000ab8 <+16>:	callq  0x8c0 <handle_msg>  ; call handle_msg()
   0x0000000000000abd <+21>:	mov    $0x0,%eax           ; load (0) for return(0)
   0x0000000000000ac2 <+26>:	pop    %rbp
   0x0000000000000ac3 <+27>:	retq
End of assembler dump.
```

## handle_msg()
```
(gdb) disas handle_msg
Dump of assembler code for function handle_msg:
   0x00000000000008c0 <+0>:	push   %rbp
   0x00000000000008c1 <+1>:	mov    %rsp,%rbp
   0x00000000000008c4 <+4>:	sub    $0xc0,%rsp             ;
   0x00000000000008cb <+11>:	lea    -0xc0(%rbp),%rax       ;
   0x00000000000008d2 <+18>:	add    $0x8c,%rax             ;
   0x00000000000008d8 <+24>:	movq   $0x0,(%rax)            ;
   0x00000000000008df <+31>:	movq   $0x0,0x8(%rax)         ;
   0x00000000000008e7 <+39>:	movq   $0x0,0x10(%rax)        ;
   0x00000000000008ef <+47>:	movq   $0x0,0x18(%rax)        ;
   0x00000000000008f7 <+55>:	movq   $0x0,0x20(%rax)        ;
   0x00000000000008ff <+63>:	movl   $0x8c,-0xc(%rbp)       ;
   0x0000000000000906 <+70>:	lea    -0xc0(%rbp),%rax       ;
   0x000000000000090d <+77>:	mov    %rax,%rdi              ;
   0x0000000000000910 <+80>:	callq  0x9cd <set_username>   ;
   0x0000000000000915 <+85>:	lea    -0xc0(%rbp),%rax       ;
   0x000000000000091c <+92>:	mov    %rax,%rdi              ;
   0x000000000000091f <+95>:	callq  0x932 <set_msg>        ;
   0x0000000000000924 <+100>:	lea    0x295(%rip),%rdi       # 0xbc0
   0x000000000000092b <+107>:	callq  0x730 <puts@plt>       ;
   0x0000000000000930 <+112>:	leaveq
   0x0000000000000931 <+113>:	retq
End of assembler dump.
```

## set_username()
```
(gdb) disas set_username
Dump of assembler code for function set_username:
   0x00000000000009cd <+0>:	push   %rbp
   0x00000000000009ce <+1>:	mov    %rsp,%rbp
   0x00000000000009d1 <+4>:	sub    $0xa0,%rsp                ;
   0x00000000000009d8 <+11>:	mov    %rdi,-0x98(%rbp)          ;
   0x00000000000009df <+18>:	lea    -0x90(%rbp),%rax          ;
   0x00000000000009e6 <+25>:	mov    %rax,%rsi                 ;
   0x00000000000009e9 <+28>:	mov    $0x0,%eax                 ;
   0x00000000000009ee <+33>:	mov    $0x10,%edx                ;
   0x00000000000009f3 <+38>:	mov    %rsi,%rdi                 ;
   0x00000000000009f6 <+41>:	mov    %rdx,%rcx                 ;
   0x00000000000009f9 <+44>:	rep stos %rax,%es:(%rdi)         ;
   0x00000000000009fc <+47>:	lea    0x1e1(%rip),%rdi          # 0xbe4
   0x0000000000000a03 <+54>:	callq  0x730 <puts@plt>          ;
   0x0000000000000a08 <+59>:	lea    0x1d0(%rip),%rax          # 0xbdf
   0x0000000000000a0f <+66>:	mov    %rax,%rdi                 ;
   0x0000000000000a12 <+69>:	mov    $0x0,%eax                 ;
   0x0000000000000a17 <+74>:	callq  0x750 <printf@plt>        ;
   0x0000000000000a1c <+79>:	mov    0x201595(%rip),%rax       # 0x201fb8
   0x0000000000000a23 <+86>:	mov    (%rax),%rax               ;
   0x0000000000000a26 <+89>:	mov    %rax,%rdx                 ;
   0x0000000000000a29 <+92>:	lea    -0x90(%rbp),%rax          ;
   0x0000000000000a30 <+99>:	mov    $0x80,%esi                ;
   0x0000000000000a35 <+104>:	mov    %rax,%rdi                 ;
   0x0000000000000a38 <+107>:	callq  0x770 <fgets@plt>         ;
   0x0000000000000a3d <+112>:	movl   $0x0,-0x4(%rbp)           ;
   0x0000000000000a44 <+119>:	jmp    0xa6a <set_username+157>  ;
   0x0000000000000a46 <+121>:	mov    -0x4(%rbp),%eax           ;
   0x0000000000000a49 <+124>:	cltq                             ;
   0x0000000000000a4b <+126>:	movzbl -0x90(%rbp,%rax,1),%ecx   ;
   0x0000000000000a53 <+134>:	mov    -0x98(%rbp),%rdx          ;
   0x0000000000000a5a <+141>:	mov    -0x4(%rbp),%eax           ;
   0x0000000000000a5d <+144>:	cltq                             ;
   0x0000000000000a5f <+146>:	mov    %cl,0x8c(%rdx,%rax,1)     ;
   0x0000000000000a66 <+153>:	addl   $0x1,-0x4(%rbp)           ;
   0x0000000000000a6a <+157>:	cmpl   $0x28,-0x4(%rbp)          ;
   0x0000000000000a6e <+161>:	jg     0xa81 <set_username+180>  ;
   0x0000000000000a70 <+163>:	mov    -0x4(%rbp),%eax           ;
   0x0000000000000a73 <+166>:	cltq                             ;
   0x0000000000000a75 <+168>:	movzbl -0x90(%rbp,%rax,1),%eax   ;
   0x0000000000000a7d <+176>:	test   %al,%al                   ;
   0x0000000000000a7f <+178>:	jne    0xa46 <set_username+121>  ;
   0x0000000000000a81 <+180>:	mov    -0x98(%rbp),%rax          ;
   0x0000000000000a88 <+187>:	lea    0x8c(%rax),%rdx           ;
   0x0000000000000a8f <+194>:	lea    0x165(%rip),%rax          # 0xbfb
   0x0000000000000a96 <+201>:	mov    %rdx,%rsi                 ;
   0x0000000000000a99 <+204>:	mov    %rax,%rdi                 ;
   0x0000000000000a9c <+207>:	mov    $0x0,%eax                 ;
   0x0000000000000aa1 <+212>:	callq  0x750 <printf@plt>        ;
   0x0000000000000aa6 <+217>:	leaveq
   0x0000000000000aa7 <+218>:	retq
End of assembler dump.
```

## set_msg()
```
(gdb) disas set_msg
Dump of assembler code for function set_msg:
   0x0000000000000932 <+0>:	push   %rbp
   0x0000000000000933 <+1>:	mov    %rsp,%rbp
   0x0000000000000936 <+4>:	sub    $0x410,%rsp         ;
   0x000000000000093d <+11>:	mov    %rdi,-0x408(%rbp)   ;
   0x0000000000000944 <+18>:	lea    -0x400(%rbp),%rax   ;
   0x000000000000094b <+25>:	mov    %rax,%rsi           ;
   0x000000000000094e <+28>:	mov    $0x0,%eax           ;
   0x0000000000000953 <+33>:	mov    $0x80,%edx          ;
   0x0000000000000958 <+38>:	mov    %rsi,%rdi           ;
   0x000000000000095b <+41>:	mov    %rdx,%rcx           ;
   0x000000000000095e <+44>:	rep stos %rax,%es:(%rdi)   ;
   0x0000000000000961 <+47>:	lea    0x265(%rip),%rdi    # 0xbcd
   0x0000000000000968 <+54>:	callq  0x730 <puts@plt>    ;
   0x000000000000096d <+59>:	lea    0x26b(%rip),%rax    # 0xbdf
   0x0000000000000974 <+66>:	mov    %rax,%rdi           ;
   0x0000000000000977 <+69>:	mov    $0x0,%eax           ;
   0x000000000000097c <+74>:	callq  0x750 <printf@plt>  ;
   0x0000000000000981 <+79>:	mov    0x201630(%rip),%rax # 0x201fb8
   0x0000000000000988 <+86>:	mov    (%rax),%rax         ;
   0x000000000000098b <+89>:	mov    %rax,%rdx           ;
   0x000000000000098e <+92>:	lea    -0x400(%rbp),%rax   ;
   0x0000000000000995 <+99>:	mov    $0x400,%esi         ;
   0x000000000000099a <+104>:	mov    %rax,%rdi           ;
   0x000000000000099d <+107>:	callq  0x770 <fgets@plt>   ;
   0x00000000000009a2 <+112>:	mov    -0x408(%rbp),%rax   ;
   0x00000000000009a9 <+119>:	mov    0xb4(%rax),%eax     ;
   0x00000000000009af <+125>:	movslq %eax,%rdx           ;
   0x00000000000009b2 <+128>:	lea    -0x400(%rbp),%rcx   ;
   0x00000000000009b9 <+135>:	mov    -0x408(%rbp),%rax   ;
   0x00000000000009c0 <+142>:	mov    %rcx,%rsi           ;
   0x00000000000009c3 <+145>:	mov    %rax,%rdi           ;
   0x00000000000009c6 <+148>:	callq  0x720 <strncpy@plt> ;
   0x00000000000009cb <+153>:	leaveq
   0x00000000000009cc <+154>:	retq
End of assembler dump.
```

## secret_backdoor()
```
(gdb) disas secret_backdoor
Dump of assembler code for function secret_backdoor:
   0x000000000000088c <+0>:	push   %rbp
   0x000000000000088d <+1>:	mov    %rsp,%rbp
   0x0000000000000890 <+4>:	add    $0xffffffffffffff80,%rsp  ;
   0x0000000000000894 <+8>:	mov    0x20171d(%rip),%rax       # 0x201fb8
   0x000000000000089b <+15>:	mov    (%rax),%rax               ;
   0x000000000000089e <+18>:	mov    %rax,%rdx                 ;
   0x00000000000008a1 <+21>:	lea    -0x80(%rbp),%rax          ;
   0x00000000000008a5 <+25>:	mov    $0x80,%esi                ;
   0x00000000000008aa <+30>:	mov    %rax,%rdi                 ;
   0x00000000000008ad <+33>:	callq  0x770 <fgets@plt>         ;
   0x00000000000008b2 <+38>:	lea    -0x80(%rbp),%rax          ;
   0x00000000000008b6 <+42>:	mov    %rax,%rdi                 ;
   0x00000000000008b9 <+45>:	callq  0x740 <system@plt>        ;
   0x00000000000008be <+50>:	leaveq
   0x00000000000008bf <+51>:	retq
End of assembler dump.
```
