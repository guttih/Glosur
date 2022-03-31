# Formatting USB
## Make a bootable USB drive
This tutorial describes how to create a bootable USB operating system disk. 
I selected the [Centos Stream 9](https://www.centos.org/centos-stream/) to setup. This manual is based on information from this [page](https://linuxize.com/post/how-to-create-a-bootable-centos-7-usb-stick-on-linux/).
1. Start by downloading the ISO for the operating system you want to install
  - In this example the ISO was downloaded to:`~/Downloads/CentOS-Stream-9-latest-x86_64-dvd1.iso`
2. Insert the USB drive
3.  Print device directory tree to find device path to your inserted USB drives
    I. Give this command
       ```shell 
       lsblk
       ```
  
    II. Example of output (We will be using **sdb1** in this example)
    ```
     NAME        MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
     sda           8:0    0   1.8T  0 disk 
     └─sda1        8:1    0   1.8T  0 part /run/media/gudjon/Transcend
     sdb           8:16   1  29.7G  0 disk 
     └─sdb1        8:17   1  29.7G  0 part /run/media/gudjon/SCANDISK
     nvme0n1     259:0    0   477G  0 disk 
     ├─nvme0n1p1 259:1    0   600M  0 part /boot/efi
     ├─nvme0n1p2 259:2    0     1G  0 part /boot
     └─nvme0n1p3 259:3    0 475.4G  0 part 
       ├─cs-root 253:0    0    70G  0 lvm  /
       ├─cs-swap 253:1    0  15.6G  0 lvm  [SWAP]
       └─cs-home 253:2    0 389.7G  0 lvm  /home
     ```
4. Unmount the the device and flash the iso with the dd command
   ```shell 
   sudo umount /dev/sdb1
   sudo dd bs=4M  status=progress oflag=sync of=/dev/sdbif=~/Downloads/CentOS-Stream-9-latest-x86_64-dvd1.iso
   sudo 
   ```
   When the command finishes, you should have a bootable OS installation disk.
5. Insert the bootable OS installation USB into the computer you want to install the OS on
6. Turn on the computer (this should run the OS installation process)
   - If the OS installation process does not start 
      I.  You will need to change the boot order in you BIOS so that the USB drive is first in the boot order.
      II. Turn you computer off, and then off again

## Changing filesystem
Changing or creating a new file system on a device.

*Note, In this example we are using **sdb1** as an example device.  Be carefule you are using the correct device.*

```
df -Th # or use lsblk
umount /dev/sdb1
```
Select one of the following file system.  (prefferred is fat32)
sudo mkfs.ext3 -m 0 /dev/sdb1
 - To format a USB drive with FAT32     file system run: `sudo mkfs.vfat /dev/sdb1`
 - To format a USB drive using the NTFS file system run: `sudo mkfs.ntfs /dev/sdb1`
 - To format a USB drive in accordance with the exFAT file system use: `sudo mkfs.exfat /dev/sdb1`
 - To format a USB drive in accordance with ext4 file system use: `sudo mkfs.ext4 /dev/sdb1`

