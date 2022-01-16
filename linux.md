# Linux commands worth remembering#

### Lingo
Pid = process Id number = that is the Id of a running process  
`Ctrl-a` -> `c` =  `Ctrl-a` followed by `c`  
 
 
 ### List processes
- `ps -a` : List all process and theyr ID
- `ps -aux` : List all process and theyr ID and system processes
- `ps -Flww -p Pid` more details about a process
- `ps -a | grep node |awk '{print $1}'` list only pIDs of processes with node in the name
- `ps -a|grep node|awk '{print $1}'|xargs ps -Flww -p` details about all processes which have node in the name
- `netstat -tulpn | grep -f <(pgrep -a node | grep 'node app.js' | awk '{print $1}') ` list ports of all all node apps called "app.js"
- `netstat -tulpn|grep -f <(ps -a|grep node|awk '{print $1}'|xargs ps -Flww -p|grep "node app.js"|awk '{print $4}')` list ports not as elegant




## Screen
`screen` -> `Enter` start the program screeen
`Ctrl-a` -> `c`: create a new windows  
`Ctrl-a` -> `w`: display the list of all the windows currently opened  
`Ctrl-a` -> `A`: rename the current windows. The name will appear when you will list the list of windows opened with Ctrl-a followed by w.  
`Ctrl-a` -> `n`: go to the next windows  
`Ctrl-a` -> `p`: go to the previous windows  
`Ctrl-a` -> `Ctrl-a`: back to the last windows used.  
`Ctrl-a` -> a number from 0 to X: go the windows n° X.  
`Ctrl-a` -> `"`: choose the windows into which to move on.  
`Ctrl-a` -> `k`: close the current windows (kill)  
`Ctrl-a` -> `S`: (capital s) split the current windows horizontally. To switch between the windows, do Ctrl-a followed by Tab.  
`Ctrl-a` -> `|`: split the current windows vertically  
`Ctrl-a` -> `d`: detach a screen session without stopping it  
`Ctrl-a` -> `r`: reattach a detached screen session  
`Ctrl-a` -> `[`: start the copy mode  
`Ctrl-a` -> `]`: paste the copied texte  

### Make a bootable USB drive
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
   sudo dd bs=4M if=~/Downloads/CentOS-Stream-9-latest-x86_64-dvd1.iso of=/dev/sdb status=progress oflag=sync
   sudo 
   ```
   When the command finishes, you should have a bootable OS installation disk.
5. Insert the bootable OS installation USB into the computer you want to install the OS on
6. Turn on the computer (this should run the OS installation process)
   - If the OS installation process does not start 
      I.  You will need to change the boot order in you BIOS so that the USB drive is first in the boot order.
      II. Turn you computer off, and then off again

### Delete (Deltree)
 Delete all node folders and theyr content, recursivly
```shell
find . -type d -name node_modules -exec rm -rf {} \;
```
When a directory is deleted then the text `
 No such file or directory` will be displayed.
 
 ### Search for files
 Finds all files with name that ends with .pdf
```shell
find .  -name "*.pdf"
```
This will search sub directories also
 
 
 
 ### Connections
 ## nc command
`nc -vz {host} {port}`  
`nc -vz 192.168.2.254 80` 
`nc -vz www.cyberciti.biz 443`
## nmap command
`nmap -PNp {port} {host}`  
`nmap -p {port} {host}`  
`nmap -p 22 www.cyberciti.biz`  
`nmap -p 443 192.168.2.254`  
 
