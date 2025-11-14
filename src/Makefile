CC = i686-elf-gcc
AS = i686-elf-as
ASFLAGS = -g
ASFILES = $(wildcard *.S)
CFILES = $(wildcard *.c)
CHDRS = $(wildcard include/*.h)
ASOBJS = $(patsubst %.S, ../build/%.S.o, $(ASFILES))
COBJS = $(patsubst %.c, ../build/%.c.o, $(CFILES))
CFLAGS = -ffreestanding \
		 -nodefaultlibs -nostartfiles \
		 -mno-red-zone -fno-stack-protector \
		 -std=gnu99 -fno-pie \
		 -fno-PIC -I include/ \
		 -mno-sse -mno-sse2 \
		 -O2 -g -c
LD = i686-elf-ld
LDFLAGS = -T linker.ld -z noexecstack
OUTPUT = ../build/KERNEL


../build/%.c.o: %.c $(CHDRS)
	$(CC) $(CFLAGS) $< -o $@
../build/%.S.o: %.S
	$(AS) $(ASFLAGS) $< -o $@
../build/KERNEL: $(COBJS) $(ASOBJS)
	$(LD) $(LDFLAGS) -o $@ $^
all: $(COBJS) $(ASOBJS) $(OUTPUT)