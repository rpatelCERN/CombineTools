import sys
sys.path.insert(0, '/uscms_data/d2/ntran/physics/SUSY/Run2/statInterp/project/CMSSW_7_1_5/src/CombineTools/macros_py/binnings')
from binning import *
from RA2bBinning import *
from RA2bBinning_72bins_2 import *
from RA2bBinning_72bins_3 import *
from RA2bBinning_48bins_3 import *
from RA2bBinning_56bins_3 import *
from RA2bBinning_60bins_3 import *
from RA2bBinning_64bins_3 import *
from SMJBinning_36bins_1 import *
from SMJBinning_72bins_1 import *
from SMJBinning_72bins_2 import *
from SMJBinning_72bins_3 import *
from SMJBinning_72bins_4 import *
from SMJBinning_48bins_4 import *
from SMJBinning_56bins_4 import *
from SMJBinning_60bins_4 import *
from SMJBinning_64bins_4 import *

#########################################################################################################
#########################################################################################################
def GetBinning(binning):
    
	if binning == "samplebins" : return samplebins;
	elif binning == "RA2bBins" : return RA2bBins;	
	elif binning == "RA2bBins_72bins_2" : return RA2bBins_72bins_2;	
	elif binning == "RA2bBins_72bins_3" : return RA2bBins_72bins_3;	
	elif binning == "RA2bBins_48bins_3" : return RA2bBins_48bins_3;	
	elif binning == "RA2bBins_56bins_3" : return RA2bBins_56bins_3;		
	elif binning == "RA2bBins_60bins_3" : return RA2bBins_60bins_3;	
	elif binning == "RA2bBins_64bins_3" : return RA2bBins_64bins_3;	
	elif binning == "SMJBins_36bins_1" : return SMJBins_36bins_1;		
	elif binning == "SMJBins_72bins_1" : return SMJBins_72bins_1;		
	elif binning == "SMJBins_72bins_2" : return SMJBins_72bins_2;		
	elif binning == "SMJBins_72bins_3" : return SMJBins_72bins_3;		
	elif binning == "SMJBins_72bins_4" : return SMJBins_72bins_4;		
	elif binning == "SMJBins_48bins_4" : return SMJBins_48bins_4;		
	elif binning == "SMJBins_56bins_4" : return SMJBins_56bins_4;		
	elif binning == "SMJBins_60bins_4" : return SMJBins_60bins_4;		
	elif binning == "SMJBins_64bins_4" : return SMJBins_64bins_4;		
	else :
		raise NameError(binning)
		return;
