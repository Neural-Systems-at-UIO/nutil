@echo off

PBUILD /G
Pause
del *.exe
del *.obj
del obj /q
cls
echo.
pbuild.exe project.xpj /dDEBUG=NO /A 
if errorlevel==1 goto Fehler
goto ende
:Fehler
echo.
echo FEHLER !
:Ende
pause
del *.res
del *.obj
del *.bak
del backups /q
rd backups
del obj /q
rd obj
del XPP*.log


