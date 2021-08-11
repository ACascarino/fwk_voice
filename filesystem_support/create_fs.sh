#!/bin/sh

# Get unix name for determining OS
UNAME=$(uname)

# Create an empty 1 MiB file
dd if=/dev/zero of=fat.fs bs=1024 count=1024

if [ "$UNAME" = "Linux" ] ; then
    MKFS_VFAT_PATH=/sbin
    sudo umount -q fat_mnt
elif [ "$UNAME" = "Darwin" ] ; then
    MKFS_VFAT_PATH=/usr/local/sbin
    hdiutil detach fat_mnt
fi

# Create an empty FAT filesystem in it
$MKFS_VFAT_PATH/mkfs.vfat -v -F12 -s1 -S4096 -n xcore_fs fat.fs

mkdir -p fat_mnt

# Mount the filesystem
if [ "$UNAME" = "Linux" ] ; then
    sudo mount -o loop fat.fs fat_mnt
elif [ "$UNAME" = "Darwin" ] ; then
    hdiutil attach -imagekey diskimage-class=CRawDiskImage -mountpoint fat_mnt fat.fs
fi

# Copy files into filesystem
sudo mkdir fat_mnt/ww
sudo cp "$WW_PATH/models/common/WR_250k.en-US.alexa.bin" fat_mnt/ww/250kenUS.bin
sudo cp "$WW_PATH/models/common/WS_50k.en-US.alexa.bin" fat_mnt/ww/50kenUS.bin

# Unmount the filesystem
if [ "$UNAME" = "Linux" ] ; then
    sudo umount fat_mnt
elif [ "$UNAME" = "Darwin" ] ; then
    hdiutil detach fat_mnt
fi

# Cleanup
sudo rm -rf fat_mnt
