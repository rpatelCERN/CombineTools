void MakeInputs(){
	
	gROOT->ProcessLine(".L MakeCombineDataCards.C++");
	MakeInputHisto("Signal");
	MakeInputHisto("LDP");
	MakeInputHisto("SLEl");
	MakeInputHisto("SLMu");
	MakeInputHisto("GJet");
	MakeInputHisto("DYMu");
}
