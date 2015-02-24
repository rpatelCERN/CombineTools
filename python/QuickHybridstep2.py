import os
import sys
import random
import time
basecommand="combine -M HybridNew --frequentist"

options=" --significance --readHybridResult --expectedFromGrid=0.5"
datacard="LowbkgStatsCar.dat"
toysfile=sys.argv[1]#"higgsCombineDummyTestBin0Combine.HybridNew.root"
os.system("%s -d %s %s --toysFile %s -S 1" %(basecommand, datacard, options, toysfile))
