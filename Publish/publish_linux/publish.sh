rm -rf nutil
mkdir nutil/
cp -r ../../Release/Nutil nutil/nutil
cp -r lib/* nutil
#cp -r ../../Release/plugins trse/bin
cp -r plugins nutil

tar -cvf nutil_linux64.tar nutil
gzip nutil_linux64.tar
scp nutil_linux64.tar.gz leuat@www.irio.co.uk:www.irio.co.uk/div/nutil_linux64.tar.gz

