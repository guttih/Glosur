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
   
## rpm

 -  `sudo find /var/cache/PackageKit/8/metadata/*/packages/ -name <rpm-file>` Quick search for a package
 - `rpm -qi <pacakge>` *query installed* Display installed information along with package version and short description
 - `rpm -ivh <rpm-file>` Install a rpm file
 - `rpm -Uvh <rpm-file>`	*Upgrade package*
 - `rpm --reinstall <rpm-file>`	*reinstall a package*
 - `rpm -ev <package>` 	Erase/remove/uninstall an installed package
 - `rpm -ev --nodeps <package>` *Erase*/remove/uninstall an installed package without checking for dependencies
 - `rpm -qf </path/to/file>` Which package a file belongs to i.e. find what package owns the file
 - ` rpm -qa` Display list all installed packages
 - `rpm -qa --last` 	Display list of all recently installed RPMs
 - `rpm -qpR <file.rpm>` Find out what dependencies a rpm file has
 - `rpm -qR <package>` Find out what dependencies a package has
 - query option
    ```
     -a, --all                         query/verify all packages
     -f, --file                         query/verify package(s) owning file
     -g, --group                        query/verify package(s) in group
     -p, --package                      query/verify a package file
         --pkgid                        query/verify package(s) with package
         --hdrid                        query/verify package(s) with header
         --triggeredby                  query the package(s) triggered by the
         --whatconflicts                query/verify the package(s) which require
         --whatrequires                 query/verify the package(s) which require
         --whatobsoletes                query/verify the package(s) which
         --whatprovides                 query/verify the package(s) which provide
         --whatrecommends               query/verify the package(s) which
         --whatsuggests                 query/verify the package(s) which
         --whatsupplements              query/verify the package(s) which
         --whatenhances                 query/verify the package(s) which
    ```
  
  [provides]: https://dnf.readthedocs.io/en/latest/command_ref.html#provides-command
  [module provides]: https://dnf.readthedocs.io/en/latest/command_ref.html#module-provide-command-label

 
 
