## binning definition for sum jet mass analysis

import sys
#sys.path.insert(0, '/uscms_data/d2/ntran/physics/SUSY/Run2/statInterp/project/CMSSW_7_1_5/src/CombineTools/macros_py/binnings')
sys.path.insert(0, 'binnings')
from binning import *

RA2bBins_72bins_2 = binning( [ "BTags" , "HT" , "MHT" , "NJets" ] )

################ SMJ cuts #### MHT cuts #### NJet cuts ###

## 0b binning (24)
RA2bBins_72bins_2.addBin( [ (-1 , 1) , ( 500 ,  800) , ( 200 ,  450)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , ( 800 , 1200) , ( 200 ,  450)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , (1200 , 9999) , ( 200 ,  450)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , ( 500 , 1200) , ( 450 ,  650)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , (1200 , 9999) , ( 450 ,  650)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , ( 800 , 9999) , ( 650 , 9999)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , ( 500 ,  800) , ( 200 ,  450)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , ( 800 , 1200) , ( 200 ,  450)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , (1200 , 9999) , ( 200 ,  450)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , ( 500 , 1200) , ( 450 ,  650)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , (1200 , 9999) , ( 450 ,  650)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , ( 800 , 9999) , ( 650 , 9999)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , ( 500 ,  800) , ( 200 ,  450)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , ( 800 , 1200) , ( 200 ,  450)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , (1200 , 9999) , ( 200 ,  450)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , ( 500 , 1200) , ( 450 ,  650)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , (1200 , 9999) , ( 450 ,  650)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ (-1 , 1) , ( 800 , 9999) , ( 650 , 9999)  , (8 ,99) ] )

RA2bBins_72bins_2.addBin( [ ( 0 , 2) , ( 500 ,  800) , ( 200 ,  450)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , ( 800 , 1200) , ( 200 ,  450)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , (1200 , 9999) , ( 200 ,  450)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , ( 500 , 1200) , ( 450 ,  650)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , (1200 , 9999) , ( 450 ,  650)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , ( 800 , 9999) , ( 650 , 9999)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , ( 500 ,  800) , ( 200 ,  450)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , ( 800 , 1200) , ( 200 ,  450)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , (1200 , 9999) , ( 200 ,  450)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , ( 500 , 1200) , ( 450 ,  650)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , (1200 , 9999) , ( 450 ,  650)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , ( 800 , 9999) , ( 650 , 9999)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , ( 500 ,  800) , ( 200 ,  450)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , ( 800 , 1200) , ( 200 ,  450)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , (1200 , 9999) , ( 200 ,  450)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , ( 500 , 1200) , ( 450 ,  650)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , (1200 , 9999) , ( 450 ,  650)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 0 , 2) , ( 800 , 9999) , ( 650 , 9999)  , (8 ,99) ] )

RA2bBins_72bins_2.addBin( [ ( 1 , 3) , ( 500 ,  800) , ( 200 ,  450)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , ( 800 , 1200) , ( 200 ,  450)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , (1200 , 9999) , ( 200 ,  450)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , ( 500 , 1200) , ( 450 ,  650)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , (1200 , 9999) , ( 450 ,  650)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , ( 800 , 9999) , ( 650 , 9999)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , ( 500 ,  800) , ( 200 ,  450)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , ( 800 , 1200) , ( 200 ,  450)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , (1200 , 9999) , ( 200 ,  450)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , ( 500 , 1200) , ( 450 ,  650)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , (1200 , 9999) , ( 450 ,  650)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , ( 800 , 9999) , ( 650 , 9999)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , ( 500 ,  800) , ( 200 ,  450)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , ( 800 , 1200) , ( 200 ,  450)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , (1200 , 9999) , ( 200 ,  450)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , ( 500 , 1200) , ( 450 ,  650)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , (1200 , 9999) , ( 450 ,  650)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 1 , 3) , ( 800 , 9999) , ( 650 , 9999)  , (8 ,99) ] )

RA2bBins_72bins_2.addBin( [ ( 2 , 9) , ( 500 ,  800) , ( 200 ,  450)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , ( 800 , 1200) , ( 200 ,  450)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , (1200 , 9999) , ( 200 ,  450)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , ( 500 , 1200) , ( 450 ,  650)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , (1200 , 9999) , ( 450 ,  650)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , ( 800 , 9999) , ( 650 , 9999)  , (3 , 7) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , ( 500 ,  800) , ( 200 ,  450)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , ( 800 , 1200) , ( 200 ,  450)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , (1200 , 9999) , ( 200 ,  450)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , ( 500 , 1200) , ( 450 ,  650)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , (1200 , 9999) , ( 450 ,  650)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , ( 800 , 9999) , ( 650 , 9999)  , (6 , 9) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , ( 500 ,  800) , ( 200 ,  450)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , ( 800 , 1200) , ( 200 ,  450)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , (1200 , 9999) , ( 200 ,  450)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , ( 500 , 1200) , ( 450 ,  650)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , (1200 , 9999) , ( 450 ,  650)  , (8 ,99) ] )
RA2bBins_72bins_2.addBin( [ ( 2 , 9) , ( 800 , 9999) , ( 650 , 9999)  , (8 ,99) ] )

########################################################################################
########################################################################################
########################################################################################
########################################################################################


