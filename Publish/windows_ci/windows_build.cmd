REM echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64

echo "Qmake.."
qmake Nutil.pro 
echo "Compiling.."
REM dir D:\a\nutil\Qt\Tools\QtCreator /s
REM dir D:\a\nutil\ /s
REM dir .
REM jom.exe -f Makefile.Release
D:\a\nutil\Qt\Tools\QtCreator\bin\jom\jom.exe -f Makefile.Release
REM D:\a\nutol\Qt\Tools\QtCreator\bin\jom\jom.exe -f Makefile.Release


REM dir .
cd Release
REM dir .
windeployqt.exe .

REM cd ..\Publish\publish_win
REM call PublishWindows.cmd
