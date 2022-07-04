# CMake notes

- See [Tutorial] for good information on how to use CMake with C++ see [Tutorial files] for the code in steps.

## CMake commands

Cd into the root of your project and create the build directory, it should  be a sibling to the top *CMakeLists.txt* file.
```
  mkdir build
  cd build
```
All commands below assume you are located in the **build directory**

- **Build** project for the first time, this should give you the **executable** to run
  ```
  cmake --build .
  make
  ls
  ```
- **Change options** of your project from the build directory with eather `ccmake .` or `cmake-gui .`
- **Install** with `cmake --install .` alternatively to install to a different location do `cmake --install . --prefix "/home/myuser/installdir"`
- **Uninstalling** an installed CMake (make install) package.  If you have the access to the *install_manifest.txt* file you can delete all installed files with the command below command:       [source]
  ```
  xargs rm < install_manifest.txt
  ```
- **Create package** Package your project [more info here].
  ```
  cpack
  ```

 
  
[more info here]: https://cmake.org/cmake/help/latest/guide/tutorial/Packaging%20an%20Installer.html
[source]: https://stackoverflow.com/questions/41471620/cmake-support-make-uninstall#answer-44649542
[Tutorial]: https://cmake.org/cmake/help/latest/guide/tutorial/index.html#
[Tutorial files]: https://gitlab.kitware.com/cmake/cmake/-/tree/master/Help/guide/tutorial
