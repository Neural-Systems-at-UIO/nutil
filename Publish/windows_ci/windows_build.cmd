REM echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64

echo "Qmake.."
qmake Nutil.pro 
echo "Compiling.."
REM dir D:\a\nutil\Qt\Tools\QtCreator /s
REM jom.exe -f Makefile.Release
D:\a\nutil\Qt\Tools\QtCreator\bin\jom.exe -f Makefile.Release

dir .
cd Release
dir .
windeployqt.exe .

cd ..\Publish\publish_win
call PublishWindows.cmd
