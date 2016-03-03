@echo off
echo before running this bat file, you will need to run karma in a different process
echo "karma start"
echo.
echo This batfile does not check if karma has started.
echo Starting grading...

for /f %%f in ('dir /b ..\out\58677') do call grade %%f ..\out\58677 src\login LoginController.spec.js
