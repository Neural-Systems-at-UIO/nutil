import pandas as pd
import sys
import matplotlib.pyplot as plt
import numpy as np
import glob
import math
#from mpl_toolkits.mplot3d import proj3d
import matplotlib.ticker as mtick
from plot_lib import plot_all



if len(sys.argv)<2:
	print("Usage: python plot_reference_atlas_regions [nutil directory] [type] [parameters]")
	exit(1)


report_files = glob.glob(sys.argv[1]+"/**/*CustomRegions_All.csv", recursive = True)
#report_files = glob.glob(sys.argv[1]+"/**/*RefAtlasRegions_*.csv", recursive = True)
colour_file = glob.glob(sys.argv[1]+"/**/custom_report_colors.csv", recursive = True)

doplot = True
outfile = 'custom_regions.png'

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

def load_colours(file):
	csv = pd.read_csv(file, sep='\t')
	names = csv['name']
	cols = csv['colour']
	for i in range(0,len(names)):
		c = cols[i]
		lst = c.split(";")
#		print(names[i].lower())
		color_map[names[i].lower()] = [float(lst[0])/256.0,float(lst[1])/256.0,float(lst[2])/256.0]; 

    

if len(report_files)==0:
	print("Could not find any reports to plot ")
	exit(1)

if len(colour_file)==0:
	print("Could not find any atlas files ")
	exit(1)


load_colours(colour_file[0])

all_data = []
print("Loading...")
for r in report_files:
	df = pd.read_csv(r, sep=';')
	all_data.append(df)



plot_all(typ,all_data,color_map,outfile, doplot, False)



