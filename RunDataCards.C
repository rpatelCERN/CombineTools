void RunDataCards(){
gROOT->ProcessLine(".L ./macros/MakeCombineDataCards_C.so");
    for(int i=0; i<72; ++i){
        MakeCombineDataCards(1500, 100, 4, "T1tttt", true, i);
        MakeCombineDataCards(1200, 800, 4, "T1tttt", true, i);
        MakeCombineDataCards(1500, 100, 4, "T1bbbb", true, i);
        MakeCombineDataCards(1000, 800, 4, "T1bbbb", true, i);
        MakeCombineDataCards(1400, 100, 4, "T1qqqq", true, i);
        MakeCombineDataCards(1000, 900, 4, "T1qqqq", true, i);

	}
   
}
