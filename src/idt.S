.global idtStubTable
.global loadIdt

.macro exceptionNoErr num
    .global exceptionStub\num
    exceptionStub\num:
        pushal
        call mainExceptionHandler
        popal
        subl $4, %eax
        iretl
.endm

.macro exceptionErr num
    .global exceptionStub\num
    exceptionStub\num:
        pushal
        call mainExceptionHandler
        popal
        iretl
.endm



exceptionNoErr 0
exceptionNoErr 1
exceptionNoErr 2
exceptionNoErr 3
exceptionNoErr 4
exceptionNoErr 5
exceptionNoErr 6
exceptionNoErr 7
exceptionErr 8
exceptionNoErr 9
exceptionErr 10
exceptionErr 11
exceptionErr 12
exceptionErr 13
exceptionErr 14
exceptionNoErr 15
exceptionNoErr 16
exceptionErr 17
exceptionNoErr 18
exceptionNoErr 19
exceptionNoErr 20
exceptionErr 21
exceptionNoErr 22
exceptionNoErr 23
exceptionNoErr 24
exceptionNoErr 25
exceptionNoErr 26
exceptionNoErr 27
exceptionNoErr 28
exceptionNoErr 29
exceptionNoErr 30
exceptionNoErr 31

.macro defstub num
    .long exceptionStub\num
.endm

idtStubTable:
.irp i, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    defstub \i
.endr

loadIdt:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    lidt (%eax)
    sti

    movl %ebp, %esp
    popl %ebp 
    ret

mainExceptionHandler:
    ret