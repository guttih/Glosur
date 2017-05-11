# Linux commands worth remembering#
 
 Delete all node folders and theyr content, recursivly
```shell
find . -type d -name node_modules -exec rm -rf {} \;
```
When a directory is deleted then the text `
 No such file or directory` will be displayed.

