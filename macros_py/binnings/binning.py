info = """
class which should be used to define binning to 
be used for statistical interpretations.  

A. Whitbeck - June 3, 2014

The constructor takes a list of variable names. 
if these variables truely correspond tree branch
names, it can be used as an iterable list so that
yields for each bin can be computed automatically.

addBin method also one to build up a list of relevant bins
so that the binning for a whole analysis can be 
defined within one single object.  The structure 
of the bin definitions is such that the low edge of 
each cut used for a given bin is store in a dictionary
where the key correspond to the variable of the cut, these
will correspond to the list of variables passed to the construct.
a similar dictionary also exists for the high edge of each
cut to be applied for a given bin.  Note, each element of the 
dict are lists of doubles - one for each bin.
"""


class binning : 
	def __init__( self , branchNameList = [ "HT" , "MHT" , "NJets" , "BTags" ] ) :

		self.branchNames = branchNameList
		self.lowBinEdge = {}
		self.highBinEdge ={}
		self.nBins = 0

		for branchName in branchNameList :
			self.lowBinEdge[ branchName ]  = []
			self.highBinEdge[ branchName ] = []

	def addBin( self , binEdges = [] ) : 

		if len( binEdges ) != len( self.branchNames ) :
			raise InputError("binning::addBin - number of entries in binEdges doesn't match number of branches passed to constructor")
			return 

		for i in range( len( self.branchNames ) ): 
			self.lowBinEdge[ self.branchNames[i] ].append( binEdges[i][0] ) 
			self.highBinEdge[ self.branchNames[i] ].append( binEdges[i][1] ) 

		self.nBins+=1


#################################################################
## binning used for the RA2 analysis
samplebins = binning() # [ "HT" , "MHT" , "NJets" , "BTags" ] )
################ HT cuts #### MHT cuts #### NJet cuts ###
## low jet binning
samplebins.addBin( [ (500 , 800) , (200 , 500)  , (3 , 999) , (-1 , 1) ] )
samplebins.addBin( [ (500 , 800) , (500 , 750)  , (3 , 999) , ( 0 , 9) ] )
# samplebins.addBin( [ (500 , 800) , (750 , 9999) , (3 , 999) ] )
# samplebins.addBin( [ (800 , 1200) , (200 , 500)  , (3 , 999) ] )
# samplebins.addBin( [ (800 , 1200) , (500 , 750)  , (3 , 999) ] )
# samplebins.addBin( [ (800 , 1200) , (750 , 9999) , (3 , 999) ] )
# samplebins.addBin( [ (1200 , 99999) , (200 , 500)  , (3 , 999) ] )
# samplebins.addBin( [ (1200 , 99999) , (500 , 750)  , (3 , 999) ] )
# samplebins.addBin( [ (1200 , 99999) , (750 , 9999) , (3 , 999) ] )
#################################################################

#########################################################################################################
#########################################################################################################
def GetBinning(binning):
    
	if binning == "samplebins" : return samplebins;
	elif binning == "RA2bBins" : return RA2bBins;		
	else :
		raise NameError(binning)
		return;


	