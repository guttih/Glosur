# Linux commands worth remembering#

### lingo
Pid = process Id number
 
 
 ### List processes
- `ps -a` : List all process and theyr ID
- `ps -flWW -p Pid` more details about a process


### Delete (Deltree)
 Delete all node folders and theyr content, recursivly
```shell
find . -type d -name node_modules -exec rm -rf {} \;
```
When a directory is deleted then the text `
 No such file or directory` will be displayed.
