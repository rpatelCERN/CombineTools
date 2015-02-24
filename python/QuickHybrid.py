import os
import sys
import random
import time
#datacard="SensStudySys_M1500_m100_T1tttt_Lumi5.dat"
#Significance:
basecommand="combine -M HybridNew --freq"
options="--testStat LHC --fullBToys --significance --saveToys --saveHybridResult -T 2500 -i 3 -S 1"

#Exp. Limit:
#options=" -H ProfileLikelihood -v 0 --saveToys --saveHybridResult -T 250 -i 3 "
#for j in range(0,1):
	#datacard="SensStudyLumi5_Bin%d_M1500_m100_T1tttt.dat" %j
datacard="LowbkgStatsCar.dat"
#datacard="LowBkgStatsCar.dat"
	#datacard="SensStudyLumi1_Bin%d_M1500_m100_T1tttt.dat" %j
#datacard="SensStudySys_M1500_m100_T1tttt_Lumi5.dat"
	#if(j>1):continue

#for j in range(0, 40):
#	point=0.0+(0.05*j)
	#if(j!=0):continue	
j=99
for i in range (0,4):
		random.seed()
		r=random.randint(1,200)
		f=open("%sBin%dbsub%d.sh" %(sys.argv[1],j,i), 'w')
		f.write("set SCRAM_ARCH=slc6_amd64_gcc481\n")
        	f.write("cd /afs/cern.ch/user/r/rpatel/CMSSW_7_1_5/src\n")
        	f.write("eval `scramv1 runtime -sh`\n")
        	f.write("cd Sens3/ \n")
        	f.write("%s %s %s -s %d -n DummyTestSig%dCombine%d  \n" %(basecommand, datacard, options, r,j,i))
        	f.close()
        	os.system("chmod 744 %sBin%dbsub%d.sh" %(sys.argv[1],j,i))
		os.system("bsub -R \"pool>30000\" -q 8nm -J job%d < %sBin%dbsub%d.sh" %(i,sys.argv[1],j,i))
#        	os.system("%s %s %s -s %d -n DummyTestBin%dCombine%d" %(basecommand, datacard, options, r,j,i))
		
