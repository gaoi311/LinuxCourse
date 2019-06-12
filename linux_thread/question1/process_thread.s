	.file	"process_thread.c"
	.text
	.globl	x
	.bss
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.zero	4
	.text
	.globl	main
	.type	main, @function
main:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	call	fork@PLT
	movl	%eax, -20(%rbp)
	cmpl	$0, -20(%rbp)
	jne	.L2
	movl	x(%rip), %eax
	addl	$10, %eax
	movl	%eax, x(%rip)
	leaq	-16(%rbp), %rax
	leaq	x(%rip), %rcx
	leaq	thread_function1(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	movq	-16(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	jmp	.L3
.L2:
	movl	x(%rip), %eax
	addl	$50, %eax
	movl	%eax, x(%rip)
	leaq	-16(%rbp), %rax
	leaq	x(%rip), %rcx
	leaq	thread_function2(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	movq	-16(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
.L3:
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.string	"\033[1;31mthread_child_before\033[0m: n is \033[1;31m%d\033[0m\n"
	.align 8
.LC1:
	.string	"\033[1;31mthread_child_after\033[0m: n is \033[1;31m%d\033[0m\n, %p\n"
	.text
	.globl	thread_function1
	.type	thread_function1, @function
thread_function1:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leal	10(%rax), %ecx
	movq	-8(%rbp), %rax
	movq	%rax, %rdx
	movl	%ecx, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %edi
	call	pthread_exit@PLT
	.cfi_endproc
.LFE6:
	.size	thread_function1, .-thread_function1
	.section	.rodata
	.align 8
.LC2:
	.string	"\033[1;33mthread_parent_before\033[0m: n is \033[1;33m%d\033[0m\n"
	.align 8
.LC3:
	.string	"\033[1;33mthread_parent_after\033[0m: n is \033[1;33m%d\033[0m\n, %p\n"
	.text
	.globl	thread_function2
	.type	thread_function2, @function
thread_function2:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leal	50(%rax), %ecx
	movq	-8(%rbp), %rax
	movq	%rax, %rdx
	movl	%ecx, %esi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %edi
	call	pthread_exit@PLT
	.cfi_endproc
.LFE7:
	.size	thread_function2, .-thread_function2
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
