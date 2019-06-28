rmdir /s /q nutil
set dir=C:\Users\nicolaag\Documents\GitHub\build-Nutil-Desktop_Qt_5_12_3_MSVC2017_64bit-Release\release
mkdir nutil
mkdir nutil\program
xcopy /s %dir%\*.exe nutil\program
xcopy /s %dir%\iconengines nutil\program
xcopy /s %dir%\platforms nutil\program
xcopy /s %dir%\*.dll nutil\program
xcopy /e ..\source\* nutil
xcopy Nutil.cmd nutil\
xcopy 7z.exe nutil\
xcopy /e dll\* nutil\program
move nutil\program\nutil.exe nutil\program\nutil_program.exe


