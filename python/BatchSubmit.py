import sys
import os
#make these arrays
mGlu=1500
mLsp=100

if(sys.argv[1]=="InitHistos"):	#ONLY HAVE TO USE THIS ONCE PerMass Point FOR A NEW SET OF BINNING
    #can create loop to make the bins for a range of mass points
    #SUBMIT TO LXPLUS BATCH
    f=open("bsub%d.sh" %i, 'w')
        f.write("set SCRAM_ARCH=slc6_amd64_gcc481\n")
        #Point to your combine area:
        f.write("cd /afs/cern.ch/user/r/rpatel/CMSSW_7_2_3_patch1/src\n")
        f.write("eval `scramv1 runtime -sh`\n")
        f.write("root -b -q 'RunInputHistos.C(%d, %d)' " %(mGlu, mLsp))
        f.close()
        os.system("chmod 744 bsub%d.sh" %i)
        os.system("bsub -R \"pool>30000\" -q 8nm -J job%d < bsub%d.sh" %(i,i))
    #RUN LOCALLY
    #os.system("root -b -q 'RunInputHistos.C(%d, %d)' " %(mGlu, mLsp))

bins=[0,1,2]
if(sys.argv[1]=="SubmitBins"):
    combineMethod="Asymptotic"
    for b in range(0, len(bins)):
        combineoFile="Ra2b_combineOutput_bin%d_MGlu%d_Mlsp%dExpLimit.root"
        datacardName="datfiles/SensStudyBin%d_M%d_m%d_DEFAULT.dat" %(bins[b],mGlu,mLsp)

        #SUBMIT TO LXPLUS BATCH
        f=open("bsub%d.sh" %i, 'w')
        f.write("set SCRAM_ARCH=slc6_amd64_gcc481\n")
        #Point to your combine area:
        f.write("cd /afs/cern.ch/user/r/rpatel/CMSSW_7_2_3_patch1/src\n")
        f.write("eval `scramv1 runtime -sh`\n")
        f.write("root -b -q 'RunCards.C(%d, %d, \"\", true, %d )' " %(mGlu, mLsp, bins[b])) #creates the card
        f.write("combine -M %s %s -o %s " %(combineMethod, datacardName, combineoFile)#run combine
        f.close()
        os.system("chmod 744 bsub%d.sh" %i)
        os.system("bsub -R \"pool>30000\" -q 8nm -J job%d < bsub%d.sh" %(i,i))
        #RUN LOCALLY
        #os.system("root -b -q 'RunCards.C(%d, %d, \"\", true, %d )' " %(mGlu, mLsp, bins[b]))

#if(sys.argv[1]=="Submit"):
#ALLBINS

    #RUN LOCALLY
        #os.system("root -b -q 'RunCards.C(%d, %d, \"\")' " %(mGlu, mLsp, bins[b]))