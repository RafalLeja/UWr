#!/bin/bash
mkdir -p ~/myinitramfs/{bin,sbin,etc,proc,sys,usr/bin,usr/sbin,dev}
cd ~/myinitramfs

cp /bin/busybox ~/myinitramfs/bin/

cd ~/myinitramfs/bin
for applet in $(./busybox --list); do ln -s busybox $applet; done

cd ~/myinitramfs
cat > init << 'EOF'
#!/bin/sh

mount -t proc none /proc
mount -t sysfs none /sys
mount -t devtmpfs none /dev

echo "Witaj użytkowniku!"

exec /bin/sh
EOF

chmod +x init

cd ~/myinitramfs
find . | cpio -o --format=newc | gzip > ../initramfs.cpio.gz

