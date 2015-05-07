import sys
sys.path.insert(0, '/uscms_data/d2/ntran/physics/SUSY/Run2/statInterp/project/CMSSW_7_1_5/src/CombineTools/macros_py/binnings')
from binning import *
from RA2bBinning import *
from SMJBinning_36bins_1 import *
from SMJBinning_72bins_1 import *

#########################################################################################################
#########################################################################################################
def GetBinning(binning):
    
	if binning == "samplebins" : return samplebins;
	elif binning == "RA2bBins" : return RA2bBins;	
	elif binning == "SMJBins_36bins_1" : return SMJBins_36bins_1;		
	elif binning == "SMJBins_72bins_1" : return SMJBins_72bins_1;		
	else :
		raise NameError(binning)
		return;
