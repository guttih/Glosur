# CMake notes

- See [Tutorial] for good information on how to use CMake with C++ see [Tutorial files] for the code in steps.

## CMake commands

- Build project for the first time, this should give you the executable to run
  ```
  mkdir build
  cd build
  cmake --build .
  make
  ls
  ```
- Uninstalling an installed CMake (make install) package.  If you have the access to the *install_manifest.txt* file you can delete all installed files with this command:
  ```
  xargs rm < install_manifest.txt
  ```
  [Uninstall answer]

[Uninstall answer]: https://stackoverflow.com/questions/41471620/cmake-support-make-uninstall#answer-44649542
[Tutorial]: https://cmake.org/cmake/help/latest/guide/tutorial/index.html#
[Tutorial files]: https://gitlab.kitware.com/cmake/cmake/-/tree/master/Help/guide/tutorial
