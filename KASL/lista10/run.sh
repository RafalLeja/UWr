#!/bin/bash
qemu-system-x86_64 -kernel /boot/vmlinuz-6.1.0-34-amd64 \
 -initrd ~/initramfs.cpio.gz -nographic -append "console=ttyS0"
