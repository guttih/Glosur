# Linux commands worth remembering#

### Lingo
Pid = process Id number = that is the Id of a running process  
`Ctrl-a` -> `c` =  `Ctrl-a` followed by `c`  
 
 ### Copy
 - `cp -avRf /mnt/* /tmp/rhel7` Copy all content of **/mnt** including hidden files and sub dirs into directory **/tmp/rhel7** and show progress
 
 ### List processes
- `ps -a` : List all process and theyr ID
- `ps -aux` : List all process and theyr ID and system processes
- `ps -Flww -p Pid` more details about a process
- `ps -a | grep node |awk '{print $1}'` list only pIDs of processes with node in the name
- `ps -a|grep node|awk '{print $1}'|xargs ps -Flww -p` details about all processes which have node in the name
- `netstat -tulpn | grep -f <(pgrep -a node | grep 'node app.js' | awk '{print $1}') ` list ports of all all node apps called "app.js"
- `netstat -tulpn|grep -f <(ps -a|grep node|awk '{print $1}'|xargs ps -Flww -p|grep "node app.js"|awk '{print $4}')` list ports not as elegant
- `PID=$(ps -aux|grep "node "|grep "/voffcon.js"|tr -s ' ' | cut -d' ' -f2);sudo kill $PID` Kill a process matching worlds `node ` and `/voffcon.js`




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

Tutorial [linux/make_bootable_usb.md](./linux/make_bootable_usb.md)

### Delete (Deltree)
 Delete all node folders and theyr content, recursivly
```shell
find . -type d -name node_modules -exec rm -rf {} \;
```
When a directory is deleted then the text `
 No such file or directory` will be displayed.

### Size on disk

to get the size of a directory type
```
du -h <path_to_dir>
```
 ### Search for files
 Finds all files with name that ends with .pdf
```shell
find .  -name "*.pdf"
```

#### Find with multiple search criteria

Search for all media except two directories for multiple files

```shell
find / ! -path "/media/*" !  -path "/root/db-config/*" -type f \( \
-name "tams-channel-config.xml" \
-o -name "tams-switch-config.xml" \
-o -name "tams-cidin-config.xml" \
-o -name "tams-gateway-config.xml" \
-o -name "tams-operator-config.xml" \
-o -name "tams-smtp-config.xml" \
-o -name "tams-amhs-config.xml" \
\) 2>/dev/null
```

#### Find with grep

Search all text files on computer for the text "192.168.52." 
but do not search directories */media* and */run*

```shell
find / ! -path "/run/*" ! -path "/media/*" -type f -exec grep -H "192.168.52." {} \; 2>/dev/null
```

Only show the filepath with matching content
```shell
find / ! -path "/run/*" ! -path "/media/*" -type f -exec grep -Hl "192.168.52." {} \; 2>/dev/null
```


This will search sub directories also

## Text manipulation

- [awk](https://www.grymoire.com/Unix/Awk.html)
- [sed](https://www.grymoire.com/Unix/Sed.html)
 
 
 
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
 
