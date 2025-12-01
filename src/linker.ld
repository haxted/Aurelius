ENTRY(_start)

SECTIONS {
    . = 2M;
    __kernel_start = .;
    .text : ALIGN(4096) {
        __text_start = .;
        KEEP(*(.multiboot))
        *(.text)
        __text_end = .;
    }
    .rodata : ALIGN(4096) {
        __rodata_start = .;
        *(.rodata)
        __rodata_end = .;
    }
    .data : ALIGN(4096) {
        __data_start = .;
        *(.data)
        __data_end = .;
    }
    .bss : ALIGN(4096) {
        __bss_start = .;
        *(.bss)
        __bss_end = .;
        *(COMMON)
    }
   __kernel_end = .;
  
}