setfont /usr/share/consolefonts/Uni3-Terminus32x16.psf.gz

mkdir /mnt/boot
mount /dev/sda1 /mnt/boot

---------

cd /tmp
mkdir initrd
cd initrd
cp /mnt/boot/initrd.img-6.1.0-34-amd64 .
# mv initrd.img-6.1.0-34-amd64 initrd.img-6.1.0-34-amd64.gz
# cpio -idmv < initrd.img-6.1.0-34-amd64
unmkinitramfs initrd.img-6.1.0-34-amd64 initram

cd initram
vi main/scripts/init-top/cryptroot
