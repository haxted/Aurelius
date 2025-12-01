.global loadGdt

loadGdt:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    lgdt (%eax)
    mov $0x28, %ax
    ltr %ax
    movl %ebp, %esp
    popl %ebp
    ljmp $0x08, $relrg
    
relrg:
    movl $0x10, %eax
    movl %eax, %ds
    movl %eax, %es 
    movl %eax, %fs 
    movl %eax, %ss 
    ret