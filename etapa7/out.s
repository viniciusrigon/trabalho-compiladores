.globl .5
	.data
	.align 4
	.type .5,@object
	.size .5, 4
.5:
	 .long 5
.globl .1
	.data
	.align 4
	.type .1,@object
	.size .1, 4
.1:
	 .long 1
.globl .b
	.data
	.align 4
	.type .b,@object
	.size .b, 4
.b:
	 .long 0
.globl .3
	.data
	.align 4
	.type .3,@object
	.size .3, 4
.3:
	 .long 3
.comm .c,12,4
.globl ..TempValue3
	.data
	.align 4
	.type ..TempValue3,@object
	.size ..TempValue3, 4
..TempValue3:
	 .long 0
.globl ..TempValue2
	.data
	.align 4
	.type ..TempValue2,@object
	.size ..TempValue2, 4
..TempValue2:
	 .long 0
.globl ..TempValue1
	.data
	.align 4
	.type ..TempValue1,@object
	.size ..TempValue1, 4
..TempValue1:
	 .long 0
.globl ..TempValue0
	.data
	.align 4
	.type ..TempValue0,@object
	.size ..TempValue0, 4
..TempValue0:
	 .long 0
.LC0: 
	.string "%d"
	.text

.globl main
	.type main,@function
main:
	pushl %ebp
	movl %esp, %ebp
	andl $-16, %esp
	subl $16, %esp
	movl .c+4, %eax
	movl %eax, ..TempValue1
	movl .1, %eax
	movl %eax, ..TempValue1
	movl .c+4, %eax
	movl %eax, ..TempValue2
	movl .5, %eax
	add ..TempValue2, %eax
	movl %eax, ..TempValue0
	movl ..TempValue0, %eax
	movl %eax, .b
	movl .c+4, %eax
	movl %eax, ..TempValue3
	movl ..TempValue3, %edx
	movl $.LC0, %eax
	movl %edx, 4(%esp)
	movl %eax, (%esp)
	call printf
	leave
	ret
