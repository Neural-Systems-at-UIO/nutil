import pandas as pd
import sys
import matplotlib.pyplot as plt
import numpy as np
import glob
import math
#from mpl_toolkits.mplot3d import proj3d
import matplotlib.ticker as mtick
from plot_lib import plot_all

# python3 plot_reference_atlas_regions.py [ nutil_output_dir ] [type]”
# where type = 0 is regular bars, type=1 is pie chart

if len(sys.argv)<2:
	print("Usage: python plot_reference_atlas_regions [nutil directory] [type] [parameters]")
	exit(1)


report_files = glob.glob(sys.argv[1]+"/**/*RefAtlasRegions.csv", recursive = True)
#report_files = glob.glob(sys.argv[1]+"/**/*RefAtlasRegions_*.csv", recursive = True)
atlas_files = glob.glob(sys.argv[1]+"/**/*.label", recursive = True)

doplot = True
outfile = 'ref_plot.png'

typ = 0
if (len(sys.argv)>=3):
	typ = int(sys.argv[2])
if (len(sys.argv)>3):
	for i in range(3,len(sys.argv)):
		s = sys.argv[i].lower()
		if (s=="-noplot"):
			doplot = False
		if ("-outfile=" in s):
			outfile = s.replace("-outfile=","")


color_map = {}

def load_labels(file):
	with open(file,'r') as f:
		for line in f:
			ol = line
			line = line.strip()
			if (not line.startswith("#")):
				line = line.replace("\"","").lower().split(",")[0]
				lst = line.split('\t')
				if (len(lst)==1): # Hack for WHS brains
					name = ol.split("\"")[1]
					line = ol.replace("\""+name+"\"","").strip()
					name = name.split(",")[0]
					lst = line.strip().split(' ')
					while("" in lst):
						lst.remove("")
						
					lst.append(name)					

#				print(lst)
#				print(len(lst))
				if len(lst)==8:
#					print(lst[7])
					color_map[lst[7]] = [float(lst[1])/256.0,float(lst[2])/256.0,float(lst[3])/256.0]

    

if len(report_files)==0:
	print("Could not find any reports to plot ")
	exit(1)

if len(atlas_files)==0:
	print("Could not find any atlas files ")
	exit(1)

load_labels(atlas_files[0])


#print(color_map)
#print(color_map["prepyramidal fissure"])


#print(report_files)

all_data = []
print("Loading...")
for r in report_files:
	df = pd.read_csv(r, sep=';')
	all_data.append(df)


plot_all(typ,all_data,color_map,outfile, doplot, True)
