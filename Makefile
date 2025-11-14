all:
	mkdir -p build/
	cd src && make all && cd ..
	mkdir -p isodir/boot/grub
	cp build/KERNEL isodir/boot/KERNEL
	cp boot/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o os.iso isodir
