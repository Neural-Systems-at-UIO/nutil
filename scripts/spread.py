import sys
import json
import numpy as np
import copy
#>>> numbers = np.genfromtxt('text_file.txt', usecols=1 )
import random

import fileinput
from xml.dom import minidom


cols = []
header = []

def read_json(fname):
	f = open(fname)
	data = json.load(f)
	f.close()
	x = []
	for d in data:
		t = d['triplets']
		k = copy.deepcopy(d)
		k['triplets'].clear()
		header.append(k)
		for i in range(int(len(t)/3)):
			v = np.zeros(3)
			j = int(i)
			v[0] = (t[3*j])
			v[1] = (t[3*j+1])
			v[2] = (t[3*j+2])
			x.append(v)
			if (i==0) :
				c = {}
				c['col'] = [ d['r'],d['g'],d['b'] ]
				c['point'] = v
				cols.append(c)

	return x

def read_file(fname):
	with open(fname, 'r') as file :
		filedata = file.read()

	filedata = filedata.replace(',', '.')

# Write the file out again
	with open(fname, 'w') as file:
		file.write(filedata)

	return np.genfromtxt(fname)

def plane_from_data(x):
	i1 = 1
	i2 = 5
	i3 = 3
	plane = np.cross( x[i1]-x[i2], x[i1]-x[i3] )
	plane = plane / np.linalg.norm(plane)
	return plane


if len(sys.argv)!=3:
    print("Usage: spread.py [ z_file.txt ] [ width ]")
    exit(1)
#print 'Number of arguments:', len(sys.argv), 'arguments.'

inFile = sys.argv[1]
width = float(sys.argv[2])





if (inFile.lower().endswith(".json")):
	x = read_json(inFile)
else:
	x = read_file(inFile)

plane = plane_from_data(x)
outFile = inFile.split(".")[0]+"_spread.json"

of = open(outFile,"w") 

def saveXYZ():
	for d in x:
		for c in cols:
			if ((c['point']==d).all()):
	#			of.write("RGBA "+str(c['col'][0]) + " " +str(c['col'][1]) + " " +str(c['col'][2]) + " 1 \n")
				of.write("RGB "+str(c['col'][0]) + " " +str(c['col'][1]) + " " +str(c['col'][2]) + "\n")
		v = d + plane * random.gauss(0,width)
		of.write(str(v[0]) + "\t" + str(v[1])   +"\t" +  str(v[2]) + "\n")
	
def saveJSON():
	cur = -1
	for d in x:
		for c in cols:
			if ((c['point']==d).all()):
	#			of.write("RGBA "+str(c['col'][0]) + " " +str(c['col'][1]) + " " +str(c['col'][2]) + " 1 \n")
				if (cur<len(header)):
					cur=cur+1

		v = d + plane * random.gauss(0,width)
		header[cur]['triplets'].append(v[0])
		header[cur]['triplets'].append(v[1])
		header[cur]['triplets'].append(v[2])
#		of.write(str(v[0]) + "\t" + str(v[1])   +"\t" +  str(v[2]) + "\n")

	json.dump(header,of)

saveJSON()

of.close()



