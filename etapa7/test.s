	.file	"test.c"
	.comm	a,24,4
.globl b
	.data
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	5
	.comm	c,4,4
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$15, a+20
	jmp	.L2
.L3:
	movl	b, %eax
	subl	$1, %eax
	movl	%eax, b
.L2:
	movl	a+20, %edx
	movl	b, %eax
	cmpl	%eax, %edx
	jg	.L3
	popl	%ebp
	ret
	.size	main, .-main
.globl babaca
	.type	babaca, @function
babaca:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.size	babaca, .-babaca
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
