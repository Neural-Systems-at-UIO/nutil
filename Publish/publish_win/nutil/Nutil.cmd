@ECHO OFF
IF exist nutil_win_beta.zip (
  .\7z e  nutil_win_beta.zip -aoa
  del nutil_win_beta.zip
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



