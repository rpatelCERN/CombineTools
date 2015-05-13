#!/usr/bin/python
import ntpath
import os
import glob
import time

import ROOT
ROOT.gROOT.ProcessLine(".L ~/tdrstyle.C");
ROOT.setTDRStyle();
ROOT.gStyle.SetPadTopMargin(0.09);
ROOT.gStyle.SetPadLeftMargin(0.12);
ROOT.gStyle.SetPadRightMargin(0.06);
ROOT.gStyle.SetPadBottomMargin(0.15);
ROOT.gStyle.SetPalette(1);
ROOT.gStyle.SetErrorX(0.5);

import sys
sys.path.insert(0, 'binnings')
from binning import *
from RA2bBinning import *
from binningIndex import *

def submitToCondor(command,outputdir,postfix): 

	print "--------------------"
	print "Processing sample..."

	#change to a tmp dir
	os.chdir("tmp");
	curdir = os.getcwd();

	f1n = "tmp_%s.sh" %(postfix);
	f1=open(f1n, 'w')
	f1.write("#!/bin/sh \n");
	f1.write("source /cvmfs/cms.cern.ch/cmsset_default.csh \n");
	f1.write("set SCRAM_ARCH=slc6_amd64_gcc481\n")
	f1.write("cd %s \n" % (curdir))
	# f1.write("cd .. \n")
	f1.write("eval `scramv1 runtime -sh`\n")
	f1.write("cd - \n")
	f1.write("\n"+command);
	f1.write("\n"+'mv higgsCombine*.root '+outputdir+'/.');
	f1.close()

	f2n = "tmp_%s.condor" %(postfix);
	f2=open(f2n, 'w')
	f2.write("universe = vanilla \n");
	f2.write("Executable = %s \n" % (f1n) );
	f2.write("Requirements = Memory >= 199 &&OpSys == \"LINUX\"&& (Arch != \"DUMMY\" )&& Disk > 1000000 \n");
	f2.write("Should_Transfer_Files = YES \n");
	f2.write("WhenToTransferOutput  = ON_EXIT_OR_EVICT \n");
	f2.write("Output = out_$(Cluster).stdout \n");
	f2.write("Error = out_$(Cluster).stderr \n");
	f2.write("Log = out_$(Cluster).log \n");
	f2.write("Notification    = Error \n");
	f2.write("Queue 1 \n");
	f2.close();

	os.system("condor_submit %s" % (f2n));

	os.chdir("../.");


## ------------------------------------------------------------
class binContainer:
	
	def __init__(self, yields, cardname):   
		
		# sig, qcd1, ttbar, w+jets, z+jets, qcd2
		self.yields = yields
		self.cn     = cardname;
		self.limit  = 1;
		self.cnbase = ntpath.basename(cardname);
		self.odir   = "/eos/uscms/store/user/ntran/SUSY/combination/output";

	def getYields(self): return self.yields;

	def computeSignificance(self):

			curdir = os.getcwd();

			combineOptions = "";
			combineOptions += "--significance -M ProfileLikelihood "
			combineOptions += " -n "+self.cnbase;
			combineCommand = "combine %s %s" % (combineOptions,curdir+"/"+self.cn);
			#print combineCommand

			outputName = self.odir+"/higgsCombine"+self.cnbase+".ProfileLikelihood.mH120.root";
			if not os.path.isfile(outputName): submitToCondor(combineCommand,self.odir,self.cnbase);
			self.limit = [0]
			if os.path.isfile(outputName): self.limit = self.getSignificance()
			print self.cnbase, self.limit;
			return self.limit;

	def getSignificance(self):

			outputName = self.odir+"/higgsCombine"+self.cnbase+".ProfileLikelihood.mH120.root";
			signif = -1.;
			
			if not os.path.isfile(outputName): 
					print "Warning (getSignificance): "+outputName+" does not exist"
					return signif;

			f = ROOT.TFile(outputName);
			t = f.Get("limit");

			#if not t.GetListOfKeys().Contains("limit"): 
			if not t: 
					print "file is corrupted";
					return signif

			entries = t.GetEntries();
			if entries != 1: print "Warning (getSignificance): number of entries is not 1"
			for i in range(entries):
					t.GetEntry(i);
					signif = t.limit;

			#os.system("rm "+outputName);
			return signif;          

############################################################################################################	
	
class WorkingPointContainer:

	def __init__(self, signaltype, mgluino, binningName, computeBinSig=False):
		
		modelname = "SMS%s%4i_%s" % ( signaltype, mgluino, binningName );
		self.cnbase = modelname;

		self.mGo = mgluino;
		#self.mLSP = mlsp;
		self.ncategoriesNames = ["sig","QCD","z+jets","WjetsTTbar"];
		self.signaltype = signaltype;
		self.binningName = binningName;
		self.theBinning = GetBinning(binningName);

		## ------------------------
		## hard-coded parameters
		#print len(glob.glob("DataCards/"+modelname+"*.txt"));
		nbinsA = len(glob.glob("DataCards/"+modelname+"_?.txt"));
		nbinsB = len(glob.glob("DataCards/"+modelname+"_??.txt"));
		nbinsC = len(glob.glob("DataCards/"+modelname+"_???.txt"));
		#print "DataCards/"+modelname+"_"+binningName+"_?.txt"
		#print nbinsA, nbinsB
		self.nbins = nbinsA+nbinsB+nbinsC;
		self.ncategories = len(self.ncategoriesNames);
		## ------------------------

		self.filenames = [];
		self.binContainers = [];
		self.nRegionsPerBin = [];
		# define bin containers
		self.maxRegions = -99;
		for i in range(self.nbins):
			cn = "DataCards/%s_%i.txt" % ( modelname, i );
			self.filenames.append(cn);
			self.binContainers.append( binContainer(self.parseFileAndGetYields(cn),cn) );
			self.nRegionsPerBin.append(len(self.binContainers[i].yields)/self.ncategories);
			if self.nRegionsPerBin[i] > self.maxRegions: self.maxRegions = self.nRegionsPerBin[i];
			#print len(self.binContainers[i].yields),self.nRegionsPerBin[i]

		# fill signifs
		self.signifs = [1.]*self.nbins;
		self.signifAll = -1.;
			
		# # fill histograms
		self.histos = [];
		hn = "h_mGo%i_datacard_TEST_%s" % ( self.mGo,self.signaltype);
		for i in range(self.maxRegions*self.ncategories):
			self.histos.append( ROOT.TH1F( hn+str(i), ";;yields",self.nbins,0,self.nbins ) );
		
		crosschecktotal = 0;
		for i in range(self.nbins):
			curyields = self.binContainers[i].getYields();
			crosschecktotal += float(curyields[2])
			for j in range(self.maxRegions*self.ncategories):
				if j < len(curyields): self.histos[j].SetBinContent(i+1, float(curyields[j]) );
				else: self.histos[j].SetBinContent(i+1, 0. );
		# print "crosschecktotal = ", crosschecktotal
		

		# define stacks
		# self.sigHist = self.histos[0];
		# self.bkgHist = ROOT.THStack();
		# self.bkgHist.SetTitle(";;yield");
		# colors = [1,2,4,6,7,2];
		# for i in range(1,self.ncategories):
		# 	self.histos[i].SetFillColor( colors[i] );
		# 	self.histos[i].SetFillStyle( 1001 );
		# 	self.bkgHist.Add(self.histos[i]);

		self.sigHists = [];
		self.bkgHists = [];
		for i in range(self.maxRegions):
			self.sigHists.append( self.histos[0+i*self.ncategories] );
			tmpstack = ROOT.THStack();
			tmpstack.SetTitle(";;yield");
			tmpstack.SetName("stackcat"+str(i));
			colors = [1,2,4,6,7,2];			
			for j in range(1,self.ncategories):
				self.histos[j+i*self.ncategories].SetFillColor( colors[j] );
				self.histos[j+i*self.ncategories].SetFillStyle( 1001 );
				tmpstack.Add(self.histos[j+i*self.ncategories]);
			self.bkgHists.append( tmpstack );

		# bin labels
		self.nbinsLabels = [];
		for i in range(self.theBinning.nBins): self.nbinsLabels.append( "bin" + str(i) );

	def parseFileAndGetYields(self,cn):

		f = open(cn,'r');
		yields = [];
		for lines in f:
			if "rate " in lines:
				yields = lines.split();
				del yields[0];
				
		# return yields[1:5];
		return yields;

	def doFullCombination(self,computeBinSig=False):
		
		if computeBinSig:
			for i in range(self.nbins): self.signifs.append( self.binContainers[i].computeSignificance() );

		self.signifAll = self.makeFullCombination();
		print "significance = ",self.signifAll

	def makeCanvas(self,ymax = -99):

		# make full combination! 

		banner = ROOT.TLatex(0.18,0.94,("m_{Gluino} = "+str(self.mGo)));
		banner.SetNDC()
		banner.SetTextSize(0.05)
		bannerS = ROOT.TLatex(0.22,0.54,( "total significance = "+str(round(self.signifAll,2))));
		bannerS.SetNDC()
		bannerS.SetTextSize(0.07)

		for i in range(self.maxRegions):
			for j in range(self.nbins):
				self.sigHists[i].GetXaxis().SetBinLabel(j+1,self.nbinsLabels[j]);
			self.sigHists[i].GetXaxis().SetLabelSize(0.04);
			self.sigHists[i].GetXaxis().LabelsOption("v");

		##--------------------------
		leg = ROOT.TLegend(0.52,0.92,0.92,0.99);
		leg.SetBorderSize(0);
		leg.SetFillStyle(0);
		leg.SetNColumns(self.ncategories);
		for i in range(self.ncategories):
			if i == 0: leg.AddEntry(self.histos[i],self.ncategoriesNames[i],"p");
			if i >= 1: leg.AddEntry(self.histos[i],self.ncategoriesNames[i],"f");

		for i in range(self.maxRegions):
			
			c = ROOT.TCanvas("c"+str(i),"c"+str(i),1400,400);
			#self.sigHist.SetMaximum(self.bkgHist.GetStack().Last().GetMaximum()*100.);
			self.sigHists[i].GetYaxis().SetTitleOffset(0.5);
			self.sigHists[i].SetMaximum(1e4);
			self.sigHists[i].SetMinimum(1e-2);
			self.sigHists[i].Draw();
			self.bkgHists[i].Draw("histsames");
			self.sigHists[i].SetMarkerStyle(24);
			self.sigHists[i].SetMarkerSize(2);        
			self.sigHists[i].Draw("psames");
			ROOT.gPad.SetLogy();
			leg.Draw();
			banner.Draw();
			#c.SaveAs("plots/Yield_"+str

			c.SaveAs("plots/SB_"+str(self.mGo)+"_"+self.signaltype+"binning_"+self.binningName+"_region"+str(i)+".pdf");
			c.SaveAs("plots/SB_"+str(self.mGo)+"_"+self.signaltype+"binning_"+self.binningName+"_region"+str(i)+".png");
			#--------------------------
		# c = ROOT.TCanvas("c","c",1400,1000);
		# #self.sigHist.SetMaximum(self.bkgHist.GetStack().Last().GetMaximum()*100.);
		# self.sigHist.SetMaximum(2e5);
		# self.sigHist.SetMinimum(1e-3);
		# self.sigHist.Draw();
		# self.bkgHist.Draw("histsames");
		# self.sigHist.SetMarkerStyle(24);
		# self.sigHist.SetMarkerSize(2);        
		# self.sigHist.Draw("psames");
		# ROOT.gPad.SetLogy();
		# leg.Draw();
		# banner.Draw();
		# #c.SaveAs("plots/Yield_"+str(self.mGo)+"_"+str(self.mLSP)+"_"+self.anatype+".pdf");
		# #c.SaveAs("plots/Yield_"+str(self.mGo)+"_"+str(self.mLSP)+"_"+self.anatype+".png");
		
		# ##--------------------------
		# hSB1 = ROOT.TH1F("h_SB1",";;Expected significance",self.nbins,0,self.nbins);
		# for i in range(self.nbins):
		# 		sb0 = self.signifs[i];
		# 		hSB1.SetBinContent(i+1,sb0);
		# hSB1.GetXaxis().SetLabelSize(0.00); #hSB1.GetXaxis().LabelsOption("v");
		# hSB1.SetFillStyle(3144);
		# hSB1.SetFillColor(ROOT.kOrange);         

		# self.sigHist.GetXaxis().SetLabelSize(0.035);
		# csb = ROOT.TCanvas("csb","csb",2000,2000);
		# # csb.Divide(1,2);
		# # csb.cd(1);
		# pad1 = ROOT.TPad("pad1","pad1",0.00,0.55,1.00,1.00)
		# pad2 = ROOT.TPad("pad2","pad2",0.00,0.00,1.00,0.55)
		# pad1.SetFillColor(0)
		# pad2.SetFillColor(0)
		# pad1.Draw()
		# pad2.Draw()
		# pad1.SetBottomMargin(0.05);
		# pad2.SetTopMargin(0.05);
		# pad2.cd();         
		# self.sigHist.Draw();
		# self.bkgHist.Draw("histsames");
		# self.sigHist.Draw("psames");
		# ROOT.gPad.SetLogy();
		# leg.Draw();
		# #banner.Draw();        
		# pad1.cd();

		# if ymax > 0: hSB1.SetMaximum(ymax);
		# hSB1.Draw();
		# # leg2.Draw();
		# banner.Draw();
		# bannerS.Draw();

		# # draw lines
		# l1 = ROOT.TLine(24,0,24,ymax);
		# l1.SetLineColor( 2 )
		# l1.Draw();
		# l2 = ROOT.TLine(48,0,48,ymax);
		# l2.SetLineColor( 2 )
		# l2.Draw();
		# l1b = ROOT.TLine(6,0,6,ymax);
		# l1b.SetLineColor( 4 )
		# l1b.Draw();
		# l2b = ROOT.TLine(12,0,12,ymax);
		# l2b.SetLineColor( 4 )
		# l2b.Draw();
		# l3b = ROOT.TLine(18,0,18,ymax);
		# l3b.SetLineColor( 4 )
		# l3b.Draw();
		# banner1 = ROOT.TLatex(0.72,0.84,( "n_{j}" ));
		# banner1.SetNDC()
		# banner1.SetTextColor(2)		
		# banner1.SetTextSize(0.07)
		# banner2 = ROOT.TLatex(0.82,0.84,( "n_{b}" ));
		# banner2.SetNDC()
		# banner2.SetTextColor(4)
		# banner2.SetTextSize(0.07)
		# banner1.Draw();
		# banner2.Draw();

		# csb.SaveAs("plots/SB_"+str(self.mGo)+"_"+self.signaltype+".pdf");
		# csb.SaveAs("plots/SB_"+str(self.mGo)+"_"+self.signaltype+".png");
		##--------------------------

	def makeFullCombination(self):

		idproc = str(self.mGo)+str(self.signaltype);
		combinedcardname = "cardcombined_"+idproc+".txt";

		combineCommand = "combineCards.py ";
		print "len(self.filenames) = ", len(self.filenames)
		cardctr = 0;
		#for i in range(len(self.filenames)):
		for i in range(self.nbins):
			#if i <=100 and i>=36: continue;
			# if self.signifs[i] > 0: 
			combineCommand += self.filenames[i] + " ";
			cardctr += 1
		combineCommand += " > "+combinedcardname;
		os.system(combineCommand);
		print "cardctr = ",cardctr
		# print combineCommand

		combineOptions = "";
		combineOptions += "--signif -M ProfileLikelihood "
		combineOptions += " -n "+idproc
		combineCommand2 = "combine %s %s" % (combineOptions,combinedcardname);
		print combineCommand2
		os.system(combineCommand2);
		
		##---------
		outputName = "higgsCombine"+idproc+".ProfileLikelihood.mH120.root";
		signif = -1.;
		if not os.path.isfile(outputName): print "Warning (makeFullCombination): "+outputName+" does not exist";
		
		f = ROOT.TFile(outputName);
		t = f.Get("limit");
		#if not t.GetListOfKeys().Contains("limit"): 
		if not t: print "file is corrupted";

		entries = t.GetEntries();
		if entries != 1: print "Warning (getSignificance): number of entries is not 1"
		for i in range(entries):
				t.GetEntry(i);
				signif = t.limit;

		os.system("rm "+outputName);
		os.system("rm "+combinedcardname);
		##---------

		return signif;