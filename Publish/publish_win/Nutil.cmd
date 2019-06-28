@ECHO OFF
IF exist nutil_win.zip (
  .\7z x  nutil_win.zip -aoa
  del nutil_win.zip
  xcopy /Y /E nutil\* .
  del /S /Q nutil

  IF exist program\nutil.exe (
    move program\nutil.exe program\nutil_program.exe
  )
 ) ELSE (
 program\nutil_program.exe
 if errorlevel 1 (
   nutil.cmd
   program\nutil_program.exe
 )
)



