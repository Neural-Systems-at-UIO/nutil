REM echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64
REM set uploadScript=C:\Users\leuat\Documents\GitHub\uploadScript\upload_win_night.cmd

echo "Qmake.."
qmake Nutil.pro 
echo "Compiling.."
dir ..\Qt\Tools\
dir ..\Qt\Tools\QtCreator\bin
..\Qt\Tools\QtCreator\bin\jom.exe -f Makefile.Release

cd release
dir .
windeployqt.exe .

cd ..\Publish\publish_win
call PublishWindows.cmd
#call %uploadScript%
