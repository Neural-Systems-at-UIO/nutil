
rm -rf nutil
mkdir nutil
cp -r ../../Release/Nutil.app nutil/
cd nutil/Nutil.app
~/Qt/5.15.0/clang_64/bin/macdeployqt .
cd ../../
rm nutil.tar.gz
cp  -R ../source/* nutil
tar -cf nutil.tar nutil
gzip nutil.tar
