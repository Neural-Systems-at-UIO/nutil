@echo off
del *.exe
del *.obj
cls
pbuild /g
pause
pbuild /a
pause
vx20 test2.exe