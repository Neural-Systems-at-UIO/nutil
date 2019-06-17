@ECHO OFF
IF exist nutil_win_beta.zip (
  .\7z x  nutil_win_beta.zip -aoa
  del nutil_win_beta.zip
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



