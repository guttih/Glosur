@echo off
setlocal enableextensions enabledelayedexpansion
rem set gradingDir=..\out\58677
rem set gradingCopyToDir=\src\login
rem set gradingCopyToDir=\src\login
rem set gradingFile=LoginController.spec.js
set submission=%1
set gradingDir=%2
set gradingCopyToDir=%3
set gradingFile=%4
set editor="C:\Program Files (x86)\Microsoft VS Code\Code.exe"

if %1x==x goto help
if /I %1==-h goto help
if /I %1==/? goto help
if /I %1==-help goto help
if /I %1==/help goto help

if /I %1==dir (
	echo diring
	dir %gradingDir%
	goto end)
if %2x==x (
	echo parameter 2 is missing
	echo You must supply the rootdir of all submissions
	goto help
)
if %3x==x (
	echo parameter 3 is missing
	echo You must supply where to copy the grading file to
	goto help
)
if %4x==x (
	echo parameter 4 is missing
	echo You must supply the name of the file to grade
	goto help
)

:goOn
	echo ------------ gradingDir %submission% ------------ 
	if NOT exist "%gradingDir%\." (
		echo - - - - -  E R R O R  gradingDir not found  - - - - - - 
		echo The Directory "%gradingDir%" does not exist
		goto endPause
	)
	if NOT exist "%gradingDir%\%submission%\." (
		echo - - - - -  E R R O R  submission directory not found  - - - - - - 
		echo The Directory "%gradingDir%\%submission%" does not exist
		goto endPause
	)
	if NOT exist "%gradingCopyToDir%\." ( 
		echo - - - - -  E R R O R  gradingCopyToDir not found  - - - - - - 
		echo The Directory "%gradingCopyToDir%" does not exist
		goto endPause)
	if NOT exist "%gradingDir%\%submission%\%gradingFile%" (
		echo - - - - -  E R R O R  FILE not found  - - - - - - 
		echo the file "%gradingDir%\%submission%\%gradingFile%"
		echo does not exist, this is the directory content
		dir "%gradingDir%\%submission%" /w
		goto endPause)
	
	
	if exist "%gradingCopyToDir%\%gradingFile%" del "%gradingCopyToDir%\%gradingFile%"
	if exist coverage/. (
		echo Cleaning coverage folder
		del /q /s coverage\*.*
	)
	timeout 1
	::copying the file from student
	xcopy "%gradingDir%\%submission%\%gradingFile%" "%gradingCopyToDir%"
	if errorlevel 1 (
		echo - - - - -  E R R O R  copying the file "%gradingFile%" "%gradingCopyToDir%"   - - - - - -
		echo Waiting for karma to recover after file change
		goto end
	)
	::Waiting for Karma and yasmin to create a report
	timeout 1
	::All is OK so let's start grading
	                                                                                                                                                                                                 
	::"C:\Program Files (x86)\Google\Chrome\Application\chrome.exe" "C:\skoli\VefII\WEEK 7 - PRACTICAL SESSION\UnitTestLoginKarma\coverage\Chrome 48.0.2564 (Windows 10 0.0.0)\/src/app.js.html"
	::"C:\Program Files (x86)\Microsoft VS Code\Code.exe" "%gradingDir%\%submission%\%gradingFile%"
	::"C:\Program Files (x86)\Microsoft VS Code\Code.exe" "%gradingDir%\%submission%\-1-einkunn.txt"
	call grunt jshint
	
	::Find files to view while grading
	set gradeViewFiles=
	for /f %%f in ('dir /b "%gradingDir%\%submission%\*.js"')           do (set gradeViewFiles=!gradeViewFiles! "%gradingDir%\%submission%\%%f ") 
	for /f %%f in ('dir /b "%gradingDir%\%submission%\-*-einkunn.txt"') do (set gradeViewFiles=!gradeViewFiles! "%gradingDir%\%submission%\%%f ") 	
	%editor% %gradeViewFiles%
	goto endPause

	
:help
	echo ----- Help on how to use this batfile -----
	echo You must provide 4 parameters with %0
	echo    1: submission (Submission number of the group)
	echo    2: gradingDir (The rootdir of all submissions)
	echo    3: gradingCopyToDir (Where to copy the grading file to)
	echo    4: gradingFile (name of the file to grade)
	echo    Do not have spaces in parameternames and no quotations
	echo.	
	echo example 1: Setup for gradingDir an assignment 1391751
	echo    %0 1391751 ..\out\58677 \src\login LoginController.spec.js
	echo.
	echo example 2: list the gradingDir
	echo    %0 dir .\out\58677
	goto end
	
:endPause
	pause
:end
:: Removing temorary variables
	set submission
	set gradingDir=
	set gradingCopyToDir=
	set gradingFile=
	set editor=
	set gradeViewFiles=
