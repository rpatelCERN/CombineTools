//
//  MakeCombineDataCards.C
//  
//
//  Created by Rishi Patel on 2/10/15.
//
//

#include <TH3F.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <stdio.h>
#include <TString.h>
#include <TGraph.h>
#include <TCanvas.h>
#include<TH1F.h>
#include<TRandom.h>
const int totalbins=72; //hard coded to default 72 analysis bins

float sig4t1500[totalbins];
float sig4t1200[totalbins];
float sig4q1400[totalbins];
float sig4q1000[totalbins];
float sig4b1500[totalbins];
float sig4b1000[totalbins];

float sig4t1500raw[totalbins];
float sig4t1200raw[totalbins];
float sig4q1400raw[totalbins];
float sig4q1000raw[totalbins];
float sig4b1500raw[totalbins];
float sig4b1000raw[totalbins];

int Bbins[totalbins];
int njbins[totalbins];
int mbins[totalbins];
float qcd[totalbins];
float zi[totalbins];
float wj[totalbins];
float ttbar[totalbins];
float SL[totalbins];
float LDP[totalbins];
float GJet[totalbins];

//leakage terms for signal and background contamination in CR bins:
float QCDSL[totalbins];
float ZSL[totalbins];
float sig4t1500SL[totalbins];
float sig4t1200SL[totalbins];
float sig4q1400SL[totalbins];
float sig4q1000SL[totalbins];
float sig4b1500SL[totalbins];
float sig4b1000SL[totalbins];

float SLLDP[totalbins];
float ZLDP[totalbins];
float sigLDP[totalbins];
float sigSL[totalbins];

float sig4t1500LDP[totalbins];
float sig4t1200LDP[totalbins];
float sig4q1400LDP[totalbins];
float sig4q1000LDP[totalbins];
float sig4b1500LDP[totalbins];
float sig4b1000LDP[totalbins];

float QCDPho[totalbins];
float SLPho[totalbins];
float sigPho[totalbins];

float sig4t1500Pho[totalbins];
float sig4t1200Pho[totalbins];
float sig4q1400Pho[totalbins];
float sig4q1000Pho[totalbins];
float sig4b1500Pho[totalbins];
float sig4b1000Pho[totalbins];


void MakeInputHisto(TString Options="Signal", float lumi=4){  //all input files
    
    std::cout << "Processing with option = " << Options << std::endl;
    //HT30:MHT:NJets30
    string HTString = "HT";
    string MHTString  = "MHT";
    string NJString = "NJets";
    if(Options=="GJet"){
        HTString = "HTnoPhotons";
        MHTString = "MHTnoPhotons";
    }



    const int nBinsjets = 3 ;
    const int nBinsBjets = 4 ;
    const int nBinsMHT = 3 ;
    const int nBinsHT = 3 ;
    //float METBinRectangular[4]={200, 500., 750.,9999.};
    
    float MHTBinRectangular[4]={200, 500., 750.,9999.};
    float HTBinRectangular[4]={500., 800., 1200.,9999.};//can do 150 to
    
    char bcutstringRectangular[nBinsBjets][100] = { "BTags==0", "BTags==1","BTags==2", "BTags>=3" } ;
    float NJets[4]={4, 7,9,99};
    //these are in an eos area on lxplus:/eos/cms/store/user/rpatel/RA2b
    TChain t1tt1500("TreeMaker2/PreSelection");
    t1tt1500.Add(TString::Format("./LatestSynchFiles/SMStttt1500.root"));
    TChain t1tt1200("TreeMaker2/PreSelection");
    t1tt1200.Add(TString::Format("./LatestSynchFiles/SMStttt1200.root"));
    TChain t1bb1000("TreeMaker2/PreSelection");
    t1bb1000.Add(TString::Format("./LatestSynchFiles/SMSbbbb1000.root"));
    TChain t1bb1500("TreeMaker2/PreSelection");
    t1bb1500.Add(TString::Format("./LatestSynchFiles/SMSbbbb1500.root"));
    TChain t1qq1000("TreeMaker2/PreSelection");
    t1qq1000.Add(TString::Format("./LatestSynchFiles/SMSqqqq1000.root"));
    TChain t1qq1400("TreeMaker2/PreSelection");
    t1qq1400.Add(TString::Format("./LatestSynchFiles/SMSqqqq1400.root"));
    
    TChain QCDCH("TreeMaker2/PreSelection") ;
    QCDCH.Add("./LatestSynchFiles/QCDHT.root");

    TChain WJets("TreeMaker2/PreSelection");
    WJets.Add("./LatestSynchFiles/WJ.root");

    TChain tt("TreeMaker2/PreSelection");
    tt.Add("./LatestSynchFiles/TTJets.root");
    
    TChain Zinv("TreeMaker2/PreSelection") ;
    Zinv.Add("./LatestSynchFiles/ZJ.root");
    
    TChain GJets("TreeMaker2/PreSelection") ;
    GJets.Add("./LatestSynchFiles/GJ.root");

    TChain DY("TreeMaker2/PreSelection") ;
    DY.Add("./LatestSynchFiles/DY.root");
    
    char commoncuts[10000] ;
    TString fileBaseName;
    if(Options=="Signal"){
        sprintf( commoncuts,"HT>500 && NJets>=4 && MHT>200 && (MuonsNum==0 && ElectronsNum==0) && abs(minDeltaPhiN)>4.0 && isoTracks==0" ); //signal region selection
        fileBaseName=TString::Format("Bins4DBINS_Lumi%2.2ffb.root",lumi);
    }
    if(Options=="LDP"){
        sprintf( commoncuts,"HT>500 && NJets>=4 && MHT>200 && (MuonsNum==0 && ElectronsNum==0) && abs(minDeltaPhiN)<4.0 && isoTracks==0" ); //LowDelPhi region selection
        fileBaseName=TString::Format("Bins4DLDP_Lumi%2.2ffb.root",lumi);
    }
    if(Options=="SLEl"){
        sprintf( commoncuts,"(HT>500 && NJets>=4 && MHT>200 && abs(minDeltaPhiN)>4.0 && (MuonsNum==0 && ElectronsNum==1) && ( sqrt(2 *METPt*ElectronsPt[0]*(1-cos(ElectronsPhi[0]-METPhi)))<100  ))");//Single Lepton region selection
        fileBaseName=TString::Format("Bins4DSLEl_Lumi%2.2ffb.root",lumi);
    }
    if(Options=="SLMu"){
        sprintf( commoncuts,"(HT>500 && NJets>=4 && MHT>200 && abs(minDeltaPhiN)>4.0 && (MuonsNum==1 && ElectronsNum==0) && ( sqrt(2 *METPt*MuonsPt[0]*(1-cos(MuonsPhi[0]-METPhi)))<100  ))");//Single Lepton region selection
        fileBaseName=TString::Format("Bins4DSLMu_Lumi%2.2ffb.root",lumi);
    }
    if(Options=="GJet"){
        sprintf( commoncuts,"(HTnoPhotons>500 && NJets>=4 && MHTnoPhotons>200 && abs(minDeltaPhiNnoPhotons)>4.0 && (Photons == 1))");//Single Lepton region selection
        fileBaseName=TString::Format("Bins4DGJet_Lumi%2.2ffb.root",lumi);
    }
    if(Options=="DYMu"){
        sprintf( commoncuts,"(HT>500 && NJets>=4 && MHT>200 && abs(minDeltaPhiN)>4.0 && (MuonsNum==2 && ElectronsNum==0))");//Single Lepton region selection
        fileBaseName=TString::Format("Bins4DYMu_Lumi%2.2ffb.root",lumi);
    }

    char weightstring[10000];
    sprintf(weightstring, "*(lheWeight*%e)", lumi); //bkg xsec weight
    
    char arg1[1000] ;
    char cuts[10000];
    char cutsUW[10000];

    //yields stored in a TH3* (one for each btag) so 4D
    TH3F*sig4t1200_[4];
    TH3F*sig4t1500_[4];
    
    TH3F*sig4b1500_[4];
    TH3F*sig4b1000_[4];
    TH3F*sig4q1400_[4];
    TH3F*sig4q1000_[4];
    
    TH3F*sig4t1200Raw_[4];
    TH3F*sig4t1500Raw_[4];
    
    TH3F*sig4b1500Raw_[4];
    TH3F*sig4b1000Raw_[4];
    TH3F*sig4q1400Raw_[4];
    TH3F*sig4q1000Raw_[4];
    
    TH3F*qcd_[4];
    TH3F*tt_[4];
    TH3F*WJ_[4];
    TH3F*ZI_[4];
    TH3F*GJ_[4];
    TH3F*DY_[4];

    //REALLY NEED TO ONLY DO THIS ONCE for the same binning and a particular luminosity scale
    TFile*f0=new TFile(TString::Format("%s", fileBaseName.Data()).Data(), "RECREATE");
    for(int b=0; b<nBinsBjets; ++b){
        
        std::cout << "Nb = " << b << std::endl;

        sig4t1500_[b]=new TH3F(TString::Format("sig4t1500__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        sig4t1200_[b]=new TH3F(TString::Format("sig4t1200__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        
        
        sig4b1500_[b]=new TH3F(TString::Format("sig4b1500__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        sig4b1000_[b]=new TH3F(TString::Format("sig4b1000__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        
        sig4q1000_[b]=new TH3F(TString::Format("sig4q1000__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        sig4q1400_[b]=new TH3F(TString::Format("sig4q1400__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        
        
        
        sig4t1500Raw_[b]=new TH3F(TString::Format("sig4t1500Raw__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        sig4t1200Raw_[b]=new TH3F(TString::Format("sig4t1200Raw__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        
        
        sig4b1500Raw_[b]=new TH3F(TString::Format("sig4b1500Raw__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        sig4b1000Raw_[b]=new TH3F(TString::Format("sig4b1000Raw__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        
        sig4q1000Raw_[b]=new TH3F(TString::Format("sig4q1000Raw__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        sig4q1400Raw_[b]=new TH3F(TString::Format("sig4q1400Raw__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        

        qcd_[b]=new TH3F(TString::Format("qcd__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular, nBinsHT,HTBinRectangular );
        tt_[b]=new TH3F(TString::Format("tt__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        WJ_[b]=new TH3F(TString::Format("WJ__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        ZI_[b]=new TH3F(TString::Format("ZI__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        GJ_[b]=new TH3F(TString::Format("GJ__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        DY_[b]=new TH3F(TString::Format("DY__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        
        
        sprintf( cuts, "(%s && %s )*(lheWeight*%e)", commoncuts,bcutstringRectangular[b],lumi );
        sprintf( cutsUW, "(%s && %s )", commoncuts,bcutstringRectangular[b] );

        sprintf( arg1, TString::Format("%s:%s:%s>>sig4t1500__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;
        t1tt1500.Draw( arg1, cuts );
        sprintf( arg1, TString::Format("%s:%s:%s>>sig4t1200__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;
        t1tt1200.Draw( arg1, cuts );
        
        sprintf( arg1, TString::Format("%s:%s:%s>>sig4q1400__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;        
        t1qq1400.Draw( arg1, cuts );
        sprintf( arg1, TString::Format("%s:%s:%s>>sig4q1000__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;        
        t1qq1000.Draw( arg1, cuts );
        
        sprintf( arg1, TString::Format("%s:%s:%s>>sig4b1500__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;        
        t1bb1500.Draw( arg1, cuts );
        sprintf( arg1, TString::Format("%s:%s:%s>>sig4b1000__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;        
        t1bb1000.Draw( arg1, cuts );
        
        
        sprintf( arg1, TString::Format("%s:%s:%s>>sig4t1500Raw__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;
        t1tt1500.Draw( arg1, cutsUW );
        sprintf( arg1, TString::Format("%s:%s:%s>>sig4t1200Raw__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;
        t1tt1200.Draw( arg1, cutsUW );
        
        sprintf( arg1, TString::Format("%s:%s:%s>>sig4q1400Raw__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;        
        t1qq1400.Draw( arg1, cutsUW );
        sprintf( arg1, TString::Format("%s:%s:%s>>sig4q1000Raw__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;        
        t1qq1000.Draw( arg1, cutsUW );
        
        sprintf( arg1, TString::Format("%s:%s:%s>>sig4b1500Raw__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;        
        t1bb1500.Draw( arg1, cutsUW );
        sprintf( arg1, TString::Format("%s:%s:%s>>sig4b1000Raw__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;        
        t1bb1000.Draw( arg1, cutsUW );
        
        sprintf( arg1, TString::Format("%s:%s:%s>>qcd__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;                
        QCDCH.Draw( arg1, cuts ) ;
        sprintf( arg1, TString::Format("%s:%s:%s>>tt__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;                
        tt.Draw( arg1, cuts ) ;
        sprintf( arg1, TString::Format("%s:%s:%s>>WJ__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;                
        WJets.Draw( arg1, cuts );
        sprintf( arg1, TString::Format("%s:%s:%s>>ZI__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;                
        Zinv.Draw( arg1, cuts ) ;
        sprintf( arg1, TString::Format("%s:%s:%s>>GJ__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;                
        GJets.Draw( arg1, cuts ) ;
        sprintf( arg1, TString::Format("%s:%s:%s>>DY__b%d",HTString.c_str(),MHTString.c_str(),NJString.c_str(),b).Data()) ;                
        DY.Draw( arg1, cuts ) ;

        sig4t1500_[b]->Write();
        sig4t1200_[b]->Write();
        sig4q1000_[b]->Write();
        sig4q1400_[b]->Write();
        sig4b1500_[b]->Write();
        sig4b1000_[b]->Write();
    
        sig4t1500Raw_[b]->Write();
        sig4t1200Raw_[b]->Write();
        sig4q1000Raw_[b]->Write();
        sig4q1400Raw_[b]->Write();
        sig4b1500Raw_[b]->Write();
        sig4b1000Raw_[b]->Write();
        
        qcd_[b]->Write();
        WJ_[b]->Write();
        tt_[b]->Write();
        ZI_[b]->Write();
        GJ_[b]->Write();
        DY_[b]->Write();

    }
    f0->Close();

}
//THIS DEFINES THE BINNING and PRODUCES THE LATEX TABLE
void fillEventYields(float lumi=4.0){

    TH3F*sig4t1200_[4];
    TH3F*sig4t1500_[4];
    
    TH3F*sig4b1500_[4];
    TH3F*sig4b1000_[4];
    TH3F*sig4q1400_[4];
    TH3F*sig4q1000_[4];
    
    TH3F*sig4t1200SL_[4];
    TH3F*sig4t1500SL_[4];
    TH3F*sig4b1500SL_[4];
    TH3F*sig4b1000SL_[4];
    TH3F*sig4q1400SL_[4];
    TH3F*sig4q1000SL_[4];
    
    TH3F*sig4t1200LDP_[4];
    TH3F*sig4t1500LDP_[4];
    TH3F*sig4b1500LDP_[4];
    TH3F*sig4b1000LDP_[4];
    TH3F*sig4q1400LDP_[4];
    TH3F*sig4q1000LDP_[4];
    
    TH3F*sig4t1200Pho_[4];
    TH3F*sig4t1500Pho_[4];
    TH3F*sig4b1500Pho_[4];
    TH3F*sig4b1000Pho_[4];
    TH3F*sig4q1400Pho_[4];
    TH3F*sig4q1000Pho_[4];
    
    TH3F*sig4t1200raw_[4];
    TH3F*sig4t1500raw_[4];
    TH3F*sig4b1500raw_[4];
    TH3F*sig4b1000raw_[4];
    TH3F*sig4q1400raw_[4];
    TH3F*sig4q1000raw_[4];
    
    TH3F*qcd_[4];
    TH3F*tt_[4];
    TH3F*WJ_[4];
    TH3F*ZI_[4];
    //SL
    TH3F*ttSL_[4];
    TH3F*WJSL_[4];
    TH3F*zSL_[4];
    TH3F*QCDSL_[4];
    //0L
    TH3F*qcdLDP_[4];
    TH3F*ttLDP_[4];
    TH3F*WJLDP_[4];
    TH3F*ZLDP_[4];
    //GJets
    TH3F*ziGJet_[4];
    TH3F*qcdPho_[4];
    TH3F*ttPho_[4];
    TH3F*WJPho_[4];
    
    
    TFile*f0=new TFile(TString::Format("Bins4DBINS_Lumi%2.2ffb.root", lumi).Data());
    TFile*f1=new TFile(TString::Format("Bins4DSL_Lumi%2.2ffb.root", lumi).Data());
    TFile*f2=new TFile(TString::Format("Bins4DLDP_Lumi%2.2ffb.root", lumi).Data());
    TFile*f3=new TFile(TString::Format("Bins4DGJet_Lumi%2.2ffb.root", lumi).Data());

    for(int b=0; b<4; ++b){

        sig4t1500_[b]=(TH3F*)f0->Get(TString::Format("sig4t1500__b%d",b).Data());
        sig4t1200_[b]=(TH3F*)f0->Get(TString::Format("sig4t1200__b%d",b).Data());
        
        sig4b1500_[b]=(TH3F*)f0->Get(TString::Format("sig4b1500__b%d",b).Data());
        sig4b1000_[b]=(TH3F*)f0->Get(TString::Format("sig4b1000__b%d",b).Data());
        
        sig4q1400_[b]=(TH3F*)f0->Get(TString::Format("sig4q1400__b%d",b).Data());
        sig4q1000_[b]=(TH3F*)f0->Get(TString::Format("sig4q1000__b%d",b).Data());
        
        sig4t1500SL_[b]=(TH3F*)f1->Get(TString::Format("sig4t1500__b%d",b).Data());
        sig4t1200SL_[b]=(TH3F*)f1->Get(TString::Format("sig4t1200__b%d",b).Data());
        sig4b1500SL_[b]=(TH3F*)f1->Get(TString::Format("sig4b1500__b%d",b).Data());
        sig4b1000SL_[b]=(TH3F*)f1->Get(TString::Format("sig4b1000__b%d",b).Data());
        sig4q1400SL_[b]=(TH3F*)f1->Get(TString::Format("sig4q1400__b%d",b).Data());
        sig4q1000SL_[b]=(TH3F*)f1->Get(TString::Format("sig4q1000__b%d",b).Data());
        
        sig4t1500LDP_[b]=(TH3F*)f2->Get(TString::Format("sig4t1500__b%d",b).Data());
        sig4t1200LDP_[b]=(TH3F*)f2->Get(TString::Format("sig4t1200__b%d",b).Data());
        sig4b1500LDP_[b]=(TH3F*)f2->Get(TString::Format("sig4b1500__b%d",b).Data());
        sig4b1000LDP_[b]=(TH3F*)f2->Get(TString::Format("sig4b1000__b%d",b).Data());
        sig4q1400LDP_[b]=(TH3F*)f2->Get(TString::Format("sig4q1400__b%d",b).Data());
        sig4q1000LDP_[b]=(TH3F*)f2->Get(TString::Format("sig4q1000__b%d",b).Data());
        
        sig4t1500Pho_[b]=(TH3F*)f3->Get(TString::Format("sig4t1500__b%d",b).Data());
        sig4t1200Pho_[b]=(TH3F*)f3->Get(TString::Format("sig4t1200__b%d",b).Data());
        sig4b1500Pho_[b]=(TH3F*)f3->Get(TString::Format("sig4b1500__b%d",b).Data());
        sig4b1000Pho_[b]=(TH3F*)f3->Get(TString::Format("sig4b1000__b%d",b).Data());
        sig4q1400Pho_[b]=(TH3F*)f3->Get(TString::Format("sig4q1400__b%d",b).Data());
        sig4q1000Pho_[b]=(TH3F*)f3->Get(TString::Format("sig4q1000__b%d",b).Data());
        
        sig4t1500raw_[b]=(TH3F*)f0->Get(TString::Format("sig4t1500Raw__b%d",b).Data());
        sig4t1200raw_[b]=(TH3F*)f0->Get(TString::Format("sig4t1200Raw__b%d",b).Data());
        
        sig4b1500raw_[b]=(TH3F*)f0->Get(TString::Format("sig4b1500Raw__b%d",b).Data());
        sig4b1000raw_[b]=(TH3F*)f0->Get(TString::Format("sig4b1000Raw__b%d",b).Data());
        
        sig4q1400raw_[b]=(TH3F*)f0->Get(TString::Format("sig4q1400Raw__b%d",b).Data());
        sig4q1000raw_[b]=(TH3F*)f0->Get(TString::Format("sig4q1000Raw__b%d",b).Data());
        
        qcd_[b]=(TH3F*)f0->Get(TString::Format("qcd__b%d",b).Data());
        tt_[b]=(TH3F*)f0->Get(TString::Format("tt__b%d",b).Data());
        WJ_[b]=(TH3F*)f0->Get(TString::Format("WJ__b%d",b).Data());
        ZI_[b]=(TH3F*)f0->Get(TString::Format("ZI__b%d",b).Data());
        
        ttSL_[b]=(TH3F*)f1->Get(TString::Format("tt__b%d",b).Data());
        WJSL_[b]=(TH3F*)f1->Get(TString::Format("WJ__b%d",b).Data());
        zSL_[b]=(TH3F*)f1->Get(TString::Format("ZI__b%d",b).Data());
        QCDSL_[b]=(TH3F*)f1->Get(TString::Format("qcd__b%d",b).Data());
        
        qcdLDP_[b]=(TH3F*)f2->Get(TString::Format("qcd__b%d",b).Data());
        ttLDP_[b]=(TH3F*)f2->Get(TString::Format("tt__b%d",b).Data());
        WJLDP_[b]=(TH3F*)f2->Get(TString::Format("WJ__b%d",b).Data());
        ZLDP_[b]=(TH3F*)f2->Get(TString::Format("ZI__b%d",b).Data());
        
        ziGJet_[b]=(TH3F*)f3->Get(TString::Format("GJ__b%d",b).Data());
        qcdPho_[b]=(TH3F*)f3->Get(TString::Format("qcd__b%d",b).Data());
        ttPho_[b]=(TH3F*)f3->Get(TString::Format("tt__b%d",b).Data());
        WJPho_[b]=(TH3F*)f3->Get(TString::Format("WJ__b%d",b).Data());
        
    }
    
    //signal strength
    FILE* fp = fopen(  "OutputTable.tex", "w" ) ;
/*
    TH1F*sig=new TH1F("sig", "", 72, 0,71);

    TH1F*data_obs=new TH1F("data_obs", "", 72, 0,71);

    
    
    TH1F*data_obs0L=new TH1F("data_obs0L", "", 72, 0,71);
    TH1F*data_obs1L=new TH1F("data_obs1L", "", 72, 0,71);
    
    TH1F*QCD=new TH1F("QCD", "", 72, 0,71);
    TH1F*WJttbar=new TH1F("WJttbar", "", 72, 0,71);
    TH1F*Zinv=new TH1F("Zinv", "", 72, 0,71);
    
    TH1F*sig_0L=new TH1F("sig_0L", "", 72, 0,71);//never fill this
    TH1F*QCD_0L=new TH1F("QCD_0L", "", 72, 0,71);
    TH1F*WJttbar_0L=new TH1F("WJttbar_0L", "", 72, 0,71);//never fill this
    TH1F*Zinv_0L=new TH1F("Zinv_0L", "", 72, 0,71);//never fill this
    
    TH1F*sig_1L=new TH1F("sig_1L", "", 72, 0,71);//never fill this
    TH1F*QCD_1L=new TH1F("QCD_1L", "", 72, 0,71);//never fill this
    TH1F*WJttbar_1L=new TH1F("WJttbar_1L", "", 72, 0,71);
    TH1F*Zinv_1L=new TH1F("Zinv_1L", "", 72, 0,71);//never fill this
*/

    fprintf(fp, "\\documentclass[10pt,a4paper]{article}\n");
    fprintf(fp, "\\usepackage[utf8]{inputenc}\n");
    fprintf(fp, "\\usepackage{amsmath}\n");
    fprintf(fp, "\\usepackage{amsfonts}\n");
    fprintf(fp, "\\usepackage{amssymb}\n");
    fprintf(fp, "\\usepackage{multirow}\n");
    fprintf(fp,"\\usepackage{graphicx}\n");
    
    fprintf(fp, "\\begin{document}\n");
    fprintf(fp, "\\begin{table}\n");
    fprintf(fp,"\\resizebox{1.2\\textwidth}{0.95\\textwidth}{\n");
    
    fprintf(fp, "\\begin{tabular}{|l|c|c|c|c|c|c|c|c|c|c|}\n");;
    fprintf(fp, "\\hline\n");
    fprintf(fp, "\\hline\n");
    fprintf(fp, "\\multicolumn{6}{ |c| }{Signal and Background Yields} \\\\\n");
    fprintf(fp, "\\hline\n");
    fprintf(fp, "\\hline\n");
    fprintf(fp,"&QCD&ttbar&Z&W&T1tttt&T1tttt&T1qqqq&T1qqqq&T1bbbb&T1bbbb\\\\\n");
    fprintf(fp, "& & & & &$M_{glu},M_{\\chi}$ & $M_{glu},M_{\\chi}$ &$M_{glu},M_{\\chi}$ & $M_{glu},M_{\\chi}$ & $M_{glu},M_{\\chi}$ &$M_{glu},M_{\\chi}$\\\\\n");
    fprintf(fp, "& & & & &1500,100 & 1200,800 &1400,100 & 1000,800 & 1500,100 &1200,900 \\\\\n");
    fprintf(fp,"\\hline\n");
    
    int boxcount=0;
    int ibin=0;
    for ( int ij=1; ij<=3; ij++ ) {
        for(int nb=0; nb<=3; nb++){
            for ( int mhti=1; mhti<=3; mhti++ ){
                for ( int hti=1; hti<=3; hti++ ) {

                    if(hti<2 && mhti==3)continue;
                    
                    if(mhti==1){
                        boxcount=hti+mhti-1;
                        sig4t1500[ibin]=sig4t1500_[nb]->GetBinContent( ij, mhti, hti );
                        sig4t1200[ibin]=sig4t1200_[nb]->GetBinContent( ij, mhti, hti );
                        sig4q1400[ibin]=sig4q1400_[nb]->GetBinContent( ij, mhti, hti );
                        sig4q1000[ibin]=sig4q1000_[nb]->GetBinContent( ij, mhti, hti );
                        sig4b1500[ibin]=sig4b1500_[nb]->GetBinContent( ij, mhti, hti );
                        sig4b1000[ibin]=sig4b1000_[nb]->GetBinContent( ij, mhti, hti );
                        
                        sig4t1500raw[ibin]=sig4t1500raw_[nb]->GetBinContent( ij, mhti, hti );
                        sig4t1200raw[ibin]=sig4t1200raw_[nb]->GetBinContent( ij, mhti, hti );
                        sig4q1400raw[ibin]=sig4q1400raw_[nb]->GetBinContent( ij, mhti, hti );
                        sig4q1000raw[ibin]=sig4q1000raw_[nb]->GetBinContent( ij, mhti, hti );
                        sig4b1500raw[ibin]=sig4b1500raw_[nb]->GetBinContent( ij, mhti, hti );
                        sig4b1000raw[ibin]=sig4b1000raw_[nb]->GetBinContent( ij, mhti, hti );
                        
                        sig4t1500SL[ibin]=sig4t1500SL_[nb]->GetBinContent( ij, mhti, hti );
                        sig4t1200SL[ibin]=sig4t1200SL_[nb]->GetBinContent( ij, mhti, hti );
                        sig4q1400SL[ibin]=sig4q1400SL_[nb]->GetBinContent( ij, mhti, hti );
                        sig4q1000SL[ibin]=sig4q1000SL_[nb]->GetBinContent( ij, mhti, hti );
                        sig4b1500SL[ibin]=sig4b1500SL_[nb]->GetBinContent( ij, mhti, hti );
                        sig4b1000SL[ibin]=sig4b1000SL_[nb]->GetBinContent( ij, mhti, hti );
                        
                        sig4t1500LDP[ibin]=sig4t1500LDP_[nb]->GetBinContent( ij, mhti, hti );
                        sig4t1200LDP[ibin]=sig4t1200LDP_[nb]->GetBinContent( ij, mhti, hti );
                        sig4q1400LDP[ibin]=sig4q1400LDP_[nb]->GetBinContent( ij, mhti, hti );
                        sig4q1000LDP[ibin]=sig4q1000LDP_[nb]->GetBinContent( ij, mhti, hti );
                        sig4b1500LDP[ibin]=sig4b1500LDP_[nb]->GetBinContent( ij, mhti, hti );
                        sig4b1000LDP[ibin]=sig4b1000LDP_[nb]->GetBinContent( ij, mhti, hti );
                        
                        sig4t1500Pho[ibin]=sig4t1500Pho_[nb]->GetBinContent( ij, mhti, hti );
                        sig4t1200Pho[ibin]=sig4t1200Pho_[nb]->GetBinContent( ij, mhti, hti );
                        sig4q1400Pho[ibin]=sig4q1400Pho_[nb]->GetBinContent( ij, mhti, hti );
                        sig4q1000Pho[ibin]=sig4q1000Pho_[nb]->GetBinContent( ij, mhti, hti );
                        sig4b1500Pho[ibin]=sig4b1500Pho_[nb]->GetBinContent( ij, mhti, hti );
                        sig4b1000Pho[ibin]=sig4b1000Pho_[nb]->GetBinContent( ij, mhti, hti );
                        
                        qcd[ibin]=qcd_[nb]->GetBinContent( ij, mhti, hti );
                        zi[ibin]=ZI_[nb]->GetBinContent( ij, mhti, hti );
                        wj[ibin]=WJ_[nb]->GetBinContent( ij, mhti, hti );
                        ttbar[ibin]=tt_[nb]->GetBinContent( ij, mhti, hti );
                        SL[ibin]= WJSL_[nb]->GetBinContent(ij, mhti, hti)+ttSL_[nb]->GetBinContent(ij, mhti, hti);
                        QCDSL[ibin]=QCDSL_[nb]->GetBinContent(ij, mhti, hti);
                        ZSL[ibin]=zSL_[nb]->GetBinContent(ij, mhti, hti);

                        
                        LDP[ibin]= qcdLDP_[nb]->GetBinContent(ij, mhti, hti);
                        SLLDP[ibin]=WJLDP_[nb]->GetBinContent(ij, mhti, hti)+ttLDP_[nb]->GetBinContent(ij, mhti, hti);
                        ZLDP[ibin]=ZLDP_[nb]->GetBinContent(ij, mhti, hti);
                        
                        GJet[ibin] = ziGJet_[nb]->GetBinContent(ij, mhti, hti);
                        QCDPho[ibin]= qcdPho_[nb]->GetBinContent(ij, mhti, hti);
                        SLPho[ibin]=WJPho_[nb]->GetBinContent(ij, mhti, hti)+ttPho_[nb]->GetBinContent(ij, mhti, hti);
                        
                        
                        ++ibin;
                        
                    }
                    
                    if(mhti==3){
                        if(hti==3)continue;
                        boxcount=4+hti;
                        
                        sig4t1500[ibin]=sig4t1500_[nb]->GetBinContent( ij, mhti, 2 )+sig4t1500_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4t1200[ibin]=sig4t1200_[nb]->GetBinContent( ij, mhti, 2 )+sig4t1200_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4q1400[ibin]=sig4q1400_[nb]->GetBinContent( ij, mhti, 2 )+sig4q1400_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4q1000[ibin]=sig4q1000_[nb]->GetBinContent( ij, mhti, 2 )+sig4q1000_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4b1500[ibin]=sig4b1500_[nb]->GetBinContent( ij, mhti, 2 )+sig4b1500_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4b1000[ibin]=sig4b1000_[nb]->GetBinContent( ij, mhti, 2 )+sig4b1000_[nb]->GetBinContent( ij, mhti, 3 );
                        
                        sig4t1500SL[ibin]=sig4t1500SL_[nb]->GetBinContent( ij, mhti, 2 )+sig4t1500SL_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4t1200SL[ibin]=sig4t1200SL_[nb]->GetBinContent( ij, mhti, 2 )+sig4t1200SL_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4q1400SL[ibin]=sig4q1400SL_[nb]->GetBinContent( ij, mhti, 2 )+sig4q1400SL_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4q1000SL[ibin]=sig4q1000SL_[nb]->GetBinContent( ij, mhti, 2 )+sig4q1000SL_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4b1500SL[ibin]=sig4b1500SL_[nb]->GetBinContent( ij, mhti, 2 )+sig4b1500SL_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4b1000SL[ibin]=sig4b1000SL_[nb]->GetBinContent( ij, mhti, 2 )+sig4b1000SL_[nb]->GetBinContent( ij, mhti, 3 );
                        
                        sig4t1500LDP[ibin]=sig4t1500LDP_[nb]->GetBinContent( ij, mhti, 2 )+sig4t1500LDP_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4t1200LDP[ibin]=sig4t1200LDP_[nb]->GetBinContent( ij, mhti, 2 )+sig4t1200LDP_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4q1400LDP[ibin]=sig4q1400LDP_[nb]->GetBinContent( ij, mhti, 2 )+sig4q1400LDP_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4q1000LDP[ibin]=sig4q1000LDP_[nb]->GetBinContent( ij, mhti, 2 )+sig4q1000LDP_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4b1500LDP[ibin]=sig4b1500LDP_[nb]->GetBinContent( ij, mhti, 2 )+sig4b1500LDP_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4b1000LDP[ibin]=sig4b1000LDP_[nb]->GetBinContent( ij, mhti, 2 )+sig4b1000LDP_[nb]->GetBinContent( ij, mhti, 3 );

                        sig4t1500Pho[ibin]=sig4t1500Pho_[nb]->GetBinContent( ij, mhti, 2 )+sig4t1500Pho_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4t1200Pho[ibin]=sig4t1200Pho_[nb]->GetBinContent( ij, mhti, 2 )+sig4t1200Pho_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4q1400Pho[ibin]=sig4q1400Pho_[nb]->GetBinContent( ij, mhti, 2 )+sig4q1400Pho_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4q1000Pho[ibin]=sig4q1000Pho_[nb]->GetBinContent( ij, mhti, 2 )+sig4q1000Pho_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4b1500Pho[ibin]=sig4b1500Pho_[nb]->GetBinContent( ij, mhti, 2 )+sig4b1500Pho_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4b1000Pho[ibin]=sig4b1000Pho_[nb]->GetBinContent( ij, mhti, 2 )+sig4b1000Pho_[nb]->GetBinContent( ij, mhti, 3 );
                        
                        sig4t1500raw[ibin]=sig4t1500raw_[nb]->GetBinContent( ij, mhti, 2 )+sig4t1500raw_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4t1200raw[ibin]=sig4t1200raw_[nb]->GetBinContent( ij, mhti, 2 )+sig4t1200raw_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4q1400raw[ibin]=sig4q1400raw_[nb]->GetBinContent( ij, mhti, 2 )+sig4q1400raw_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4q1000raw[ibin]=sig4q1000raw_[nb]->GetBinContent( ij, mhti, 2 )+sig4q1000raw_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4b1500raw[ibin]=sig4b1500raw_[nb]->GetBinContent( ij, mhti, 2 )+sig4b1500raw_[nb]->GetBinContent( ij, mhti, 3 );
                        sig4b1000raw[ibin]=sig4b1000raw_[nb]->GetBinContent( ij, mhti, 2 )+sig4b1000raw_[nb]->GetBinContent( ij, mhti, 3 );
                        
                        
                        
                        qcd[ibin]=qcd_[nb]->GetBinContent( ij, mhti, 2 )+qcd_[nb]->GetBinContent( ij, mhti, 3 );
                        zi[ibin]=ZI_[nb]->GetBinContent( ij, mhti, 2 )+ZI_[nb]->GetBinContent( ij, mhti, 3 );
                        wj[ibin]=WJ_[nb]->GetBinContent( ij, mhti, 2 )+WJ_[nb]->GetBinContent( ij, mhti, 3 );
                        ttbar[ibin]=tt_[nb]->GetBinContent( ij, mhti, 2)+tt_[nb]->GetBinContent( ij, mhti, 3);
                        SL[ibin]= WJSL_[nb]->GetBinContent(ij, mhti, 2)+WJSL_[nb]->GetBinContent(ij, mhti, 3)+ttSL_[nb]->GetBinContent(ij, mhti, 2)+ttSL_[nb]->GetBinContent(ij, mhti, 3);
                        QCDSL[ibin]=QCDSL_[nb]->GetBinContent(ij, mhti, 2)+QCDSL_[nb]->GetBinContent(ij, mhti, 3);
                        ZSL[ibin]=zSL_[nb]->GetBinContent(ij, mhti, 2)+zSL_[nb]->GetBinContent(ij, mhti, 3);

                        
                        LDP[ibin]= qcdLDP_[nb]->GetBinContent(ij, mhti, 2)+qcdLDP_[nb]->GetBinContent(ij, mhti, 3);
                        ZLDP[ibin]=ZLDP_[nb]->GetBinContent(ij, mhti, 2)+ZLDP_[nb]->GetBinContent(ij, mhti, 3);
                        SLLDP[ibin]=WJLDP_[nb]->GetBinContent(ij, mhti, 2)+WJLDP_[nb]->GetBinContent(ij, mhti, 3)+ttLDP_[nb]->GetBinContent(ij, mhti, 2)+ttLDP_[nb]->GetBinContent(ij, mhti, 3);
                        
                        GJet[ibin] = ziGJet_[nb]->GetBinContent(ij, mhti, 2)+ziGJet_[nb]->GetBinContent(ij, mhti, 3);
                        
                        QCDPho[ibin]= qcdPho_[nb]->GetBinContent(ij, mhti, 2)+qcdPho_[nb]->GetBinContent(ij, mhti, 3);
                        SLPho[ibin]=WJPho_[nb]->GetBinContent(ij, mhti, 2)+WJPho_[nb]->GetBinContent(ij, mhti, 3)+ttPho_[nb]->GetBinContent(ij, mhti, 2)+ttPho_[nb]->GetBinContent(ij, mhti, 3);
                        
                        ++ibin;
                    }
                    
                    if(mhti==2){
                        if(hti==2)continue;
                        boxcount=4;
                        // if(ij==1&& nb==0)++boxcount;
                        sig4t1500[ibin]=sig4t1500_[nb]->GetBinContent( ij, mhti, 1 )+sig4t1500_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4t1200[ibin]=sig4t1200_[nb]->GetBinContent( ij, mhti, 1 )+sig4t1200_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4q1400[ibin]=sig4q1400_[nb]->GetBinContent( ij, mhti, 1 )+sig4q1400_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4q1000[ibin]=sig4q1000_[nb]->GetBinContent( ij, mhti, 1 )+sig4q1000_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4b1500[ibin]=sig4b1500_[nb]->GetBinContent( ij, mhti, 1 )+sig4b1500_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4b1000[ibin]=sig4b1000_[nb]->GetBinContent( ij, mhti, 1 )+sig4b1000_[nb]->GetBinContent( ij, mhti, 2 );
                        
                        sig4t1500SL[ibin]=sig4t1500SL_[nb]->GetBinContent( ij, mhti, 1 )+sig4t1500SL_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4t1200SL[ibin]=sig4t1200SL_[nb]->GetBinContent( ij, mhti, 1 )+sig4t1200SL_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4q1400SL[ibin]=sig4q1400SL_[nb]->GetBinContent( ij, mhti, 1 )+sig4q1400SL_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4q1000SL[ibin]=sig4q1000SL_[nb]->GetBinContent( ij, mhti, 1 )+sig4q1000SL_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4b1500SL[ibin]=sig4b1500SL_[nb]->GetBinContent( ij, mhti, 1 )+sig4b1500SL_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4b1000SL[ibin]=sig4b1000SL_[nb]->GetBinContent( ij, mhti, 1 )+sig4b1000SL_[nb]->GetBinContent( ij, mhti, 2 );
                        
                        sig4t1500LDP[ibin]=sig4t1500LDP_[nb]->GetBinContent( ij, mhti, 1 )+sig4t1500LDP_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4t1200LDP[ibin]=sig4t1200LDP_[nb]->GetBinContent( ij, mhti, 1 )+sig4t1200LDP_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4q1400LDP[ibin]=sig4q1400LDP_[nb]->GetBinContent( ij, mhti, 1 )+sig4q1400LDP_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4q1000LDP[ibin]=sig4q1000LDP_[nb]->GetBinContent( ij, mhti, 1 )+sig4q1000LDP_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4b1500LDP[ibin]=sig4b1500LDP_[nb]->GetBinContent( ij, mhti, 1 )+sig4b1500LDP_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4b1000LDP[ibin]=sig4b1000LDP_[nb]->GetBinContent( ij, mhti, 1 )+sig4b1000LDP_[nb]->GetBinContent( ij, mhti, 2 );

                        sig4t1500Pho[ibin]=sig4t1500Pho_[nb]->GetBinContent( ij, mhti, 1 )+sig4t1500Pho_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4t1200Pho[ibin]=sig4t1200Pho_[nb]->GetBinContent( ij, mhti, 1 )+sig4t1200Pho_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4q1400Pho[ibin]=sig4q1400Pho_[nb]->GetBinContent( ij, mhti, 1 )+sig4q1400Pho_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4q1000Pho[ibin]=sig4q1000Pho_[nb]->GetBinContent( ij, mhti, 1 )+sig4q1000Pho_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4b1500Pho[ibin]=sig4b1500Pho_[nb]->GetBinContent( ij, mhti, 1 )+sig4b1500Pho_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4b1000Pho[ibin]=sig4b1000Pho_[nb]->GetBinContent( ij, mhti, 1 )+sig4b1000Pho_[nb]->GetBinContent( ij, mhti, 2 );
                        
                        sig4t1500raw[ibin]=sig4t1500raw_[nb]->GetBinContent( ij, mhti, 1 )+sig4t1500raw_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4t1200raw[ibin]=sig4t1200raw_[nb]->GetBinContent( ij, mhti, 1 )+sig4t1200raw_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4q1400raw[ibin]=sig4q1400raw_[nb]->GetBinContent( ij, mhti, 1 )+sig4q1400raw_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4q1000raw[ibin]=sig4q1000raw_[nb]->GetBinContent( ij, mhti, 1 )+sig4q1000raw_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4b1500raw[ibin]=sig4b1500raw_[nb]->GetBinContent( ij, mhti, 1 )+sig4b1500raw_[nb]->GetBinContent( ij, mhti, 2 );
                        sig4b1000raw[ibin]=sig4b1000raw_[nb]->GetBinContent( ij, mhti, 1 )+sig4b1000raw_[nb]->GetBinContent( ij, mhti, 2 );
                        
                        qcd[ibin]=qcd_[nb]->GetBinContent( ij, mhti, 1 )+qcd_[nb]->GetBinContent( ij, mhti, 2 );
                        zi[ibin]=ZI_[nb]->GetBinContent( ij, mhti, 1 )+ZI_[nb]->GetBinContent( ij, mhti, 2 );
                        wj[ibin]=WJ_[nb]->GetBinContent( ij, mhti, 1 )+WJ_[nb]->GetBinContent( ij, mhti, 2 );
                        ttbar[ibin]=tt_[nb]->GetBinContent( ij, mhti, 1)+tt_[nb]->GetBinContent( ij, mhti, 2);
                        SL[ibin]= WJSL_[nb]->GetBinContent(ij, mhti, 1)+WJSL_[nb]->GetBinContent(ij, mhti, 2)+ttSL_[nb]->GetBinContent(ij, mhti, 1)+ttSL_[nb]->GetBinContent(ij, mhti, 2);
                        QCDSL[ibin]=QCDSL_[nb]->GetBinContent(ij, mhti, 1)+QCDSL_[nb]->GetBinContent(ij, mhti, 1);
                        ZSL[ibin]=zSL_[nb]->GetBinContent(ij, mhti, 1)+zSL_[nb]->GetBinContent(ij, mhti, 2);

                        
                        LDP[ibin]= qcdLDP_[nb]->GetBinContent(ij, mhti, 1)+qcdLDP_[nb]->GetBinContent(ij, mhti, 2);
                        
                        SLLDP[ibin]=WJLDP_[nb]->GetBinContent(ij, mhti, 1)+WJLDP_[nb]->GetBinContent(ij, mhti, 2)+ttLDP_[nb]->GetBinContent(ij, mhti, 1)+ttLDP_[nb]->GetBinContent(ij, mhti, 2);
                        ZLDP[ibin]=ZLDP_[nb]->GetBinContent(ij, mhti, 1)+ZLDP_[nb]->GetBinContent(ij, mhti, 2);

                        GJet[ibin]= ziGJet_[nb]->GetBinContent(ij, mhti, 1)+ziGJet_[nb]->GetBinContent(ij, mhti, 2);
                                  QCDPho[ibin]= qcdPho_[nb]->GetBinContent(ij, mhti, 1)+qcdPho_[nb]->GetBinContent(ij, mhti, 2);
                        SLPho[ibin]=WJPho_[nb]->GetBinContent(ij, mhti, 1)+WJPho_[nb]->GetBinContent(ij, mhti, 2)+ttPho_[nb]->GetBinContent(ij, mhti, 1)+ttPho_[nb]->GetBinContent(ij, mhti, 2);
                        if(hti==3){
                            boxcount=5;
                            sig4t1500[ibin]=sig4t1500_[nb]->GetBinContent( ij, mhti, hti );
                            sig4t1200[ibin]=sig4t1200_[nb]->GetBinContent( ij, mhti, hti );
                            sig4q1400[ibin]=sig4q1400_[nb]->GetBinContent( ij, mhti, hti );
                            sig4q1000[ibin]=sig4q1000_[nb]->GetBinContent( ij, mhti, hti );
                            sig4b1500[ibin]=sig4b1500_[nb]->GetBinContent( ij, mhti, hti );
                            sig4b1000[ibin]=sig4b1000_[nb]->GetBinContent( ij, mhti, hti );
                            
                            sig4t1500SL[ibin]=sig4t1500SL_[nb]->GetBinContent( ij, mhti, hti );
                            sig4t1200SL[ibin]=sig4t1200SL_[nb]->GetBinContent( ij, mhti, hti );
                            sig4q1400SL[ibin]=sig4q1400SL_[nb]->GetBinContent( ij, mhti, hti );
                            sig4q1000SL[ibin]=sig4q1000SL_[nb]->GetBinContent( ij, mhti, hti );
                            sig4b1500SL[ibin]=sig4b1500SL_[nb]->GetBinContent( ij, mhti, hti );
                            sig4b1000SL[ibin]=sig4b1000SL_[nb]->GetBinContent( ij, mhti, hti );
                            
                            sig4t1500LDP[ibin]=sig4t1500LDP_[nb]->GetBinContent( ij, mhti, hti );
                            sig4t1200LDP[ibin]=sig4t1200LDP_[nb]->GetBinContent( ij, mhti, hti );
                            sig4q1400LDP[ibin]=sig4q1400LDP_[nb]->GetBinContent( ij, mhti, hti );
                            sig4q1000LDP[ibin]=sig4q1000LDP_[nb]->GetBinContent( ij, mhti, hti );
                            sig4b1500LDP[ibin]=sig4b1500LDP_[nb]->GetBinContent( ij, mhti, hti );
                            sig4b1000LDP[ibin]=sig4b1000LDP_[nb]->GetBinContent( ij, mhti, hti );
                            
                            sig4t1500Pho[ibin]=sig4t1500Pho_[nb]->GetBinContent( ij, mhti, hti );
                            sig4t1200Pho[ibin]=sig4t1200Pho_[nb]->GetBinContent( ij, mhti, hti );
                            sig4q1400Pho[ibin]=sig4q1400Pho_[nb]->GetBinContent( ij, mhti, hti );
                            sig4q1000Pho[ibin]=sig4q1000Pho_[nb]->GetBinContent( ij, mhti, hti );
                            sig4b1500Pho[ibin]=sig4b1500Pho_[nb]->GetBinContent( ij, mhti, hti );
                            sig4b1000Pho[ibin]=sig4b1000Pho_[nb]->GetBinContent( ij, mhti, hti );
                            
                            sig4t1500raw[ibin]=sig4t1500raw_[nb]->GetBinContent( ij, mhti, hti );
                            sig4t1200raw[ibin]=sig4t1200raw_[nb]->GetBinContent( ij, mhti, hti );
                            sig4q1400raw[ibin]=sig4q1400raw_[nb]->GetBinContent( ij, mhti, hti );
                            sig4q1000raw[ibin]=sig4q1000raw_[nb]->GetBinContent( ij, mhti, hti );
                            sig4b1500raw[ibin]=sig4b1500raw_[nb]->GetBinContent( ij, mhti, hti );
                            sig4b1000raw[ibin]=sig4b1000raw_[nb]->GetBinContent( ij, mhti, hti );
                            
                            qcd[ibin]=qcd_[nb]->GetBinContent( ij, mhti, hti );
                            zi[ibin]=ZI_[nb]->GetBinContent( ij, mhti, hti );
                            wj[ibin]=WJ_[nb]->GetBinContent( ij, mhti, hti );
                            ttbar[ibin]=tt_[nb]->GetBinContent( ij, mhti, hti );
                            SL[ibin]= WJSL_[nb]->GetBinContent(ij, mhti, hti)+ttSL_[nb]->GetBinContent(ij, mhti, hti);
                            QCDSL[ibin]=QCDSL_[nb]->GetBinContent(ij, mhti, hti);
                            ZSL[ibin]=zSL_[nb]->GetBinContent(ij, mhti, hti);

                            
                            
                            LDP[ibin]= qcdLDP_[nb]->GetBinContent(ij, mhti, hti);
                            SLLDP[ibin]=WJLDP_[nb]->GetBinContent(ij, mhti, hti)+ttLDP_[nb]->GetBinContent(ij, mhti, hti);
                            ZLDP[ibin]=ZLDP_[nb]->GetBinContent(ij, mhti, hti);

                            
                            
                            GJet[ibin]= ziGJet_[nb]->GetBinContent(ij, mhti, hti);
                            QCDPho[ibin]= qcdPho_[nb]->GetBinContent(ij, mhti, hti);
                            SLPho[ibin]=WJPho_[nb]->GetBinContent(ij, mhti, hti)+ttPho_[nb]->GetBinContent(ij, mhti, hti);

                        }
                        //std::cout<<"Ibin "<<ibin<<"nj "<<ij<<" nb "<<nb<<" hti "<< hti<<" mhti "<<mhti<<std::endl;

                        ++ibin;
                    }
                    
                    if(nb>=2)fprintf(fp, "HT-MHTBin%d jetbin%d btag%d & %4.2f & %4.2f & %4.2f & %4.2f & %4.2f & %4.2f & %4.2f & %4.2f  & %4.2f & %4.2f  \\\\ \n", boxcount,ij, nb,qcd[ibin-1], ttbar[ibin-1],zi[ibin-1],wj[ibin-1],sig4t1500[ibin-1],sig4t1200[ibin-1],sig4q1400[ibin-1],sig4q1000[ibin-1],sig4b1500[ibin-1],sig4b1000[ibin-1] );
                    Bbins[ibin-1]=nb;
                    njbins[ibin-1]=ij;
                    mbins[ibin-1]=boxcount;

                }
            }
        }
    }
    fprintf(fp,"\\hline\n");
    fprintf(fp,"\\end{tabular}}\n");
    fprintf(fp,"\\caption{TEST}\n");
    fprintf(fp,"\\end{table}\n");
    fprintf(fp,"\\end{document}\n"); //made Latex File with Yields
    fclose(fp);

    f0->Close();
    f1->Close();
    f2->Close();
    f3->Close();

}

//THis prints the data cards with specified Uncertainties (entered by hand for now)
void MakeCombineDataCards(int mGlu, int MLSP, float mu=1.0, float lumi=4, TString Options="", int bin=0){
    
    float sig[totalbins];
    float sigRaw[totalbins];
    float obs[totalbins];
    fillEventYields(lumi);
    
    for(int i=0; i<totalbins; ++i){
        if(Options=="T1tttt" && mGlu==1500){
            sig[i]=sig4t1500[i]; sigRaw[i]=sig4t1500raw[i];sigSL[i]=sig4t1500SL[i];sigLDP[i]=sig4t1500LDP[i];sigPho[i]=sig4t1500Pho[i];
        }
        if(Options=="T1tttt" && mGlu==1200){
            sig[i]=sig4t1200[i];sigRaw[i]=sig4t1200raw[i];sigSL[i]=sig4t1200SL[i];sigLDP[i]=sig4t1200LDP[i];
            sigPho[i]=sig4t1200Pho[i];
        }
        if(Options=="T1qqqq" && mGlu==1400){
            sig[i]=sig4q1400[i];sigRaw[i]=sig4q1400raw[i];sigSL[i]=sig4q1400SL[i];sigLDP[i]=sig4q1400LDP[i];
            sigPho[i]=sig4q1400Pho[i];
        }
        if(Options=="T1qqqq"  && mGlu==1000){
            sig[i]=sig4q1000[i];sigRaw[i]=sig4q1000raw[i];sigSL[i]=sig4q1000SL[i];sigLDP[i]=sig4q1000LDP[i];
            sigPho[i]=sig4q1000Pho[i];
        }
        if(Options=="T1bbbb" && mGlu==1500){
            sig[i]=sig4b1500[i];sigRaw[i]=sig4b1500raw[i];sigSL[i]=sig4b1500SL[i];sigLDP[i]=sig4b1500LDP[i];
            sigPho[i]=sig4b1500Pho[i];

        }
        if(Options=="T1bbbb" && mGlu==1000){
            sig[i]=sig4b1000[i];sigRaw[i]=sig4b1000raw[i];sigSL[i]=sig4b1000SL[i];sigLDP[i]=sig4b1000LDP[i];
            sigPho[i]=sig4b1000Pho[i];

        }
        
        obs[i]=(qcd[i]+ zi[i]+wj[i]+ttbar[i] + (mu*sig[i]));
    }

    //std::cout << "bin = " << bin << " " << qcd[bin] << " " << zi[bin] << " " << wj[bin] << " " << ttbar[bin] << " " << sig[bin] << " " << LDP[bin] << " " << SL[bin] << " " << GJet[bin] << std::endl;

    float qcdscale=10.0;
    float ttbarScale=1.0;
    float gjetScale=1.0; //???
    
    // --------------------------------

    // some code for the gamma + jets estimation
    
 /*
    int ibin=0;
    int nbForCurrentBin = -99;
    for ( int ij=1; ij<=3; ij++ ) {
        for(int nb=0; nb<=3; nb++){
            for ( int mhti=1; mhti<=3; mhti++ ){
                for ( int hti=1; hti<=3; hti++ ) {
                    if (bin == ibin) nbForCurrentBin = nb;
                    ibin++;
                    // std::cout << ibin << " " << ij << " " << nb << " " << mhti << " " << hti << std::endl;
                }
            }
        }
    }

    // std::cout << "nbForCurrentBin = " << nbForCurrentBin << std::endl;
*/
    
    TString str=(TString::Format("./DataCards/SensStudyLumi%2.2f_Bin%d_M%d_m%d_%s.dat",lumi,bin, mGlu, MLSP,Options.Data())).Data();
    // const char outputfilename[100]=str.Data();

    FILE* fp = fopen(  str.Data(), "w" ) ;
    
    int numberOfChannels = 3;
    if (Bbins[bin] == 0) numberOfChannels = 4;
    fprintf(fp, "imax %d number of channels\n", numberOfChannels);//signal region PLUS 3 control bins
    fprintf(fp, "jmax %d number of backgrounds (QCD, Zinv, WJttbar)\n",3);//4 bkg processes
    fprintf(fp, "kmax * nuissance\n");
    fprintf(fp, "------------\n");
    if (Bbins[bin] == 0) fprintf(fp, "bin Bin%d BinContLDP%d BinContSL%d BinContPh%d ", bin,bin,bin,bin);
    if (Bbins[bin] > 0) fprintf(fp, "bin Bin%d BinContLDP%d BinContSL%d ", bin,bin,bin);
    //4 bins
    if (Bbins[bin] == 0) fprintf(fp, "\nobservation %g %g %g %g", obs[bin],LDP[bin]+ZLDP[bin]+SLLDP[bin]+sigLDP[bin],SL[bin]+QCDSL[bin]+ZSL[bin]+sigSL[bin],GJet[bin]+QCDPho[bin]+SLPho[bin]+sigPho[bin]);
    if (Bbins[bin] > 0) fprintf(fp, "\nobservation %g %g %g", obs[bin],LDP[bin]+ZLDP[bin]+SLLDP[bin]+sigLDP[bin],SL[bin]+QCDSL[bin]+ZSL[bin]+sigSL[bin]);
   //4 Expected Count bins (MC)
    fprintf(fp, "\nbin Bin%d  Bin%d  Bin%d  Bin%d ", bin,bin, bin, bin);
    fprintf(fp, "BinContLDP%d  BinContLDP%d  BinContLDP%d  BinContLDP%d ",bin, bin,bin, bin);
    fprintf(fp, "BinContSL%d  BinContSL%d  BinContSL%d  BinContSL%d ", bin,bin, bin, bin);
    if (Bbins[bin] == 0) fprintf(fp, "BinContPh%d  BinContPh%d  BinContPh%d  BinContPh%d ", bin,bin, bin, bin);
    //fprintf(fp, "BinContT%d  BinContT%d  BinContT%d  BinContT%d  BinContT%d ",bin, bin,bin, bin, bin);
    
    fprintf(fp, "\nprocess sig QCD Zinv WJttbar ");
    fprintf(fp, "sig QCD Zinv WJttbar  ");
    fprintf(fp, "sig QCD Zinv WJttbar  ");
    if (Bbins[bin] == 0) fprintf(fp, "sig QCD Zinv WJttbar  ");
    
    fprintf(fp, "\nprocess %d %d %d %d ", 0, 1,2,3);
    fprintf(fp, "%d %d %d %d ",0, 1,2,3);
    fprintf(fp, "%d %d %d %d ",0, 1,2,3);
    if (Bbins[bin] == 0) fprintf(fp, "%d %d %d %d ",0, 1,2,3);
    
    //NOW THIS IS MY EXPECTED SIGNAL REGION!
    if(sig[bin]>0.0000000000000000001) fprintf(fp, "\nrate %g ", sig[bin]);
    else fprintf(fp, "\nrate %g ", 0.000001);
    
    if(qcd[bin]>0.0000000000000000001) fprintf(fp, " %g ", qcd[bin]);
    else fprintf(fp, " %g ",0.0000001);
    
    fprintf(fp, " %g ", zi[bin]);
    if(wj[bin]+ttbar[bin]>0.0000000000000000001)fprintf(fp, " %g ",wj[bin]+ttbar[bin]);
    else fprintf(fp, " %g ",0.0000001);
    
    //QCD Region 1
    fprintf(fp, " %g ",sigLDP[bin]);
    if(LDP[bin]>0.0000000000000000001)fprintf(fp, " %g ",LDP[bin]);
    else fprintf(fp, " %g ",qcdscale*0.001);
    //fprintf(fp, " %g ",10.);
    fprintf(fp, " %g %g ",ZLDP[bin], SLLDP[bin]);
    
    //WJ/TTbar Region 1
    fprintf(fp, " %g %g %g",sigSL[bin],QCDSL[bin],ZSL[bin]);
    if(SL[bin]>0.0000000000000000001)fprintf(fp, " %g ",SL[bin]);
    else fprintf(fp, " %g ", ttbarScale*0.001);
    if (Bbins[bin] > 0) fprintf(fp, "\n");

    
    //Gamma+jets Region 1
    if (Bbins[bin] == 0){
        fprintf(fp, " %g %g",sigPho[bin],QCDPho[bin]);
        if(GJet[bin]>0.0000000000000000001)fprintf(fp, " %g ",GJet[bin]);
        else fprintf(fp, " %g ", gjetScale*0.001);
        fprintf(fp, "%g \n", SLPho[bin]);
    }

    ////////////////////////
    //// now systematics
    ////////////////////////
    fprintf(fp, "------------\n");

    ///--------------------------------------
    /// QCD
    float logUErr=100.;
    if(LDP[bin]>0.0000000000000000001){
        fprintf(fp, "rateBqcd%d lnU - %8.1f - - ",bin, logUErr );
        fprintf(fp, " - %8.1f - - ",logUErr);
        if (Bbins[bin] == 0) fprintf(fp, " - %8.1f - -  ", logUErr);
        fprintf(fp, " - %8.1f - -\n",logUErr);
    }
    else {
       logUErr=10000;
       fprintf(fp, "rateBqcd%d lnU - %8.1f - - ",bin, logUErr );
       fprintf(fp, " - %8.1f - - ",logUErr);
        if (Bbins[bin] == 0) fprintf(fp, " - %8.1f - -  ", logUErr);
        fprintf(fp, " - %8.1f - -\n",logUErr);
    }

   fprintf(fp, "LogBqcd%d lnN - %g - -  ",bin, 1.3 );
   fprintf(fp, " - - - -  ");
   if (Bbins[bin] == 0) fprintf(fp, " - - - -  ");
   fprintf(fp, " - - - -  \n");

    ///--------------------------------------
    /// SL
    if(SL[bin]>0.0000000000000000001){
        logUErr=100;
        fprintf(fp, "rateBW%d lnU - - - %8.1f  ",bin, logUErr );
        fprintf(fp, " - - - %8.1f  ",logUErr);
        fprintf(fp, " - - - %8.1f  ",logUErr);
        if (Bbins[bin] == 0) fprintf(fp, " - - - %8.1f  \n", logUErr);
        if (Bbins[bin] > 0) fprintf(fp, "\n");
    }
    else{
        logUErr=10000;
        fprintf(fp, "rateBW%d lnU - - - %8.1f  ",bin, logUErr );
        fprintf(fp, " - - - %8.1f  ", logUErr);
        fprintf(fp, " - - - %8.1f  ",logUErr);  
        if (Bbins[bin] == 0) fprintf(fp, " - - - %8.1f  \n", logUErr);
        if (Bbins[bin] > 0) fprintf(fp, "\n");
    }

    //background systematics
    //lepton efficiency in MHT/HT plane

    float LepEff=1.0;
    
    if(mbins[bin]==1)LepEff=1.05;
    if(mbins[bin]==2)LepEff=1.07;
    if(mbins[bin]==3)LepEff=1.10;
    if(mbins[bin]==4)LepEff=1.07;
    if(mbins[bin]==5)LepEff=1.1;
    if(mbins[bin]==6)LepEff=1.1;
    
    fprintf(fp, "LepEff lnN - - - %g ", LepEff );
    fprintf(fp, " - - - - ");
    fprintf(fp, " - - - - ");
    if (Bbins[bin] == 0) fprintf(fp, " - - - -  \n");
    if (Bbins[bin] > 0) fprintf(fp, "\n");

    float MCClose=1.0;
    if(njbins[bin]==1)MCClose=1.1;
    if(njbins[bin]==2)MCClose=1.2;
    if(njbins[bin]==3)MCClose=1.3;

    fprintf(fp, "MCClose_%d lnN - - - %g ", bin,MCClose) ;
    fprintf(fp, " - - - - ");
    fprintf(fp, " - - - - ");
    if (Bbins[bin] == 0) fprintf(fp, " - - - -  \n");
    if (Bbins[bin] > 0) fprintf(fp, "\n");

    ///--------------------------------------    
    /// Zinv

    if (Bbins[bin] == 0){
        logUErr=100;
        fprintf(fp, "rateBPh%d lnU - - %8.1f -  ",bin, logUErr );
        fprintf(fp, " - - - -  ");
        fprintf(fp, " - - - -  ");
        fprintf(fp, " - - %8.1f - \n",logUErr);
        fprintf(fp, "rateB0BTo1B lnU - - %8.1f -  ", logUErr );
        fprintf(fp, " - - - -  ");
        fprintf(fp, " - - - -  ");
        fprintf(fp, " - - - -  \n");
        fprintf(fp, "rateB0BTo2B lnU - - %8.1f -  ", logUErr );
        fprintf(fp, " - - - -  ");
        fprintf(fp, " - - - -  ");
        fprintf(fp, " - - - -  \n");
        fprintf(fp, "rateB0BTo3B lnU - - %8.1f -  ", logUErr );
        fprintf(fp, " - - - -  ");
        fprintf(fp, " - - - -  ");
        fprintf(fp, " - - - -  \n");
        fprintf(fp, "LogBPh lnN - - %g -  ", 1.3 );
        fprintf(fp, " - - - -  ");
        fprintf(fp, " - - - -  ");
        fprintf(fp, " - - - -  \n");
    }
    else{
        fprintf(fp, "rateB0BTo%1iB lnU - - %8.1f -  ",Bbins[bin], logUErr );
        fprintf(fp, " - - - -  ");
        fprintf(fp, " - - - -  \n");
        fprintf(fp, "LogB0BTo%iB lnN - - %g -  ",Bbins[bin], 1.3 );
        fprintf(fp, " - - - -  ");
        fprintf(fp, " - - - -  \n");
        fprintf(fp, "LogBPh lnN - - %g -  ", 1.3 );
        fprintf(fp, " - - - -  ");
        fprintf(fp, " - - - -  \n");        
    }
    ///--------------------------------------    


   /* 
    fprintf(fp, "LogBZ%d lnN - - %g - ",bin, 1.3 );
    fprintf(fp, " - - - - ");
    fprintf(fp, " - - - - ");
    fprintf(fp, " - - - - ");
    if (Bbins[bin] == 0) fprintf(fp, " - - - -  \n");
    if (Bbins[bin] > 0) fprintf(fp, "\n");
    */
    //apply b-tag uncertainty
    
    float btagerrUP=1.0;
    if(Bbins[bin]==0)btagerrUP=0.9;
    if(Bbins[bin]==3)btagerrUP=1.1;
    fprintf(fp, "BTagEffSigmaUp lnN %g - - - ", btagerrUP );
    fprintf(fp, " - - - - ");
    fprintf(fp, " - - - - ");
    if (Bbins[bin] == 0) fprintf(fp, " - - - -  \n");
    if (Bbins[bin] > 0) fprintf(fp, "\n");

    float btagerrDown=1.0;
    if(Bbins[bin]==0)btagerrDown=1.1;
    if(Bbins[bin]==3)btagerrDown=0.9;
    
    fprintf(fp, "BTagEffSigmaDown lnN %g - - - ",btagerrDown );
    fprintf(fp, " - - - - ");
    fprintf(fp, " - - - - ");
    if (Bbins[bin] == 0) fprintf(fp, " - - - -  \n");
    if (Bbins[bin] > 0) fprintf(fp, "\n");
    
    fprintf(fp, "lumi lnN %g - - - ", 1.044 );
    fprintf(fp, " - - - - ");
    fprintf(fp, " - - - - ");
    if (Bbins[bin] == 0) fprintf(fp, " - - - -  \n");
    if (Bbins[bin] > 0) fprintf(fp, "\n");
    
    fprintf(fp, "PDFUnc lnN %g - - - ", 1.1 );
    fprintf(fp, " - - - - ");
    fprintf(fp, " - - - - ");
    if (Bbins[bin] == 0) fprintf(fp, " - - - -  \n");
    if (Bbins[bin] > 0) fprintf(fp, "\n");
    
    float JEC_UnclECorr=1.0;
    
    if(mbins[bin]==1)JEC_UnclECorr=0.95-0.01-0.02;
    if(mbins[bin]==2)JEC_UnclECorr=0.97-0.01-0.02;
    if(mbins[bin]==3)JEC_UnclECorr=1.1+0.01+0.02;
    if(mbins[bin]==4)JEC_UnclECorr=0.96-0.01-0.02;
    if(mbins[bin]==5)JEC_UnclECorr=1.04+0.01+0.02;
    if(mbins[bin]==6)JEC_UnclECorr=1.05+0.01+0.02;
    
    fprintf(fp, "JEC lnN %g - - - ", JEC_UnclECorr );
    fprintf(fp, " - - - - ");
    fprintf(fp, " - - - - ");
    if (Bbins[bin] == 0) fprintf(fp, " - - - -  \n");
    if (Bbins[bin] > 0) fprintf(fp, "\n");    
    
    if (sigRaw[bin] > 0.0001) fprintf(fp, "MCstat_%d lnN %g - - - ", bin,1+(sqrt(sigRaw[bin]))/sigRaw[bin]) ;
    else fprintf(fp, "MCstat_%d lnN %g - - - ", bin,100.) ;
    fprintf(fp, " - - - - ");
    fprintf(fp, " - - - - ");
    if (Bbins[bin] == 0) fprintf(fp, " - - - -  \n");
    if (Bbins[bin] > 0) fprintf(fp, "\n");
    
}
                                                                                                                                                                                                                                                                                                      