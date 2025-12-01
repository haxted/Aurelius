all:
	mkdir -p build/
	cd src && make all && cd ..
	mkdir -p isodir/boot/grub
	cp build/KERNEL isodir/boot/KERNEL
	cp boot/grub.cfg isodir/boot/grub/grub.cfg
	cp boot/init.tar isodir/boot/init.tar
	grub-mkrescue -o os.iso isodir
clean:
	rm -rf build