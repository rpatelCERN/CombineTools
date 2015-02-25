# MAKE DATA CARDS For Higgs Combine tool datacards made for the Sensitivity study of RA2+RA2b: Full Recipe

#Setup CMSSW Release w/ Combine Tool: 

setenv SCRAM_ARCH slc6_amd64_gcc481

cmsrel CMSSW_7_1_5

cd CMSSW_7_1_5/src/

cmsenv

git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit

scramv1 b -j 32

#Grab the Macros and python scripts: 

git clone -b stable-version https://github.com/rpatelCERN/CombineTools.git

cd CombineTools

//for running tests you can use my version of the input analysis files from eos at CERN : 

source getInputFiles.csh //makes the input files dir and also downloads files (don't do this if you are using your own) It will take a few minutes

//compile the macro for making datacards

root -b .L  macros/MakeCombineDataCards.C++

//need to make input histograms of the 4d bins (here they are just made rectangular):
root -b 

root>.L macros/MakeCombineDataCards_C.so

root> MakeInputHiso("Signal", 4); //make histograms of the signal region for 4/fb 

root>.x RunDataCards.C //gives 72 bin datacards for each signal model in the directory DataCards

exit root

Combine all the cards into a single file for each model :
e.g python ./python/QuickCombineCards.py T1tttt 1500 100

//compute significance

combine -M ProfileLikelihood AllBinsT1tttt1500_Lumi4.dat --signif

Output: 
<RooAbsArg*> > is available
Computing limit starting from observation

-- Profile Likelihood --
Significance: 2.62241
(p-value = 0.00436557)
Done in 0.09 min (cpu), 0.09 min (real)