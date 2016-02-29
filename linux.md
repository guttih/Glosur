# Linux commands worth remembering#
 
 Delete all bower and node folders and theyr content, recursivly
```shell
find -type d -name node_modules -o -name bower_components -exec rm -rf {} \;
```
