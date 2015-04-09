# MAKE DATA CARDS For Higgs Combine tool datacards made for the Sensitivity study of RA2+RA2b: Full Recipe
#Setup CMSSW Release w/ Combine Tool: 

setenv SCRAM_ARCH slc6_amd64_gcc481

cmsrel CMSSW_7_1_5

cd CMSSW_7_1_5/src/

cmsenv

git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit

#Grab the relevant Macros and python scripts: 
