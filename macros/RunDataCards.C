void RunDataCards(){
	
	gROOT->ProcessLine(".L MakeCombineDataCards.C++");
    for(int i=0; i<72; ++i){
    	MakeCombineDataCards(1500, 100, 1.0, 4, "T1tttt", i);
        // MakeCombineDataCards(1200, 800, 1.0, 4, "T1tttt", i);
        // MakeCombineDataCards(1500, 100, 1.0, 4, "T1bbbb", i);
        // MakeCombineDataCards(1000, 800, 1.0, 4, "T1bbbb", i);
        // MakeCombineDataCards(1400, 100, 1.0, 4, "T1qqqq", i);
        // MakeCombineDataCards(1000, 900, 1.0, 4, "T1qqqq", i);
	}
}
