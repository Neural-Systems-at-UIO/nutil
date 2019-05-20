@ECHO OFF
IF exist nutil_win.zip (
  .\7z e  nutil_win.zip -aoa
  del nutil_win.zip
  IF exist nutil.exe (
    move nutil.exe nutil_program.exe
  )
 ) ELSE (
 nutil_program.exe
 if errorlevel 1 (
   nutil.cmd
   nutil_program.exe
 )
)



