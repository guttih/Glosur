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

### Delete (Deltree)
 Delete all node folders and theyr content, recursivly
```shell
find . -type d -name node_modules -exec rm -rf {} \;
```
When a directory is deleted then the text `
 No such file or directory` will be displayed.
 
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
 
