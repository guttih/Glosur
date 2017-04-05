@echo off
 set timi=%DATE:~-4%%DATE:~-7,2%%DATE:~-10,2%%TIME:~0,2%%TIME:~3,2%%TIME:~6,2%
 set timi=%timi: =0%
 set zippath=C:\Users\gudjonhs\Documents\DeploymentKreditkort%timi%.zip
 echo hef afritun %timi%
 if exist %zippath% del %zippath%
@echo on

call "C:\scripts\CopyViews.bat" "C:\tfssrc\Web\dev\Kreditkort\Kreditkort" "C:\DeploymentKreditkort"

del C:\DeploymentKreditkort\Mvc\Views\_ViewStart.cshtml
del C:\DeploymentKreditkort\Views\_ViewStart.cshtml
zip %zippath% C:\DeploymentKreditkort/*.* -r -S
set timi=
set zippath=
explorer "C:\Users\gudjonhs\Documents"
pause
