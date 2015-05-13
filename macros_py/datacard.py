"""
class intended to organize all the relevant information
for building a multi-binned cut & count datacard.

A. Whitbeck - June 3, 2014

The binning object (as defined in binning.py), a list
of signal channel labels, and a list of background channel 
labels should all be passed to the constructor.
"""
import sys
sys.path.insert(0, 'binnings')
from binning import *
from RA2bBinning import *

class datacard:

	def __init__( self , binning, sigLabels , bkgLabels ) :

		self.binning = binning
		
		self.sigLabels = sigLabels
		self.bkgLabels = bkgLabels

		self.sigYields = {}
		self.bkgYields = {}

		for label in sigLabels :
			self.sigYields[ label ] = [0.]*self.binning.nBins

		for label in bkgLabels :
			self.bkgYields[ label ] = [0.]*self.binning.nBins		

	def printDatacard( self , bin = 0, fileName = "exampleCard.txt", signalYield = [0], bkgYield = [0], regionlabels = ['sig'], nb = -1 ) :

		#for var in self.binning.lowBinEdge :
			#print self.binning.lowBinEdge[var][bin]
		self.signalYield = signalYield
		self.bkgYield = bkgYield
		self.regionlabels = regionlabels;
		self.nCategories = len(regionlabels);
		self.observedVals = [];
		for i in range(len(regionlabels)):
			self.observedVals.append( signalYield[i] + sum(bkgYield[i]) );

		self.outputFile = open( fileName , 'w' )

		#############################
		# yield part of the datacard
		line = "";
		line = "imax %i #number of channels \n" % (self.nCategories);
		self.outputFile.write(line);
		line = "jmax %i #number of backgrounds \n" % (len(self.bkgLabels));
		self.outputFile.write(line);
		self.outputFile.write("kmax * nuissance \n");
		self.outputFile.write("------------ \n");

		line = "bin";
		for label in regionlabels: line += " Bin"+label+str(bin);
		line += "\n";
		self.outputFile.write(line);

		line = "observation";
		for val in self.observedVals: line += " %.3f" % (val);
		line += "\n"
		self.outputFile.write(line);

		line = "bin";
		for label in regionlabels:
			for i in range(len(self.sigLabels)+len(self.bkgLabels)):
				line += " Bin"+label+str(bin);
		line += "\n"
		self.outputFile.write(line);

		line = "process";
		line2 = "process"; 
		for i in range(len(regionlabels)):
			for j in range(len(self.sigLabels)): 
				line += " " + self.sigLabels[j];
				line2 += " " + str(0-j);
			for j in range(len(self.bkgLabels)): 
				line += " " + self.bkgLabels[j];
				line2 += " " + str(j+1)
		line += "\n";
		line2 += "\n";
		self.outputFile.write(line);
		self.outputFile.write(line2);

		line = "rate";
		zeroProxy = 0.0001;
		qcdScaleFactor = 1.;
		for r in range(len(regionlabels)):
			# print "signalYield[r] = ", signalYield[r]
			if signalYield[r] < 0.000001: line += " " + str(zeroProxy);
			else: line += " %.5f" % (signalYield[r]);
			for i in range(len(self.bkgLabels)): 
				if bkgYield[r][i] < 0.000001: 
					if regionlabels[r] == 'LDP' and self.bkgLabels[i] == 'QCD': line += " " + str(qcdScaleFactor*zeroProxy);
					else: line += " " + str(zeroProxy);
				else: line += " %.5f" % (bkgYield[r][i]);
		line += "\n";
		self.outputFile.write(line);

		#############################
		# add systematics
		self.outputFile.write("------------ \n");		
		self.AddSystematic('lumi', 'lnN', 1.044, ['Signal'], self.sigLabels);
		self.AddSystematic('PDFunc', 'lnN', 1.1, ['Signal'], self.sigLabels);
		self.AddSystematic('JEC', 'lnN', 1.1, ['Signal'], self.sigLabels);
		self.AddSystematic('BTagEffSigmaUp', 'lnN', 1.1, ['Signal'], self.sigLabels);
		self.AddSystematic('BTagEffSigmaDn', 'lnN', 0.9, ['Signal'], self.sigLabels);
		# self.AddSystematic('MCstat_'+str(bin), 'lnN', 1.1, ['Signal'], self.sigLabels); # handled externally
		
		# QCD systematics
		self.AddSystematic('rateBqcd_'+str(bin), 'lnU', 100, ['Signal','LDP'], ['QCD']);
		self.AddSystematic('LDPRUnc', 'lnN', 1.3, ['Signal'], ['QCD']);

		# SL systematics
		self.AddSystematic('rateBW_'+str(bin), 'lnU', 100, ['Signal','SL'], ['WjetTT']);
		self.AddSystematic('LepEff', 'lnN', 1.07, ['Signal'], ['WjetTT']);
		self.AddSystematic('MCClose_'+str(bin),'lnN',1.1,['Signal'], ['WjetTT']);
		
		# GJet systematics
		if nb == 0:
			self.AddSystematic('rateBPh_'+str(bin),'lnU',100,['Signal','GJet'],['Zinv']);
			self.AddSystematic('rateB0BTo1B','lnU',100,['Signal'],['Zinv']);
			self.AddSystematic('rateB0BTo2B','lnU',100,['Signal'],['Zinv']);
			self.AddSystematic('rateB0BTo3B','lnU',100,['Signal'],['Zinv']);
			self.AddSystematic('PhoRUnc', 'lnN', 1.3, ['Signal'], ['Zinv']);
		if nb > 0:
			self.AddSystematic('rateB0BTo'+str(nb)+'B','lnU',100,['Signal'],['Zinv']);
			self.AddSystematic('PhoRUnc', 'lnN', 1.3, ['Signal'], ['Zinv']);
			self.AddSystematic('RUnc0BtoNB', 'lnN', 1.3, ['Signal'], ['Zinv']);

	def AddSystematic(self,name,systype,val,regions,channels):

		line = "";
		line += name;
		line += " " + systype;

		for i in range(len(self.regionlabels)):
			for j in range(len(self.sigLabels)):
				if self.regionlabels[i] in regions and self.sigLabels[j] in channels: 
					# check if 0.0000
					if self.signalYield[i] < 0.000001 and systype == 'lnU': line += " " + str(val*1000) + " ";
					else: line += " " + str(val) + " ";
				else: line += " - "
			for j in range(len(self.bkgLabels)):
				if self.regionlabels[i] in regions and self.bkgLabels[j] in channels: 
					if self.bkgYield[i][j] < 0.000001 and systype == 'lnU': line += " " + str(val*1000) + " ";
					else: line += " " + str(val) + " ";
				else: line += " - "
		line += "\n";

		self.outputFile.write( line );

	def Close(self):
		self.outputFile.close();

