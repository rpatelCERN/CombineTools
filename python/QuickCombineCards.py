import os
import sys
#str=" "
for j in range (4, 5):
	str=" "
	for i in range(0,72):
		str=str + " SensStudyLumi%2.2f_Bin%d_M%s_m%s_%s.dat " %(j,i, sys.argv[2], sys.argv[3], sys.argv[1])
	os.system("combineCards.py %s >AllBins%s%s_Lumi%d.dat" %(str,sys.argv[1], sys.argv[2],j))
