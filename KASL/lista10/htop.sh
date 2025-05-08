#!/bin/bash

cd ~/Downloads
cp htop ~/myinitramfs/bin/htop

cd ~/myinitramfs
find . | cpio -o --format=newc | gzip > ../initramfs.cpio.gz
