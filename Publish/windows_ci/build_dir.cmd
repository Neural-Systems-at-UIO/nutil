rmdir /s /q nutil
set dir=release
mkdir nutil
mkdir nutil\program
xcopy /s %dir%\*.exe nutil\program
xcopy /s %dir%\iconengines nutil\program
xcopy /s %dir%\platforms nutil\program
xcopy /s %dir%\*.dll nutil\program
xcopy /e Publish\source\* nutil
xcopy Publish\publish_win\Nutil.cmd nutil\
xcopy version.txt nutil\program
xcopy version.txt nutil
REM xcopy 7z.exe nutil\
xcopy /e Publish\publish_win\dll\* nutil\program
move nutil\program\nutil.exe nutil\program\nutil_program.exe


