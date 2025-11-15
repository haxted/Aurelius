.section .multiboot
.set MAGIC, 0x1BADB002
.set FLAGS, (1 << 0) | (1 << 1)
.set CHECKSUM, -(MAGIC + FLAGS)
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stbtm: .skip 16384
stack:


.section .text
.global _start
_start:
    cli
    mov $stack, %esp
    cld
    pushl %ebx
    call kmain
    hlt
