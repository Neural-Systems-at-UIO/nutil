import os
import sys
import shutil
import subprocess


for dir in os.listdir("."):
    if not os.path.isfile(dir):
        print("************************** "+dir+" **************************************")
        if (os.path.exists(dir+"/Out")):
            shutil.rmtree(dir+"/Out")
