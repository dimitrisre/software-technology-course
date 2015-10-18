	.file	"sum.c"
	.version	"01.01"
.globl n
	.data
	.align 4
	.type	n, @object
	.size	n, 4
n:
	.long	1000
.globl Sum
	.bss
	.align 4
	.type	Sum, @object
	.size	Sum, 4
Sum:
	.zero	4
	.section	.rodata
.LC0:
	.string	"The sum from 0 to %d is %d\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	subl	%eax, %esp
.L2:
	cmpl	$0, n
	js	.L3
	movl	n, %eax
	addl	%eax, Sum
	decl	n
	jmp	.L2
.L3:
	subl	$4, %esp
	pushl	Sum
	pushl	$1000
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 3.4.0"
