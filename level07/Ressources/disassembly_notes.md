# Level 7 - Disassembly Notes

## Functions
```
level07@OverRide:~$ gdb -q level07
...
(gdb) info functions
All defined functions:

Non-debugging symbols:
0x0804842c  _init
0x08048470  printf
0x08048470  printf@plt
0x08048480  fflush
0x08048480  fflush@plt
0x08048490  getchar
0x08048490  getchar@plt
0x080484a0  fgets
0x080484a0  fgets@plt
0x080484b0  __stack_chk_fail
0x080484b0  __stack_chk_fail@plt
0x080484c0  puts
0x080484c0  puts@plt
0x080484d0  __gmon_start__
0x080484d0  __gmon_start__@plt
0x080484e0  __libc_start_main
0x080484e0  __libc_start_main@plt
0x080484f0  memset
0x080484f0  memset@plt
0x08048500  __isoc99_scanf
0x08048500  __isoc99_scanf@plt
0x08048510  _start
0x08048540  __do_global_dtors_aux
0x080485a0  frame_dummy
0x080485c4  clear_stdin
0x080485e7  get_unum                ; 
0x0804861f  prog_timeout            ; 
0x08048630  store_number            ; store
0x080486d7  read_number             ; read
0x08048723  main                    ; main
0x08048a00  __libc_csu_init
0x08048a70  __libc_csu_fini
0x08048a72  __i686.get_pc_thunk.bx
0x08048a80  __do_global_ctors_aux
0x08048aac  _fini
```

## main()
```
(gdb) disas main
Dump of assembler code for function main:
   0x08048723 <+0>:	push   %ebp
   0x08048724 <+1>:	mov    %esp,%ebp

   0x08048726 <+3>:	push   %edi
   0x08048727 <+4>:	push   %esi
   0x08048728 <+5>:	push   %ebx
   0x08048729 <+6>:	and    $0xfffffff0,%esp


#### Initialize stack ####

   0x0804872c <+9>:	sub    $0x1d0,%esp                      ; allocate 464 bytes on stack for local variables
   0x08048732 <+15>:	mov    0xc(%ebp),%eax                   ; argv[0]
   0x08048735 <+18>:	mov    %eax,0x1c(%esp)                  ; store argv[0]
   0x08048739 <+22>:	mov    0x10(%ebp),%eax                  ; env
   0x0804873c <+25>:	mov    %eax,0x18(%esp)                  ; store env

   0x08048740 <+29>:	mov    %gs:0x14,%eax                    ; canary value
   0x08048746 <+35>:	mov    %eax,0x1cc(%esp)                 ; store canary value at end of stack
   0x0804874d <+42>:	xor    %eax,%eax                        ; clear register eax

   0x0804874f <+44>:	movl   $0x0,0x1b4(%esp)                 ; int ret = 0;
   0x0804875a <+55>:	movl   $0x0,0x1b8(%esp)                 ; char buffer[20];
   0x08048765 <+66>:	movl   $0x0,0x1bc(%esp)                 ; 0
   0x08048770 <+77>:	movl   $0x0,0x1c0(%esp)                 ; 0
   0x0804877b <+88>:	movl   $0x0,0x1c4(%esp)                 ; 0
   0x08048786 <+99>:	movl   $0x0,0x1c8(%esp)                 ; 0
   0x08048791 <+110>:	lea    0x24(%esp),%ebx                  ; int tab[100] = 0;
   0x08048795 <+114>:	mov    $0x0,%eax                        ; 0
   0x0804879a <+119>:	mov    $0x64,%edx                       ; 100
   0x0804879f <+124>:	mov    %ebx,%edi                        ; tab
   0x080487a1 <+126>:	mov    %edx,%ecx                        ; zero loop
   0x080487a3 <+128>:	rep stos %eax,%es:(%edi)                ; int tab[100] = 0;


#### memset argv Loop ####

   0x080487a5 <+130>:	jmp    0x80487ea <main+199>             ; jump into loop

   0x080487a7 <+132>:	mov    0x1c(%esp),%eax                  ; argv
   0x080487ab <+136>:	mov    (%eax),%eax                      ; argv[i]
   0x080487ad <+138>:	movl   $0xffffffff,0x14(%esp)           ; -1
   0x080487b5 <+146>:	mov    %eax,%edx                        ; argv[i]
   0x080487b7 <+148>:	mov    $0x0,%eax                        ; 0
   0x080487bc <+153>:	mov    0x14(%esp),%ecx                  ; -1
   0x080487c0 <+157>:	mov    %edx,%edi                        ; argv[i]
   0x080487c2 <+159>:	repnz scas %es:(%edi),%al               ; strlen(argv[i])
   0x080487c4 <+161>:	mov    %ecx,%eax                        ; -1
   0x080487c6 <+163>:	not    %eax                             ; !
   0x080487c8 <+165>:	lea    -0x1(%eax),%edx                  ; strlen(argv[i]) - 1
   0x080487cb <+168>:	mov    0x1c(%esp),%eax                  ; argv
   0x080487cf <+172>:	mov    (%eax),%eax                      ; argv[i]
   0x080487d1 <+174>:	mov    %edx,0x8(%esp)                   ; load arg 3 - strlen(argv[i]) - 1
   0x080487d5 <+178>:	movl   $0x0,0x4(%esp)                   ; load arg 2 - 0
   0x080487dd <+186>:	mov    %eax,(%esp)                      ; load arg 1 - argv[i]
   0x080487e0 <+189>:	call   0x80484f0 <memset@plt>           ; memset(argv[i], 0, strlen(argv[i]) - 1);

   0x080487e5 <+194>:	addl   $0x4,0x1c(%esp)                  ; i++
   0x080487ea <+199>:	mov    0x1c(%esp),%eax                  ; argv[i]
   0x080487ee <+203>:	mov    (%eax),%eax                      ; argv[i]
   0x080487f0 <+205>:	test   %eax,%eax                        ; argv[i] = 0 ?
   0x080487f2 <+207>:	jne    0x80487a7 <main+132>             ; jump back to start of loop


#### memset env Loop ####

   0x080487f4 <+209>:	jmp    0x8048839 <main+278>             ; jump into loop

   0x080487f6 <+211>:	mov    0x18(%esp),%eax                  ; env
   0x080487fa <+215>:	mov    (%eax),%eax                      ; env[i]
   0x080487fc <+217>:	movl   $0xffffffff,0x14(%esp)           ; -1
   0x08048804 <+225>:	mov    %eax,%edx                        ; env[i]
   0x08048806 <+227>:	mov    $0x0,%eax                        ; 0
   0x0804880b <+232>:	mov    0x14(%esp),%ecx                  ; -1
   0x0804880f <+236>:	mov    %edx,%edi                        ; zero loop
   0x08048811 <+238>:	repnz scas %es:(%edi),%al               ; strlen(env[i])

   0x08048813 <+240>:	mov    %ecx,%eax                        ; -1
   0x08048815 <+242>:	not    %eax                             ; !
   0x08048817 <+244>:	lea    -0x1(%eax),%edx                  ; strlen(env[i]) - 1
   0x0804881a <+247>:	mov    0x18(%esp),%eax                  ; env
   0x0804881e <+251>:	mov    (%eax),%eax                      ; env[i]
   0x08048820 <+253>:	mov    %edx,0x8(%esp)                   ; load arg 3 - strlen(env[i]) - 1
   0x08048824 <+257>:	movl   $0x0,0x4(%esp)                   ; load arg 2 - 0
   0x0804882c <+265>:	mov    %eax,(%esp)                      ; load arg 1 - env[i]
   0x0804882f <+268>:	call   0x80484f0 <memset@plt>           ; memset(env[i], 0, strlen(env[i] - 1));

   0x08048834 <+273>:	addl   $0x4,0x18(%esp)                  ; i++
   0x08048839 <+278>:	mov    0x18(%esp),%eax                  ; env[i]
   0x0804883d <+282>:	mov    (%eax),%eax                      ; env[i]
   0x0804883f <+284>:	test   %eax,%eax                        ; env[i] = 0 ?
   0x08048841 <+286>:	jne    0x80487f6 <main+211>             ; jump back to start of loop


#### Print Welcome, Input command ####

   0x08048843 <+288>:	movl   $0x8048b38,(%esp)                ; '-' <repeats 52 times>, "\n  Welcome to wil's crappy number storage service!   \n", '-' <repeats 52 times>, "\n Commands:", ' ' <repeats 31 times>...
   0x0804884a <+295>:	call   0x80484c0 <puts@plt>             ; puts Welcome

   0x0804884f <+300>:	mov    $0x8048d4b,%eax                  ; "Input command: "
   0x08048854 <+305>:	mov    %eax,(%esp)                      ; "Input command: "
   0x08048857 <+308>:	call   0x8048470 <printf@plt>           ; printf "Input command: "


#### Read stdin to buffer ####

   0x0804885c <+313>:	movl   $0x1,0x1b4(%esp)                 ; ret = 1;
   0x08048867 <+324>:	mov    0x804a040,%eax                   ; stdin
   0x0804886c <+329>:	mov    %eax,0x8(%esp)                   ; load arg 3 - stdin
   0x08048870 <+333>:	movl   $0x14,0x4(%esp)                  ; load arg 2 - 20
   0x08048878 <+341>:	lea    0x1b8(%esp),%eax                 ; buffer
   0x0804887f <+348>:	mov    %eax,(%esp)                      ; load arg 1 - buffer
   0x08048882 <+351>:	call   0x80484a0 <fgets@plt>            ; fgets(buffer, 20, stdin);


#### Null terminate buffer ####

   0x08048887 <+356>:	lea    0x1b8(%esp),%eax                 ; buffer
   0x0804888e <+363>:	movl   $0xffffffff,0x14(%esp)           ; -1
   0x08048896 <+371>:	mov    %eax,%edx                        ; buffer
   0x08048898 <+373>:	mov    $0x0,%eax                        ; 0
   0x0804889d <+378>:	mov    0x14(%esp),%ecx                  ; buffer
   0x080488a1 <+382>:	mov    %edx,%edi                        ; strlen loop
   0x080488a3 <+384>:	repnz scas %es:(%edi),%al               ; strlen(buffer)
   0x080488a5 <+386>:	mov    %ecx,%eax                        ; strlen(buffer)
   0x080488a7 <+388>:	not    %eax                             ; !
   0x080488a9 <+390>:	sub    $0x1,%eax                        ; strlen(buffer) - 1
   0x080488ac <+393>:	sub    $0x1,%eax                        ; strlen(buffer) - 2
   0x080488af <+396>:	movb   $0x0,0x1b8(%esp,%eax,1)          ; buffer[strlen(buffer) - 2] = 0;


#### Command = store ? ####

   0x080488b7 <+404>:	lea    0x1b8(%esp),%eax                 ; buffer
   0x080488be <+411>:	mov    %eax,%edx                        ; buffer
   0x080488c0 <+413>:	mov    $0x8048d5b,%eax                  ; "store"
   0x080488c5 <+418>:	mov    $0x5,%ecx                        ; 5 (bytes len for strncmp)
   0x080488ca <+423>:	mov    %edx,%esi                        ; buffer
   0x080488cc <+425>:	mov    %eax,%edi                        ; "store"
   0x080488ce <+427>:	repz cmpsb %es:(%edi),%ds:(%esi)        ; strncmp("store", buffer, 5)
   0x080488d0 <+429>:	seta   %dl                              ; compare
   0x080488d3 <+432>:	setb   %al                              ; compare
   0x080488d6 <+435>:	mov    %edx,%ecx                        ; compare
   0x080488d8 <+437>:	sub    %al,%cl                          ; compare
   0x080488da <+439>:	mov    %ecx,%eax                        ; result
   0x080488dc <+441>:	movsbl %al,%eax                         ; result
   0x080488df <+444>:	test   %eax,%eax                        ; strncmp("store", buffer, 5) = 0 ?
   0x080488e1 <+446>:	jne    0x80488f8 <main+469>             ; jump past call store_number()

   0x080488e3 <+448>:	lea    0x24(%esp),%eax                  ; tab
   0x080488e7 <+452>:	mov    %eax,(%esp)                      ; load arg - tab
   0x080488ea <+455>:	call   0x8048630 <store_number>         ; ret = store_number(tab)
   0x080488ef <+460>:	mov    %eax,0x1b4(%esp)                 ; store return
   0x080488f6 <+467>:	jmp    0x8048965 <main+578>             ; jump to end of else command strncmp


#### Command = read ? ####

   0x080488f8 <+469>:	lea    0x1b8(%esp),%eax                 ; buffer
   0x080488ff <+476>:	mov    %eax,%edx                        ; buffer
   0x08048901 <+478>:	mov    $0x8048d61,%eax                  ; "read"
   0x08048906 <+483>:	mov    $0x4,%ecx                        ; 4 (bytes len for strncmp)
   0x0804890b <+488>:	mov    %edx,%esi                        ; buffer
   0x0804890d <+490>:	mov    %eax,%edi                        ; "read"
   0x0804890f <+492>:	repz cmpsb %es:(%edi),%ds:(%esi)        ; strncmp("read", buffer, 4)
   0x08048911 <+494>:	seta   %dl                              ; compare
   0x08048914 <+497>:	setb   %al                              ; compare
   0x08048917 <+500>:	mov    %edx,%ecx                        ; compare
   0x08048919 <+502>:	sub    %al,%cl                          ; compare
   0x0804891b <+504>:	mov    %ecx,%eax                        ; result
   0x0804891d <+506>:	movsbl %al,%eax                         ; result
   0x08048920 <+509>:	test   %eax,%eax                        ; strncmp("read", buffer, 4) = 0 ?
   0x08048922 <+511>:	jne    0x8048939 <main+534>             ; jump past call read_number()

   0x08048924 <+513>:	lea    0x24(%esp),%eax                  ; tab
   0x08048928 <+517>:	mov    %eax,(%esp)                      ; load arg - tab
   0x0804892b <+520>:	call   0x80486d7 <read_number>          ; ret = read_number(tab)
   0x08048930 <+525>:	mov    %eax,0x1b4(%esp)                 ; store return
   0x08048937 <+532>:	jmp    0x8048965 <main+578>             ; jump to end of else command strncmp


#### Command = quit ? ####

   0x08048939 <+534>:	lea    0x1b8(%esp),%eax                 ; buffer
   0x08048940 <+541>:	mov    %eax,%edx                        ; buffer
   0x08048942 <+543>:	mov    $0x8048d66,%eax                  ; "quit"
   0x08048947 <+548>:	mov    $0x4,%ecx                        ; 4 (bytes len for strncmp)
   0x0804894c <+553>:	mov    %edx,%esi                        ; buffer
   0x0804894e <+555>:	mov    %eax,%edi                        ; "quit"
   0x08048950 <+557>:	repz cmpsb %es:(%edi),%ds:(%esi)        ; strncmp("quit", buffer, 4)
   0x08048952 <+559>:	seta   %dl                              ; compare
   0x08048955 <+562>:	setb   %al                              ; compare
   0x08048958 <+565>:	mov    %edx,%ecx                        ; compare
   0x0804895a <+567>:	sub    %al,%cl                          ; compare
   0x0804895c <+569>:	mov    %ecx,%eax                        ; result
   0x0804895e <+571>:	movsbl %al,%eax                         ; result
   0x08048961 <+574>:	test   %eax,%eax                        ; strncmp("read", buffer, 4) = 0 ?
   0x08048963 <+576>:	je     0x80489cf <main+684>             ; jump to return(0)


#### Command Fail / Success ####

   0x08048965 <+578>:	cmpl   $0x0,0x1b4(%esp)                 ; ret = 0 ?
   0x0804896d <+586>:	je     0x8048989 <main+614>             ; jump to Success

   0x0804896f <+588>:	mov    $0x8048d6b,%eax                  ; " Failed to do %s command\n"
   0x08048974 <+593>:	lea    0x1b8(%esp),%edx                 ; buffer
   0x0804897b <+600>:	mov    %edx,0x4(%esp)                   ; load arg 2 - buffer
   0x0804897f <+604>:	mov    %eax,(%esp)                      ; load arg 1 - " Failed to do %s command\n"
   0x08048982 <+607>:	call   0x8048470 <printf@plt>           ; printf(" Failed to do %s command\n", buffer);
   0x08048987 <+612>:	jmp    0x80489a1 <main+638>             ; jump to bzero return(0)

   0x08048989 <+614>:	mov    $0x8048d88,%eax                  ; " Completed %s command successfully\n"
   0x0804898e <+619>:	lea    0x1b8(%esp),%edx                 ; buffer
   0x08048995 <+626>:	mov    %edx,0x4(%esp)                   ; load arg 2 - buffer
   0x08048999 <+630>:	mov    %eax,(%esp)                      ; load arg 1 - " Completed %s command successfully\n"
   0x0804899c <+633>:	call   0x8048470 <printf@plt>           ; printf(" Completed %s command successfully\n", buffer);


#### Flush buffer ####

   0x080489a1 <+638>:	lea    0x1b8(%esp),%eax                 ; buffer
   0x080489a8 <+645>:	movl   $0x0,(%eax)                      ; bzero(buffer, 20);
   0x080489ae <+651>:	movl   $0x0,0x4(%eax)                   ; bzero(buffer, 20);
   0x080489b5 <+658>:	movl   $0x0,0x8(%eax)                   ; bzero(buffer, 20);
   0x080489bc <+665>:	movl   $0x0,0xc(%eax)                   ; bzero(buffer, 20);
   0x080489c3 <+672>:	movl   $0x0,0x10(%eax)                  ; bzero(buffer, 20);


#### Command Loop, jump back ####

   0x080489ca <+679>:	jmp    0x804884f <main+300>             ; jump back to start of command loop
   0x080489cf <+684>:	nop


#### Return ####

   0x080489d0 <+685>:	mov    $0x0,%eax                        ; 0
   0x080489d5 <+690>:	mov    0x1cc(%esp),%esi                 ; load stored canary value
   0x080489dc <+697>:	xor    %gs:0x14,%esi                    ; load original canary value
   0x080489e3 <+704>:	je     0x80489ea <main+711>             ; jump past stack overflow exit
   0x080489e5 <+706>:	call   0x80484b0 <__stack_chk_fail@plt> ; stack overflow exit
   0x080489ea <+711>:	lea    -0xc(%ebp),%esp

   0x080489ed <+714>:	pop    %ebx
   0x080489ee <+715>:	pop    %esi
   0x080489ef <+716>:	pop    %edi
   0x080489f0 <+717>:	pop    %ebp

   0x080489f1 <+718>:	ret
End of assembler dump.
```

## read_number()
```
(gdb) disas read_number
Dump of assembler code for function read_number:
   0x080486d7 <+0>:	push   %ebp
   0x080486d8 <+1>:	mov    %esp,%ebp
   0x080486da <+3>:	sub    $0x28,%esp             ; allocate 40 bytes on stack for local variables


#### Print Index ####

   0x080486dd <+6>:	movl   $0x0,-0xc(%ebp)        ; unsigned int input = 0;
   0x080486e4 <+13>:	mov    $0x8048add,%eax        ; " Index: "
   0x080486e9 <+18>:	mov    %eax,(%esp)            ; load arg - " Index: "
   0x080486ec <+21>:	call   0x8048470 <printf@plt> ; printf(" Index: ");


#### get_unum() ####

   0x080486f1 <+26>:	call   0x80485e7 <get_unum>   ; get_unum()
   0x080486f6 <+31>:	mov    %eax,-0xc(%ebp)        ; store return


#### Print Number ####

   0x080486f9 <+34>:	mov    -0xc(%ebp),%eax        ; get_unum() return
   0x080486fc <+37>:	shl    $0x2,%eax              ; shift left 2
   0x080486ff <+40>:	add    0x8(%ebp),%eax         ; tab[input]
   0x08048702 <+43>:	mov    (%eax),%edx            ; tab[input]
   0x08048704 <+45>:	mov    $0x8048b1b,%eax        ; " Number at data[%u] is %u\n"
   0x08048709 <+50>:	mov    %edx,0x8(%esp)         ; load arg 3 - tab[input]
   0x0804870d <+54>:	mov    -0xc(%ebp),%edx        ; input
   0x08048710 <+57>:	mov    %edx,0x4(%esp)         ; load arg 2 - input
   0x08048714 <+61>:	mov    %eax,(%esp)            ; load arg 1 - " Number at data[%u] is %u\n"
   0x08048717 <+64>:	call   0x8048470 <printf@plt> ; printf(" Number at data[%u] is %u\n", input, tab[input]);

   0x0804871c <+69>:	mov    $0x0,%eax              ; load (0) for return(0)
   0x08048721 <+74>:	leave
   0x08048722 <+75>:	ret
End of assembler dump.
```

## store_number()
```
(gdb) disas store_number
Dump of assembler code for function store_number:
   0x08048630 <+0>:	push   %ebp
   0x08048631 <+1>:	mov    %esp,%ebp


#### Initialize Stack ####

   0x08048633 <+3>:	sub    $0x28,%esp                      ; allocate 40 bytes on stack for local variables
   0x08048636 <+6>:	movl   $0x0,-0x10(%ebp)                ; unsigned int input = 0;
   0x0804863d <+13>:	movl   $0x0,-0xc(%ebp)                 ; unsigned int index = 0;


#### Get Input ####

   0x08048644 <+20>:	mov    $0x8048ad3,%eax                 ; " Number: "
   0x08048649 <+25>:	mov    %eax,(%esp)                     ; load arg - " Number: "
   0x0804864c <+28>:	call   0x8048470 <printf@plt>          ; printf(" Number: ");

   0x08048651 <+33>:	call   0x80485e7 <get_unum>            ; get_unum()
   0x08048656 <+38>:	mov    %eax,-0x10(%ebp)                ; input = get_unum()


#### Get Index ####

   0x08048659 <+41>:	mov    $0x8048add,%eax                 ; " Index: "
   0x0804865e <+46>:	mov    %eax,(%esp)                     ; load arg - " Index: "
   0x08048661 <+49>:	call   0x8048470 <printf@plt>          ; printf(" Index: ");

   0x08048666 <+54>:	call   0x80485e7 <get_unum>            ; get_unum()
   0x0804866b <+59>:	mov    %eax,-0xc(%ebp)                 ; index = get_unum()


#### Check index & input ####

   0x0804866e <+62>:	mov    -0xc(%ebp),%ecx                 ; index
   0x08048671 <+65>:	mov    $0xaaaaaaab,%edx                ; 0xaaaaaaab
   0x08048676 <+70>:	mov    %ecx,%eax                       ; index
   0x08048678 <+72>:	mul    %edx                            ; index / 3
   0x0804867a <+74>:	shr    %edx                            ; useless
   0x0804867c <+76>:	mov    %edx,%eax                       ; useless
   0x0804867e <+78>:	add    %eax,%eax                       ; useless
   0x08048680 <+80>:	add    %edx,%eax                       ; useless
   0x08048682 <+82>:	mov    %ecx,%edx                       ; useless
   0x08048684 <+84>:	sub    %eax,%edx                       ; modulo
   0x08048686 <+86>:	test   %edx,%edx                       ; index % 3 == 0 ?
   0x08048688 <+88>:	je     0x8048697 <store_number+103>    ; jump to puts

   0x0804868a <+90>:	mov    -0x10(%ebp),%eax                ; input
   0x0804868d <+93>:	shr    $0x18,%eax                      ; shift right 24
   0x08048690 <+96>:	cmp    $0xb7,%eax                      ; == 183 ?
   0x08048695 <+101>:	jne    0x80486c2 <store_number+146> ; jump past puts


#### Print Error index reserved for wil!, return(1) ####

   0x08048697 <+103>:	movl   $0x8048ae6,(%esp)            ; " *** ERROR! ***"
   0x0804869e <+110>:	call   0x80484c0 <puts@plt>         ; puts(" *** ERROR! ***")
   0x080486a3 <+115>:	movl   $0x8048af8,(%esp)            ; "   This index is reserved for wil!"
   0x080486aa <+122>:	call   0x80484c0 <puts@plt>         ; puts("   This index is reserved for wil!")
   0x080486af <+127>:	movl   $0x8048ae6,(%esp)            ; " *** ERROR! ***"
   0x080486b6 <+134>:	call   0x80484c0 <puts@plt>         ; puts(" *** ERROR! ***")

   0x080486bb <+139>:	mov    $0x1,%eax                    ; load (1) for return(1)
   0x080486c0 <+144>:	jmp    0x80486d5 <store_number+165> ; jump to return(1)


#### Store input, return(0) ####

   0x080486c2 <+146>:	mov    -0xc(%ebp),%eax              ; index
   0x080486c5 <+149>:	shl    $0x2,%eax                    ; shift left 2
   0x080486c8 <+152>:	add    0x8(%ebp),%eax               ; tab[index]
   0x080486cb <+155>:	mov    -0x10(%ebp),%edx             ; input
   0x080486ce <+158>:	mov    %edx,(%eax)                  ; tab[index] = input;

   0x080486d0 <+160>:	mov    $0x0,%eax                    ; load (0) for return(0)
   0x080486d5 <+165>:	leave
   0x080486d6 <+166>:	ret
End of assembler dump.
```

## get_unum()
```
(gdb) disas get_unum
Dump of assembler code for function get_unum:
   0x080485e7 <+0>:	push   %ebp
   0x080485e8 <+1>:	mov    %esp,%ebp


#### Initialize Stack ####

   0x080485ea <+3>:	sub    $0x28,%esp                      ; allocate 40 bytes on stack for local variables
   0x080485ed <+6>:	movl   $0x0,-0xc(%ebp)                 ; unsigned int input;


#### Flush Stdout ####

   0x080485f4 <+13>:	mov    0x804a060,%eax                  ; stdout
   0x080485f9 <+18>:	mov    %eax,(%esp)                     ; load arg - stdout
   0x080485fc <+21>:	call   0x8048480 <fflush@plt>          ; fflush(stdout)


#### Read input ####

   0x08048601 <+26>:	mov    $0x8048ad0,%eax                 ; "%u"
   0x08048606 <+31>:	lea    -0xc(%ebp),%edx                 ; input
   0x08048609 <+34>:	mov    %edx,0x4(%esp)                  ; load arg 2 - input
   0x0804860d <+38>:	mov    %eax,(%esp)                     ; load arg 1 - "%u"
   0x08048610 <+41>:	call   0x8048500 <__isoc99_scanf@plt>  ; scanf("%u", input);


#### Return input ####

   0x08048615 <+46>:	call   0x80485c4 <clear_stdin>         ; clear_stdin()
   0x0804861a <+51>:	mov    -0xc(%ebp),%eax                 ; load (input) for return(input)
   0x0804861d <+54>:	leave
   0x0804861e <+55>:	ret
End of assembler dump.
```
