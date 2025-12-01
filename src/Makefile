CC = i686-elf-gcc
AS = i686-elf-as
ASFLAGS = -g
ASFILES = $(wildcard *.S)
CFILES = $(shell find . -type f -name "*.c")
CHDRS = $(wildcard include/*.h)
ASOBJS = $(patsubst %.S, ../build/%.S.o, $(ASFILES))
COBJS = $(patsubst %.c, ../build/%.c.o, $(CFILES))
NASMFILES = $(wildcard *.asm)
NASMOBJS = $(patsubst %.asm, ../build/%.asm.o, $(NASMFILES))
NASMFLAGS = -g -felf32
CFLAGS = -ffreestanding \
		 -nodefaultlibs -nostartfiles \
		 -mno-red-zone -fno-stack-protector \
		 -std=gnu99 -fno-pie \
		 -fno-PIC -I include/ \
		 -I . \
		 -mno-sse -mno-sse2 \
		 -O2 -g -c -fno-omit-frame-pointer
LD = i686-elf-ld
LDFLAGS = -T linker.ld -z noexecstack
OUTPUT = ../build/KERNEL


../build/%.c.o: %.c $(CHDRS)
	@mkdir -p "$$(dirname $@)"
	@$(CC) $(CFLAGS) $< -o $@
	@echo "CC    $@"
../build/%.S.o: %.S
	@$(AS) $(ASFLAGS) $< -o $@
	@echo "AS    $@"
../build/%.asm.o: %.asm
	@nasm $(NASMFLAGS) $< -o $@
	@echo "AS    $@"
../build/KERNEL: $(COBJS) $(ASOBJS) $(NASMOBJS)
	@$(LD) $(LDFLAGS) -o $@ $^
	@echo "LD    $@"
all: $(COBJS) $(ASOBJS) $(NASMOBJS) $(OUTPUT)