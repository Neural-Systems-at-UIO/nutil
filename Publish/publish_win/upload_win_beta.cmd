del nutil\nutil.cmd
copy nutil_beta.cmd nutil\nutil.cmd
del nutil.zip
7z a nutil.zip nutil
pscp nutil.zip leuat@www.irio.co.uk:www/med/nutil/nutil_win_beta.zip
