# MAKE DATA CARDS For Higgs Combine tool datacards made for the Sensitivity study of RA2+RA2b: Full Recipe
#Setup CMSSW Release w/ Combine Tool: 

> setenv SCRAM_ARCH slc6_amd64_gcc481

> cmsrel CMSSW_7_1_5

> cd CMSSW_7_1_5/src/

> cmsenv

> git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit

#Grab the relevant Macros and python scripts: 

# To make datacards
1. Make histograms for input

> root -l -b -q MakeInputs.C

> hadd Bins4DSL_Lumi4.00fb.root Bins4DSLEl_Lumi4.00fb.root Bins4DSLMu_Lumi4.00fb.root

2. Make datacards

> root -l -b -q RunDatacards.C

N.B. Right now the code uses "lheWeight" introduced by Nhan instead of "Weight" branch standard in the TreeMaker

Files needed:
SMSbbbb1000.root
SMSbbbb1500.root
SMSqqqq1000.root
SMSqqqq1400.root
SMStttt1200.root
SMStttt1500.root
TTJets.root
QCDHT.root
WJ.root
ZJ.root
DY.root (not really needed)
GJ.root
