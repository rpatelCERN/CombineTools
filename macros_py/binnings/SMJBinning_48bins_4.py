## binning definition for sum jet mass analysis

import sys
#sys.path.insert(0, '/uscms_data/d2/ntran/physics/SUSY/Run2/statInterp/project/CMSSW_7_1_5/src/CombineTools/macros_py/binnings')
sys.path.insert(0, 'binnings')
from binning import *

SMJBins_48bins_4 = binning( [ "BTags", "MHT" , "ak1p2Jets_sumJetMass", "NJets" ] )

################ SMJ cuts #### MHT cuts #### NJet cuts ###

## 0b binning (24)

SMJBins_48bins_4.addBin( [ (-1 , 1) , ( 200 ,  450) , ( 100 ,  600)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ (-1 , 1) , (	450 ,  650) , ( 100 ,  600)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ (-1 , 1) , ( 650 , 9999) , ( 100 ,  600)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ (-1 , 1) , ( 200 ,  450) , ( 600 , 9999)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ (-1 , 1) , (	450 ,  650) , ( 600 , 9999)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ (-1 , 1) , ( 650 , 9999) , ( 600 , 9999)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ (-1 , 1) , ( 200 ,  450) , ( 100 ,  600)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ (-1 , 1) , (	450 ,  650) , ( 100 ,  600)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ (-1 , 1) , ( 650 , 9999) , ( 100 ,  600)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ (-1 , 1) , ( 200 ,  450) , ( 600 , 9999)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ (-1 , 1) , (	450 ,  650) , ( 600 , 9999)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ (-1 , 1) , ( 650 , 9999) , ( 600 , 9999)  , (6 ,99) ] )

SMJBins_48bins_4.addBin( [ ( 0 , 2) , ( 200 ,  450) , ( 100 ,  600)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 0 , 2) , (	450 ,  650) , ( 100 ,  600)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 0 , 2) , ( 650 , 9999) , ( 100 ,  600)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 0 , 2) , ( 200 ,  450) , ( 600 , 9999)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 0 , 2) , (	450 ,  650) , ( 600 , 9999)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 0 , 2) , ( 650 , 9999) , ( 600 , 9999)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 0 , 2) , ( 200 ,  450) , ( 100 ,  600)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 0 , 2) , (	450 ,  650) , ( 100 ,  600)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 0 , 2) , ( 650 , 9999) , ( 100 ,  600)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 0 , 2) , ( 200 ,  450) , ( 600 , 9999)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 0 , 2) , (	450 ,  650) , ( 600 , 9999)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 0 , 2) , ( 650 , 9999) , ( 600 , 9999)  , (6 ,99) ] )

SMJBins_48bins_4.addBin( [ ( 1 , 3) , ( 200 ,  450) , ( 100 ,  600)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 1 , 3) , (	450 ,  650) , ( 100 ,  600)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 1 , 3) , ( 650 , 9999) , ( 100 ,  600)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 1 , 3) , ( 200 ,  450) , ( 600 , 9999)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 1 , 3) , (	450 ,  650) , ( 600 , 9999)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 1 , 3) , ( 650 , 9999) , ( 600 , 9999)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 1 , 3) , ( 200 ,  450) , ( 100 ,  600)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 1 , 3) , (	450 ,  650) , ( 100 ,  600)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 1 , 3) , ( 650 , 9999) , ( 100 ,  600)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 1 , 3) , ( 200 ,  450) , ( 600 , 9999)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 1 , 3) , (	450 ,  650) , ( 600 , 9999)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 1 , 3) , ( 650 , 9999) , ( 600 , 9999)  , (6 ,99) ] )

SMJBins_48bins_4.addBin( [ ( 2 , 9) , ( 200 ,  450) , ( 100 ,  600)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 2 , 9) , (	450 ,  650) , ( 100 ,  600)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 2 , 9) , ( 650 , 9999) , ( 100 ,  600)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 2 , 9) , ( 200 ,  450) , ( 600 , 9999)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 2 , 9) , (	450 ,  650) , ( 600 , 9999)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 2 , 9) , ( 650 , 9999) , ( 600 , 9999)  , (3 , 7) ] )
SMJBins_48bins_4.addBin( [ ( 2 , 9) , ( 200 ,  450) , ( 100 ,  600)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 2 , 9) , (	450 ,  650) , ( 100 ,  600)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 2 , 9) , ( 650 , 9999) , ( 100 ,  600)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 2 , 9) , ( 200 ,  450) , ( 600 , 9999)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 2 , 9) , (	450 ,  650) , ( 600 , 9999)  , (6 ,99) ] )
SMJBins_48bins_4.addBin( [ ( 2 , 9) , ( 650 , 9999) , ( 600 , 9999)  , (6 ,99) ] )


########################################################################################
########################################################################################
########################################################################################
########################################################################################


