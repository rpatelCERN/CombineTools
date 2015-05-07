## binning definition for sum jet mass analysis

import sys
#sys.path.insert(0, '/uscms_data/d2/ntran/physics/SUSY/Run2/statInterp/project/CMSSW_7_1_5/src/CombineTools/macros_py/binnings')
sys.path.insert(0, 'binnings')
from binning import *

SMJBins_36bins_1 = binning( [ "BTags", "MHT" , "ak1p2Jets_sumJetMass" ] )

################ SMJ cuts #### MHT cuts #### NJet cuts ###

## 0b binning (24)
SMJBins_36bins_1.addBin( [ (-1 , 1) , ( 200 ,  450)  , (100 ,  400) ] )
SMJBins_36bins_1.addBin( [ (-1 , 1) , ( 450 ,  650)  , (100 ,  400) ] )
SMJBins_36bins_1.addBin( [ (-1 , 1) , ( 650 , 9999)  , (100 ,  400) ] )
SMJBins_36bins_1.addBin( [ (-1 , 1) , ( 200 ,  450)  , (400 ,  600) ] )
SMJBins_36bins_1.addBin( [ (-1 , 1) , ( 450 ,  650)  , (400 ,  600) ] )
SMJBins_36bins_1.addBin( [ (-1 , 1) , ( 650 , 9999)  , (400 ,  600) ] )
SMJBins_36bins_1.addBin( [ (-1 , 1) , ( 200 ,  450)  , (600 , 9999) ] )
SMJBins_36bins_1.addBin( [ (-1 , 1) , ( 450 ,  650)  , (600 , 9999) ] )
SMJBins_36bins_1.addBin( [ (-1 , 1) , ( 650 , 9999)  , (600 , 9999) ] )

SMJBins_36bins_1.addBin( [ ( 0 , 2) , ( 200 ,  450)  , (100 ,  400) ] )
SMJBins_36bins_1.addBin( [ ( 0 , 2) , ( 450 ,  650)  , (100 ,  400) ] )
SMJBins_36bins_1.addBin( [ ( 0 , 2) , ( 650 , 9999)  , (100 ,  400) ] )
SMJBins_36bins_1.addBin( [ ( 0 , 2) , ( 200 ,  450)  , (400 ,  600) ] )
SMJBins_36bins_1.addBin( [ ( 0 , 2) , ( 450 ,  650)  , (400 ,  600) ] )
SMJBins_36bins_1.addBin( [ ( 0 , 2) , ( 650 , 9999)  , (400 ,  600) ] )
SMJBins_36bins_1.addBin( [ ( 0 , 2) , ( 200 ,  450)  , (600 , 9999) ] )
SMJBins_36bins_1.addBin( [ ( 0 , 2) , ( 450 ,  650)  , (600 , 9999) ] )
SMJBins_36bins_1.addBin( [ ( 0 , 2) , ( 650 , 9999)  , (600 , 9999) ] )

SMJBins_36bins_1.addBin( [ ( 1 , 3) , ( 200 ,  450)  , (100 ,  400) ] )
SMJBins_36bins_1.addBin( [ ( 1 , 3) , ( 450 ,  650)  , (100 ,  400) ] )
SMJBins_36bins_1.addBin( [ ( 1 , 3) , ( 650 , 9999)  , (100 ,  400) ] )
SMJBins_36bins_1.addBin( [ ( 1 , 3) , ( 200 ,  450)  , (400 ,  600) ] )
SMJBins_36bins_1.addBin( [ ( 1 , 3) , ( 450 ,  650)  , (400 ,  600) ] )
SMJBins_36bins_1.addBin( [ ( 1 , 3) , ( 650 , 9999)  , (400 ,  600) ] )
SMJBins_36bins_1.addBin( [ ( 1 , 3) , ( 200 ,  450)  , (600 , 9999) ] )
SMJBins_36bins_1.addBin( [ ( 1 , 3) , ( 450 ,  650)  , (600 , 9999) ] )
SMJBins_36bins_1.addBin( [ ( 1 , 3) , ( 650 , 9999)  , (600 , 9999) ] )

SMJBins_36bins_1.addBin( [ ( 2 , 9) , ( 200 ,  450)  , (100 ,  400) ] )
SMJBins_36bins_1.addBin( [ ( 2 , 9) , ( 450 ,  650)  , (100 ,  400) ] )
SMJBins_36bins_1.addBin( [ ( 2 , 9) , ( 650 , 9999)  , (100 ,  400) ] )
SMJBins_36bins_1.addBin( [ ( 2 , 9) , ( 200 ,  450)  , (400 ,  600) ] )
SMJBins_36bins_1.addBin( [ ( 2 , 9) , ( 450 ,  650)  , (400 ,  600) ] )
SMJBins_36bins_1.addBin( [ ( 2 , 9) , ( 650 , 9999)  , (400 ,  600) ] )
SMJBins_36bins_1.addBin( [ ( 2 , 9) , ( 200 ,  450)  , (600 , 9999) ] )
SMJBins_36bins_1.addBin( [ ( 2 , 9) , ( 450 ,  650)  , (600 , 9999) ] )
SMJBins_36bins_1.addBin( [ ( 2 , 9) , ( 650 , 9999)  , (600 , 9999) ] )


########################################################################################
########################################################################################
########################################################################################
########################################################################################


