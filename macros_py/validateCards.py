#!/usr/bin/python
import ROOT
# ROOT.gROOT.ProcessLine(".L ~/tdrstyle.C");
# ROOT.setTDRStyle();
# ROOT.gStyle.SetPadTopMargin(0.09);
# ROOT.gStyle.SetPadLeftMargin(0.16);
# ROOT.gStyle.SetPadRightMargin(0.06);
# ROOT.gStyle.SetPadBottomMargin(0.35);
# ROOT.gStyle.SetPalette(1);
# ROOT.gStyle.SetErrorX(0.5);

from containers import *

############################################
#            Job steering                  #
############################################
from optparse import OptionParser

parser = OptionParser()
parser.add_option('-b', action='store_true', dest='noX', default=False, help='no X11 windows')
parser.add_option('--doEachBin',action="store_true",dest="doEachBin",default=False,help='do training')
parser.add_option('--makeCanvas',action="store_true",dest="makeCanvas",default=False,help='do training')
parser.add_option("--binning",dest="binning",default="RA2bBins",help="Select binning to be used: Classic, SMJ, extSMJ", metavar="binning")

(options, args) = parser.parse_args()

############################################################


## ------------------------------------------------------------
## ------------------------------------------------------------
## ------------------------------------------------------------

if __name__ == '__main__':

	doEachBin = options.doEachBin;
	binningName = options.binning;
	ymax = 4.;

	wp1 = WorkingPointContainer( "tttt", 1500, binningName, doEachBin);
	wp2 = WorkingPointContainer( "tttt", 1200, binningName, doEachBin);
	wp3 = WorkingPointContainer( "bbbb", 1500, binningName, doEachBin);
	wp4 = WorkingPointContainer( "bbbb", 1000, binningName, doEachBin);
	wp5 = WorkingPointContainer( "qqqq", 1400, binningName, doEachBin);
	wp6 = WorkingPointContainer( "qqqq", 1000, binningName, doEachBin);

	wp1.doFullCombination(options.doEachBin)
	wp2.doFullCombination(options.doEachBin)
	wp3.doFullCombination(options.doEachBin)
	wp4.doFullCombination(options.doEachBin)
	wp5.doFullCombination(options.doEachBin)
	wp6.doFullCombination(options.doEachBin)

	wp1.makeCanvas(ymax);
	wp2.makeCanvas(ymax);
	wp3.makeCanvas(ymax);
	wp4.makeCanvas(ymax);
	wp5.makeCanvas(ymax);
	wp6.makeCanvas(ymax);