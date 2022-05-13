# How to create a QT application

## On linux with Qt installed
1. Make a new folder called `test`
2. Cd into `test`
3. Create the file `test.cpp`
4. Copy copy paste the following into newly created `test.cpp`
  ```cpp

  #include <QApplication>
  #include <QPushButton>


  int main( int argc, char **argv )
  {
      QApplication a( argc, argv );

      QPushButton hello( "Hello world!", 0 );
      hello.resize( 100, 30 );

      hello.show();
      return a.exec();
  }

  ```
5. Create the project file by running command
  ```
  qmake -project
  ```
6. Add add the line `QT += widgets` to top of the newly created `test.pro` file.
7. Run following shell commands to make the executable
  ```shell
  qmake
  make
  ```
8. And finally run the program you just created with the command
   - Command to run
   ```
   ./test
   ```
   - This should open a small window called **Hello world!**

  - Alternatively you can do steps **5** to **8** all in one command
     ```shell
     qmake -project && echo 'QT += widgets' | cat - test.pro > temp && mv temp test.pro && qmake && make && ./test
     ```
  
  
