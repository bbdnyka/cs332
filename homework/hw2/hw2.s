	.file	"hw2.c"
	.text
	.section	.rodata
.LC0:
	.string	"block device"
.LC1:
	.string	"character device"
.LC2:
	.string	"directory"
.LC3:
	.string	"named pipe (FIFO)"
.LC4:
	.string	"symbolic link"
.LC5:
	.string	"regular file"
.LC6:
	.string	"UNIX domain socket"
.LC7:
	.string	"unknown file type"
.LC8:
	.string	"UNKNOWN"
	.text
	.globl	fileType
	.type	fileType, @function
fileType:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -20(%rbp)
	movzbl	-20(%rbp), %eax
	cmpl	$12, %eax
	ja	.L2
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L4(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L4(%rip), %rdx
	addq	%rdx, %rax
	notrack jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L4:
	.long	.L11-.L4
	.long	.L10-.L4
	.long	.L9-.L4
	.long	.L2-.L4
	.long	.L8-.L4
	.long	.L2-.L4
	.long	.L7-.L4
	.long	.L2-.L4
	.long	.L6-.L4
	.long	.L2-.L4
	.long	.L5-.L4
	.long	.L2-.L4
	.long	.L3-.L4
	.text
.L7:
	leaq	.LC0(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L9:
	leaq	.LC1(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L8:
	leaq	.LC2(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L10:
	leaq	.LC3(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L5:
	leaq	.LC4(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L6:
	leaq	.LC5(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L3:
	leaq	.LC6(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L11:
	leaq	.LC7(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L2:
	leaq	.LC8(%rip), %rax
	movq	%rax, -8(%rbp)
.L12:
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	fileType, .-fileType
	.section	.rodata
.LC9:
	.string	"Error opening directory '%s'\n"
.LC10:
	.string	"."
.LC11:
	.string	".."
.LC12:
	.string	" "
.LC13:
	.string	"%*s[%d] %s (%s)\n"
	.text
	.globl	traverseDir
	.type	traverseDir, @function
traverseDir:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	opendir@PLT
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L15
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC9(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$-1, %edi
	call	exit@PLT
.L15:
	movl	$1, -28(%rbp)
	jmp	.L16
.L19:
	movq	-16(%rbp), %rax
	addq	$19, %rax
	leaq	.LC10(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L16
	movq	-16(%rbp), %rax
	addq	$19, %rax
	leaq	.LC11(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L18
	jmp	.L16
.L18:
	movq	-16(%rbp), %rax
	movzbl	18(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	fileType
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	leaq	19(%rax), %rcx
	movl	-44(%rbp), %eax
	leal	0(,%rax,4), %esi
	movl	-28(%rbp), %eax
	movq	%rdx, %r9
	movq	%rcx, %r8
	movl	%eax, %ecx
	leaq	.LC12(%rip), %rdx
	leaq	.LC13(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -28(%rbp)
.L16:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	readdir@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L19
	movq	-16(%rbp), %rax
	movzbl	18(%rax), %eax
	cmpb	$4, %al
	jne	.L21
	movl	$2000, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movq	-40(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy@PLT
	movq	-8(%rbp), %rax
	movq	$-1, %rcx
	movq	%rax, %rdx
	movl	$0, %eax
	movq	%rdx, %rdi
	repnz scasb
	movq	%rcx, %rax
	notq	%rax
	leaq	-1(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movw	$47, (%rax)
	movq	-16(%rbp), %rax
	leaq	19(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
	movl	-44(%rbp), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	traverseDir
.L21:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	traverseDir, .-traverseDir
	.section	.rodata
.LC14:
	.string	"File type:                "
.LC15:
	.string	"FIFO/pipe"
.LC16:
	.string	"symlink"
.LC17:
	.string	"socket"
.LC18:
	.string	"unknown?"
	.align 8
.LC19:
	.string	"I-node number:            %ld\n"
	.align 8
.LC20:
	.string	"Mode:                     %lo (octal)\n"
	.align 8
.LC21:
	.string	"Link count:               %ld\n"
	.align 8
.LC22:
	.string	"Ownership:                UID=%ld   GID=%ld\n"
	.align 8
.LC23:
	.string	"Preferred I/O block size: %ld bytes\n"
	.align 8
.LC24:
	.string	"File size:                %lld bytes\n"
	.align 8
.LC25:
	.string	"Blocks allocated:         %lld\n"
.LC26:
	.string	"Last status change:       %d"
.LC27:
	.string	"Last file access:         %d"
.LC28:
	.string	"Last file modification:   %d"
	.text
	.globl	printstat
	.type	printstat, @function
printstat:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC14(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	40(%rbp), %eax
	andl	$61440, %eax
	cmpl	$49152, %eax
	je	.L23
	cmpl	$49152, %eax
	ja	.L24
	cmpl	$40960, %eax
	je	.L25
	cmpl	$40960, %eax
	ja	.L24
	cmpl	$32768, %eax
	je	.L26
	cmpl	$32768, %eax
	ja	.L24
	cmpl	$24576, %eax
	je	.L27
	cmpl	$24576, %eax
	ja	.L24
	cmpl	$16384, %eax
	je	.L28
	cmpl	$16384, %eax
	ja	.L24
	cmpl	$4096, %eax
	je	.L29
	cmpl	$8192, %eax
	je	.L30
	jmp	.L24
.L27:
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	jmp	.L31
.L30:
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
	jmp	.L31
.L28:
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	jmp	.L31
.L29:
	leaq	.LC15(%rip), %rdi
	call	puts@PLT
	jmp	.L31
.L25:
	leaq	.LC16(%rip), %rdi
	call	puts@PLT
	jmp	.L31
.L26:
	leaq	.LC5(%rip), %rdi
	call	puts@PLT
	jmp	.L31
.L23:
	leaq	.LC17(%rip), %rdi
	call	puts@PLT
	jmp	.L31
.L24:
	leaq	.LC18(%rip), %rdi
	call	puts@PLT
	nop
.L31:
	movq	24(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC19(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	40(%rbp), %eax
	movl	%eax, %eax
	movq	%rax, %rsi
	leaq	.LC20(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC21(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	48(%rbp), %eax
	movl	%eax, %edx
	movl	44(%rbp), %eax
	movl	%eax, %eax
	movq	%rax, %rsi
	leaq	.LC22(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	72(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC23(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	64(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC24(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	80(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC25(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	120(%rbp), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	ctime@PLT
	movl	%eax, %esi
	leaq	.LC26(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	88(%rbp), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	ctime@PLT
	movl	%eax, %esi
	leaq	.LC27(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	104(%rbp), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	ctime@PLT
	movl	%eax, %esi
	leaq	.LC28(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	printstat, .-printstat
	.section	.rodata
.LC29:
	.string	"Usage: %s <dirname>\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$192, %rsp
	movl	%edi, -180(%rbp)
	movq	%rsi, -192(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -168(%rbp)
	movl	$0, -164(%rbp)
	movl	$0, -176(%rbp)
	movl	$0, -172(%rbp)
	cmpl	$1, -180(%rbp)
	jg	.L33
	movq	-192(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC29(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$-1, %edi
	call	exit@PLT
.L33:
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L35
	call	__stack_chk_fail@PLT
.L35:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
