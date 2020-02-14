@echo off

if [%1]==[] goto usage

setlocal enableDelayedExpansion
FOR %%G IN (%1\*.nut) DO (
	@echo !DATE! !TIME!
	@echo Processing %%G
	nutil_program.exe %%G %2
	@echo %%G done.
)
@echo !DATE! !TIME!
@echo All .nut files processed. Have a nice day :)
goto :eof

:usage
@echo Run from nutil_program.exe folder ONLY!
@echo Usage: process_folder.bat intupt_folder number_of_threads
@echo Example: process_folder.bat Z:\HBP_Analytics\Nutil_Connectivity\PhD_Martin\Allen_connectivity\batch-test 4