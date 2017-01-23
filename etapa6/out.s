.globl .5
	.data
	.align 4
	.type .5,@object
	.size .5, 4
.5:
	 .long 5
.globl .9
	.data
	.align 4
	.type .9,@object
	.size .9, 4
.9:
	 .long 9
.globl .1
	.data
	.align 4
	.type .1,@object
	.size .1, 4
.1:
	 .long 1
.globl .a
	.data
	.align 4
	.type .a,@object
	.size .a, 4
.a:
	 .long 0
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
.comm .c,3,1
.globl .boa
	.data
	.align 4
	.type .boa,@object
	.size .boa, 4
.boa:
	 .long 0
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
	.align 1
	.type ..TempValue0,@object
	.size ..TempValue0, 1
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
	movl $.LC0, %eax
	movl $.b, 4(%esp)
	movl %eax, (%esp)
	call __isoc99_scanf
	movl .1, %eax
	movl .9, %ebx
	movl %ebx, .c(,%eax,4)
.TempLabel4:
	movl .b, %edx
	movl .5, %eax
	cmpl %eax, %edx
	jne .LABELJNE0
	movl $0, %eax
	jmp .LABELJNEEND0
.LABELJNE0:
	movl $1, %eax
.LABELJNEEND0:
	movl %eax, ..TempValue0
	movl ..TempValue0, %eax
	testl %eax,%eax
	jz .TempLabel5
	movl (.c+4), %eax
	movl %eax, ..TempValue2
	movl ..TempValue2, %edx
	movl $.LC0, %eax
	movl %edx, 4(%esp)
	movl %eax, (%esp)
	call printf
	movl .b, %eax
	sub .1, %eax
	movl %eax, ..TempValue1
	movl ..TempValue1, %eax
	movl %eax, .b
	movl .b, %edx
	movl $.LC0, %eax
	movl %edx, 4(%esp)
	movl %eax, (%esp)
	call printf
	movl .1, %eax
	movl %eax, .boa
	call func
	movl %eax, ..TempValue3
	movl ..TempValue3, %eax
	movl %eax, .a
	movl .a, %edx
	movl $.LC0, %eax
	movl %edx, 4(%esp)
	movl %eax, (%esp)
	call printf
	jmp .TempLabel4
.TempLabel5:
	movl .b, %edx
	movl $.LC0, %eax
	movl %edx, 4(%esp)
	movl %eax, (%esp)
	call printf
	leave
	popl %ebp
	ret

.globl func
	.type func,@function
func:
	pushl %ebp
	movl %esp, %ebp
	andl $-16, %esp
	subl $16, %esp
	movl .boa, %edx
	movl $.LC0, %eax
	movl %edx, 4(%esp)
	movl %eax, (%esp)
	call printf
	leave
	popl %ebp
	ret
