void MakeInputs(){
	
	gROOT->ProcessLine(".L MakeCombineDataCards.C++");

	float lumi = 4.;
	int doSMJ = 0;

	MakeInputHisto("Signal",lumi,doSMJ);
	MakeInputHisto("LDP",lumi,doSMJ);
	MakeInputHisto("SLEl",lumi,doSMJ);
	MakeInputHisto("SLMu",lumi,doSMJ);
	MakeInputHisto("GJet",lumi,doSMJ);
	MakeInputHisto("DYMu",lumi,doSMJ);
}
