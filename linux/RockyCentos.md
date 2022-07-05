# Centos / Rocky linux

RedHat based distros like fedora, centos and Rocky

## Fix Invalid urls in Centos 8

```
sed -i 's/^mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-*
sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*
```


## dnf
 - `dnf provides <provide-spec>` [provides] Finds the packages providing the given <provide-spec>. This is useful when one knows a filename and wants to find what package (installed or not) provides this file. The <provide-spec> is gradually looked for at following locations:
 - `dnf module provides <package-name-spec>` [module provides] Lists all modular packages matching <package-name-spec> from all modules (including disabled), along with the modules and streams they belong to.
  
  
  
  
  [provides]: https://dnf.readthedocs.io/en/latest/command_ref.html#provides-command
  [module provides]: https://dnf.readthedocs.io/en/latest/command_ref.html#module-provide-command-label
