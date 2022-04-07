import pandas as pd
import sys
import matplotlib.pyplot as plt
import numpy as np
import glob
import math
import matplotlib.ticker as mtick
import json
import numpy as np
import plotly.graph_objects as go

# python3 plot_reference_atlas_regions.py [ nutil_output_dir ] [type]”
# where type = 0 is regular bars, type=1 is pie chart

if len(sys.argv)<2:
	print("Usage: python plot_reference_atlas_regions [nutil directory] [type] [parameters]")
	exit(1)


data_files = glob.glob(sys.argv[1]+"/**/*3D_combined.json", recursive = True)
#report_files = glob.glob(sys.argv[1]+"/**/*RefAtlasRegions_*.csv", recursive = True)
atlas_files = glob.glob(sys.argv[1]+"/**/*.label", recursive = True)



typ = 0
#if (len(sys.argv)==3):
#	typ = int(sys.argv[2])


color_map = {}

def load_labels(file):
	
	with open(file,'r') as f:
		line = f.readline()
		while line:
			line = f.readline().strip()
			if (not line.startswith("#")):
				line = line.replace("\"","").lower().split(",")[0]
				lst = line.split('\t')
				if len(lst)==8:
#					print(lst[7])
					color_map[lst[7]] = [float(lst[1])/256.0,float(lst[2])/256.0,float(lst[3])/256.0]

    

if len(data_files)==0:
	print("Could not find any reports to plot ")
	exit(1)

if len(atlas_files)==0:
	print("Could not find any atlas files ")
	exit(1)


load_labels(atlas_files[0])


f = open(data_files[0])
 
# returns JSON object as
# a dictionary
data = json.load(f)


x=[]
y=[]
z=[]
colors = []
sc = 10.0
for d in data:
	i = 0
	j = 0
	col = 'rgb('+str(d['r'])+','+str(d['g'])+','+str(d['b'])+')'
	for i in range(0,int(len(d['triplets'])/3)):
		x.append(d['triplets'][j]*sc)
		y.append(d['triplets'][j+1]*sc)
		z.append(d['triplets'][j+2]*sc)
		colors.append(col)		
		j+=3



fig = go.Figure(data=[go.Scatter3d(x=x, y=y, z=z,
                                   mode='markers',
                                   marker = dict(size=1,
 									color=colors,

                                   	)
                                   )])



fig.update_traces(marker_size = 1)

camera = dict(
    up=dict(x=0, y=0, z=1),
    center=dict(x=0, y=0, z=0),
    eye=dict(x=0, y=0, z=1.25)
)

fig.update_layout(scene_camera=camera, title="Coordinates")


#tls.get_embed('test.html')

fig.write_image("3d_plot.png")
fig.show()

