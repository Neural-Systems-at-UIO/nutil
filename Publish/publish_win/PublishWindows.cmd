rmdir /s /q nutil
set dir=C:\Users\leuat\Documents\GitHub\build-Nutil-Desktop_Qt_5_9_2_MSVC2017_64bit-Release\release
mkdir nutil
xcopy /s %dir%\*.exe nutil\
xcopy /s %dir%\iconengines nutil\
xcopy /s %dir%\platforms nutil\
xcopy /s %dir%\*.dll nutil\
xcopy /e ..\source\* nutil
