import ROOT
from ROOT import TFile, TTree, TChain, gPad, gDirectory
from datacard import *
# from sumJetMassBinning import *
# from sumJetMassbBinning import *
# from TestBinning import *
# from RA2bBinning import *
# from extendedSumJetMassBinning import *
# from gluinoXsec import *
from multiprocessing import Process
from optparse import OptionParser
from operator import add
import math
import sys
sys.path.insert(0, 'binnings')
from binning import *
# from RA2bBinning import *
# from RA2bBinning_72bins_2 import *
# from RA2bBinning_72bins_3 import *
# from RA2bBinning_48bins_3 import *
# from RA2bBinning_56bins_3 import *
# from RA2bBinning_64bins_3 import *
# from SMJBinning_36bins_1 import *
# from SMJBinning_72bins_1 import *
# from SMJBinning_72bins_2 import *
# from SMJBinning_72bins_3 import *
# from SMJBinning_72bins_4 import *
# from SMJBinning_48bins_4 import *
# from SMJBinning_56bins_4 import *
# from SMJBinning_64bins_4 import *

from binningIndex import *

parser = OptionParser()
parser.add_option("--lumi", dest="lumi", default = 4,help="mass of LSP", metavar="MLSP")
parser.add_option("--binning",dest="binning",default="RA2bBins",help="Select binning to be used: Classic, SMJ, extSMJ", metavar="binning")

(options, args) = parser.parse_args()

#LUMI
#Signals??
#Binning

#########################################################################################################
#########################################################################################################
def computeYields(  tree , binning , analysisRegion, samplename, isRaw=0 ) :

	lumi = float(options.lumi);
	yields = [];

	cutString = ""
	if analysisRegion   == 'Signal':
		cutString = "(HT>500 && NJets>=4 && MHT>200 && (MuonsNum==0 && ElectronsNum==0) && abs(minDeltaPhiN)>4.0 && isoTracks==0";
	elif analysisRegion == 'LDP':
		cutString = "(HT>500 && NJets>=4 && MHT>200 && (MuonsNum==0 && ElectronsNum==0) && abs(minDeltaPhiN)<4.0 && isoTracks==0";
	elif analysisRegion == 'SLe':
		cutString = "(HT>500 && NJets>=4 && MHT>200 && abs(minDeltaPhiN)>4.0 && (MuonsNum==0 && ElectronsNum==1) && ( sqrt(2 *METPt*ElectronsPt[0]*(1-cos(ElectronsPhi[0]-METPhi)))<100  )";
	elif analysisRegion == 'SLm':
		cutString = "(HT>500 && NJets>=4 && MHT>200 && abs(minDeltaPhiN)>4.0 && (MuonsNum==1 && ElectronsNum==0) && ( sqrt(2 *METPt*MuonsPt[0]*(1-cos(MuonsPhi[0]-METPhi)))<100  )";
	elif analysisRegion == 'GJet':
		cutString = "(HTnoPhotons>500 && NJets>=4 && MHTnoPhotons>200 && abs(minDeltaPhiNnoPhotons)>4.0 && (Photons == 1)";
	elif analysisRegion == 'DYm':
		cutString = "(HT>500 && NJets>=4 && MHT>200 && abs(minDeltaPhiN)>4.0 && (MuonsNum==2 && ElectronsNum==0)";
	else: 
		raise NameError("No such analysis region...!")


	for iBin in range( binning.nBins ): 
		#print "[computeYields] nbin = ",iBin
		# print "bin = ", iBin;
		curCutString = "";
		# add bin cuts		
		for i in range( len( binning.branchNames ) ) : 
			branchName = binning.branchNames[i];
			branchNameIndex = binning.branchNames[i];
			if analysisRegion == 'GJet' and branchName == 'HT': branchName = 'HTnoPhotons';
			if analysisRegion == 'GJet' and branchName == 'MHT': branchName = 'MHTnoPhotons';
			curCutString+=" && {0} > {1} && {0} < {2} ".format(branchName,binning.lowBinEdge[branchNameIndex][iBin],binning.highBinEdge[branchNameIndex][iBin])

		if isRaw == 0: curCutString += ")*(lheWeight*%e)" % lumi;
		if isRaw == 1: curCutString += ")";
		theCut = cutString + curCutString;
		# print "thecut = ", theCut

		histName = "htt"+str(iBin)+analysisRegion+samplename;
		#print binning.branchNames[0]+">>"+histName
		binEntries = tree.Project(histName,"HT",theCut);
		#print "yield: ", gDirectory.Get(histName).Integral()
		yields.append( gDirectory.Get(histName).Integral() );
	
	return yields;

#########################################################################################################
#########################################################################################################
if __name__ == '__main__':

	binning = options.binning
	theBins = GetBinning(binning);
	signalmodels = ['SMStttt1500','SMStttt1200','SMSbbbb1500','SMSbbbb1000','SMSqqqq1400','SMSqqqq1000'];

	# ---------------------------------------------------
	## Define cards to build
	myDatacard = [];
	for signal in signalmodels:
		myDatacard.append( datacard( theBins , [signal] , [ "QCD" , "Zinv" , "WjetTT" ] ) );

	# ---------------------------------------------------
	## Define the files
	inputDir = "./"

	accessProtocol = "root://cmsxrootd-site.fnal.gov//store/user/"
	fileDir = "/uscms_data/d2/ntran/physics/SUSY/Run2/statInterp/project/CMSSW_7_1_5/src/CombineTools/macros/LatestSynchFiles/"
	treeName = 'TreeMaker2/PreSelection'

	SignalTrees = [];
	for i in range(len(signalmodels)):
		tmptree = TChain(treeName);
		tmptree.Add( fileDir + signalmodels[i] + ".root" )
		SignalTrees.append( tmptree );

	QCDtree = TChain(treeName)
	QCDtree.Add( fileDir + "QCDHT.root" )
	Zjttree = TChain(treeName)
	Zjttree.Add( fileDir + "ZJ.root" )
	Wjttree = TChain(treeName)
	Wjttree.Add( fileDir + "WJ.root" )
	TTbtree = TChain(treeName)
	TTbtree.Add( fileDir + "TTJets.root" )
	Gjttree = TChain(treeName)
	Gjttree.Add( fileDir + "GJ.root" )
	DYmtree = TChain(treeName)
	DYmtree.Add( fileDir + "DY.root" )

	# ---------------------------------------------------
	## compute yields (outputs a number per bin, different cuts based on region defined)
	#analysisRegions = ['Signal','LDP','SLe','SLm','GJet','DYm']
	analysisRegions = ['Signal','LDP','SLe','SLm','GJet']
	# analysisRegions = ['Signal','LDP']
	allBkgQCDYields = [];
	allBkgZinvYields = [];
	allBkgWjTTYields = [];
	allBkgGJetYields = [];
	for region in analysisRegions:

		print "computing background yields for analysis region ",region
		print("QCD");
		allBkgQCDYields.append(  computeYields( QCDtree  , theBins , region, "qcd" ) );
		print("Zinv");
		allBkgZinvYields.append( computeYields( Zjttree  , theBins , region, "zinv" ) );
		print("WJet");
		curWJYields            = computeYields( Wjttree  , theBins , region, "wjt" );
		print("TTbar");
		curTTYields            = computeYields( TTbtree  , theBins , region, "ttb" );
		allBkgWjTTYields.append( map(add,curWJYields,curTTYields) );
		print("GJet");
		allBkgGJetYields.append( computeYields( Gjttree  , theBins , region, "gjt" ) );
		
	# don't forget signals!
	allSigYields = [];
	allSigYieldsRaw = [];
	for region in analysisRegions:
		tmpSigYields = [];
		tmpSigYieldsRaw = [];
		for i in range(len(signalmodels)):
			tmpSigYields.append( computeYields( SignalTrees[i], theBins, region, "signal"+str(i) ) );
			tmpSigYieldsRaw.append( computeYields( SignalTrees[i], theBins, region, "signal"+str(i),1 ) );
		allSigYields.append( tmpSigYields );
		allSigYieldsRaw.append( tmpSigYieldsRaw );

	# ---------------------------------------------------
	# create the cards

	for i in range( theBins.nBins ) :

		# get nb's 
		nbjets = -1;
		if "BTags" in theBins.branchNames:
			if theBins.lowBinEdge["BTags"][i] < 0 and theBins.highBinEdge["BTags"][i] > 0: nbjets = 0;
			if theBins.lowBinEdge["BTags"][i] < 1 and theBins.highBinEdge["BTags"][i] > 1: nbjets = 1;
			if theBins.lowBinEdge["BTags"][i] < 2 and theBins.highBinEdge["BTags"][i] > 2: nbjets = 2;
			if theBins.lowBinEdge["BTags"][i] < 3 and theBins.highBinEdge["BTags"][i] > 3: nbjets = 3;

		# how to pass yields to the datacard?
		# list of lists, per analysis region to include
		binBkgYield_tmp = []
		binBkgYield = []
		ARLabels = [];
		for bi in range(len(analysisRegions)): 
			if analysisRegions[bi] == 'GJet': binBkgYield_tmp.append( [allBkgQCDYields[bi][i],allBkgGJetYields[bi][i],allBkgWjTTYields[bi][i]] );
			else: binBkgYield_tmp.append( [allBkgQCDYields[bi][i],allBkgZinvYields[bi][i],allBkgWjTTYields[bi][i]] );
			# print "analysis Region = ", analysisRegions[bi], " -- " , binBkgYield_tmp[bi]
			# print "allBkgQCDYields = ", allBkgQCDYields[bi]
			# print "allBkgZinvYields = ", allBkgZinvYields[bi]
			# print "allBkgWjTTYields = ", allBkgWjTTYields[bi]
			# print "allBkgGJetYields = ", allBkgGJetYields[bi]


		# have to do this to merge the SL regions
		sleBkgYields = []; slmBkgYields = [];
		for bi in range(len(analysisRegions)): 
			if analysisRegions[bi] == 'SLe': # requires that 'SLe' comes before 'SLm'
				sleBkgYields = binBkgYield_tmp[bi];
			elif analysisRegions[bi] == 'SLm': # requires that 'SLe' comes before 'SLm'
				slmBkgYields = binBkgYield_tmp[bi];
				binBkgYield.append( map(add,sleBkgYields,slmBkgYields) ); ###!!!!!!!!!
				ARLabels.append( 'SL' )
			elif nbjets > 0 and analysisRegions[bi] == 'GJet':
				continue;
			else: 
				binBkgYield.append( binBkgYield_tmp[bi] )
				ARLabels.append( analysisRegions[bi])

		for si in range(len(signalmodels)):
			binSigYield = [];
			binSigYieldRaw = allSigYieldsRaw[0][si][i];
			#print "binSigYieldRaw = ", binSigYieldRaw;
			for bi in range(len(analysisRegions)):
				if analysisRegions[bi] == 'SLe': continue;
				else: binSigYield.append( allSigYields[bi][si][i] );
			nameOfCard = "DataCards/"+signalmodels[si]+"_"+binning+"_"+str(i)+".txt";

			# print nameOfCard, binSigYield, binBkgYield
			myDatacard[si].printDatacard(i,nameOfCard,binSigYield,binBkgYield,ARLabels,nbjets);
			# add any aditional systematics
			if binSigYieldRaw > 0: myDatacard[si].AddSystematic('MCstat_'+str(i), 'lnN', (1. + (math.sqrt(binSigYieldRaw)/binSigYieldRaw)), ['Signal'], signalmodels[si]);
			# close file
			myDatacard[si].Close();



