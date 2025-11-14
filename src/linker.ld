ENTRY(_start)

SECTIONS {
    . = 2M;
    .text : {
        KEEP(*(.multiboot))
        *(.text)
    }
    .rodata : {
        *(.rodata)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
        *(COMMON)
    }
   
  
}