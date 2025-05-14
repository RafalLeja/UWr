butloader.bin: butloader.asm
	nasm -f bin butloader.asm -o butloader.bin

send: butloader.bin
	sudo dd if=/dev/sda of=mbr_full.bin bs=512 count=1
	sudo dd if=butloader.bin of=mbr_full.bin bs=1 count=446 conv=notrunc
	sudo dd if=mbr_full.bin of=/dev/sda bs=512 count=1 conv=notrunc

run: send
	sudo qemu-system-x86_64 -enable-kvm -m 1024 -drive file=/dev/sda,format=raw
