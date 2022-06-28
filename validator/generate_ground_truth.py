import os
import sys
import shutil
import subprocess

nutil = sys.argv[1]

for dir in os.listdir("."):
    if not os.path.isfile(dir):
        print("************************** "+dir+" **************************************")
        if (os.path.exists(dir+"/correct")):
            print("Deleting old ground truth...")
            shutil.rmtree(dir+"/correct")
        if (os.path.isfile(dir+"/Out")):
            shutil.rmtree(dir+"/Out")
#        os.chdir(dir)
        subprocess.run([nutil,dir+"/batch.nut","4"])
        os.rename(dir+"/Out", dir+"/correct")        
 #       os.chdir("..")
