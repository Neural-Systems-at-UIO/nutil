
rm -rf nutil
mkdir nutil
cp -r ../../../NutilRelease/Nutil.app nutil/
cd nutil/Nutil.app
~/Qt/6.4.2/macos/bin/macdeployqt .
rm Contents/Frameworks/libtiff.5.dylib
#cp /opt/homebrew/opt/libomp/lib/libomp.dylib nutil/Nutil.app/Contents/Frameworks
rm Contents/Frameworks/libomp.dylib
cd ../../
rm nutil.tar.gz
cp  -R ../source/* nutil
hdiutil create -volname Nutil -srcfolder nutil/ -ov -format UDZO nutil_0.8.1.dmg

