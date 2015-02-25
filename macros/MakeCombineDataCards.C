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
const int totalbins=72; //hard coded to default 72 analysis bins

float sig4t1500[totalbins];
float sig4t1200[totalbins];
float sig4q1400[totalbins];
float sig4q1000[totalbins];
float sig4b1500[totalbins];
float sig4b1000[totalbins];


float qcd[totalbins];
float zi[totalbins];
float wj[totalbins];
float ttbar[totalbins];

void MakeInputHisto(TString Options="Signal", float lumi=4){  //all input files
    const int nBinsjets = 3 ;
    const int nBinsBjets = 4 ;
    const int nBinsMHT = 3 ;
    const int nBinsHT = 3 ;
    //float METBinRectangular[4]={200, 500., 750.,9999.};
    
    float MHTBinRectangular[4]={200, 500., 750.,9999.};
    float HTBinRectangular[4]={500., 800., 1200.,9999.};//can do 150 to
    
    char bcutstringRectangular[nBinsBjets][100] = { "BTags30==0", "BTags30==1","BTags30==2", "BTags30>=3" } ;
    float NJets[4]={4, 7,9,99};
    //these are in an eos area on lxplus:/eos/cms/store/user/rpatel/RA2b
    TChain t1tt1500("TreeMaker2/ReducedTree");
    t1tt1500.Add(TString::Format("./InputFiles/ReducedTree_SMSttttM1500.root"));
    TChain t1tt1200("TreeMaker2/ReducedTree");
    t1tt1200.Add(TString::Format("./InputFiles/ReducedTree_SMSttttM1200.root"));
    TChain t1bb1000("TreeMaker2/ReducedTree");
    t1bb1000.Add(TString::Format("./InputFiles/ReducedTree_SMSbbbbM1000.root"));
    TChain t1bb1500("TreeMaker2/ReducedTree");
    t1bb1500.Add(TString::Format("./InputFiles/ReducedTree_SMSbbbbM1500.root"));
    TChain t1qq1000("TreeMaker2/ReducedTree");
    t1qq1000.Add(TString::Format("./InputFiles/ReducedTree_SMSqqqqM1000.root"));
    TChain t1qq1400("TreeMaker2/ReducedTree");
    t1qq1400.Add(TString::Format("./InputFiles/ReducedTree_SMSqqqqM1400.root"));
    
    TChain QCDCH("TreeMaker2/ReducedTree") ;
    QCDCH.Add("./InputFiles/ReducedTree_QCDHT500.root");
    QCDCH.Add("./InputFiles/ReducedTree_QCDHT250.root");
    QCDCH.Add("./InputFiles/ReducedTree_QCDHT1000.root");

    TChain WJets("TreeMaker2/ReducedTree");
    WJets.Add("./InputFiles/ReducedTree_WJ100.root");
    WJets.Add("./InputFiles/ReducedTree_WJ200.root");
    WJets.Add("./InputFiles/ReducedTree_WJ400.root");
    WJets.Add("./InputFiles/ReducedTree_WJ600Merged.root");

    TChain tt("TreeMaker2/ReducedTree");
    tt.Add("./InputFiles/ReducedTree_TBarToLeptons_t.root");
    tt.Add("./InputFiles/ReducedTree_TToLeptons_t.root");
    tt.Add("./InputFiles/ReducedTree_TTJetsMSDecaysCKM.root");
    tt.Add("./InputFiles/ReducedTree_T_tW.root");
    tt.Add("./InputFiles/ReducedTree_Tbar_tW.root");
    
    TChain Zinv("TreeMaker2/ReducedTree") ;
    Zinv.Add("./InputFiles/ReducedTree_ZInv100.root");
    Zinv.Add("./InputFiles/ReducedTree_ZInv200.root");
    Zinv.Add("./InputFiles/ReducedTree_ZInv400.root");
    Zinv.Add("./InputFiles/ReducedTree_ZInv600.root");
    
    
    
    char commoncuts[10000] ;
    TString fileBaseName;
    if(Options=="Signal"){
        sprintf( commoncuts,"HT30>500 && NJets30>=4 && MHT>200 && (Muons==0 && Electrons==0) && abs(minDeltaPhiN)>4.0 && isoTracks==0" ); //signal region selection
        fileBaseName=TString::Format("Bins4DBINS_Lumi%2.2ffb.root",lumi);
    }
    if(Options=="LDP"){
        sprintf( commoncuts,"HT30>500 && NJets30>=4 && MHT>200 && (Muons==0 && Electrons==0) && abs(minDeltaPhiN)<4.0 && isoTracks==0" ); //LowDelPhi region selection
        fileBaseName=TString::Format("Bins4DLDP_Lumi%2.2ffb.root",lumi);

    }
    if(Options=="SL"){
        sprintf( commoncuts,"HT30>500 && NJets30>=4 && MHT>200 && (Muons+Electrons==1) && abs(minDeltaPhiN)>4.0 && isoTracks==0" );//Single Lepton region selection
        fileBaseName=TString::Format("Bins4DSL_Lumi%2.2ffb.root",lumi);

    }
    char weightstring[10000];
    sprintf(weightstring, "*(weight*%2.2f)", lumi*1000); //bkg xsec weight
    
    char arg1[1000] ;
    char cuts[10000];
    //yields stored in a TH3* (one for each btag) so 4D
    TH3F*sig4t1200_[4];
    TH3F*sig4t1500_[4];
    
    TH3F*sig4b1500_[4];
    TH3F*sig4b1000_[4];
    TH3F*sig4q1400_[4];
    TH3F*sig4q1000_[4];
    
    TH3F*qcd_[4];
    TH3F*tt_[4];
    TH3F*WJ_[4];
    TH3F*ZI_[4];
    
    //REALLY NEED TO ONLY DO THIS ONCE for the same binning and a particular luminosity scale
    TFile*f0=new TFile(TString::Format("%s", fileBaseName.Data()).Data(), "RECREATE");
    for(int b=0; b<nBinsBjets; ++b){
        
        sig4t1500_[b]=new TH3F(TString::Format("sig4t1500__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        sig4t1200_[b]=new TH3F(TString::Format("sig4t1200__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        
        
        sig4b1500_[b]=new TH3F(TString::Format("sig4b1500__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        sig4b1000_[b]=new TH3F(TString::Format("sig4b1000__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        
        sig4q1000_[b]=new TH3F(TString::Format("sig4q1000__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        sig4q1400_[b]=new TH3F(TString::Format("sig4q1400__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        
        qcd_[b]=new TH3F(TString::Format("qcd__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular, nBinsHT,HTBinRectangular );
        tt_[b]=new TH3F(TString::Format("tt__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        WJ_[b]=new TH3F(TString::Format("WJ__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        ZI_[b]=new TH3F(TString::Format("ZI__b%d", b).Data(), "", nBinsjets, NJets,nBinsMHT,MHTBinRectangular,nBinsHT,HTBinRectangular  );
        
        sprintf( cuts, "(%s && %s )%s", commoncuts,bcutstringRectangular[b],weightstring );
        //HT30:MHT:NJets30
        
        sprintf( arg1, TString::Format("HT30:MHT:NJets30>>sig4t1500__b%d",b).Data()) ;
        t1tt1500.Draw( arg1, cuts );
        sprintf( arg1, TString::Format("HT30:MHT:NJets30>>sig4t1200__b%d",b).Data()) ;
        t1tt1200.Draw( arg1, cuts );
        
        sprintf( arg1, TString::Format("HT30:MHT:NJets30>>sig4q1400__b%d",b).Data()) ;
        t1qq1400.Draw( arg1, cuts );
        sprintf( arg1, TString::Format("HT30:MHT:NJets30>>sig4q1000__b%d",b).Data()) ;
        t1qq1000.Draw( arg1, cuts );
        
        sprintf( arg1, TString::Format("HT30:MHT:NJets30>>sig4b1500__b%d",b).Data()) ;
        t1bb1500.Draw( arg1, cuts );
        sprintf( arg1, TString::Format("HT30:MHT:NJets30>>sig4b1000__b%d",b).Data()) ;
        t1bb1000.Draw( arg1, cuts );
        
        sprintf( arg1, TString::Format("HT30:MHT:NJets30>>qcd__b%d",b).Data()) ;
        QCDCH.Draw( arg1, cuts ) ;
        sprintf( arg1, TString::Format("HT30:MHT:NJets30>>tt__b%d",b).Data()) ;
        tt.Draw( arg1, cuts ) ;
        sprintf( arg1, TString::Format("HT30:MHT:NJets30>>WJ__b%d",b).Data()) ;
        WJets.Draw( arg1, cuts );
        sprintf( arg1, TString::Format("HT30:MHT:NJets30>>ZI__b%d",b).Data()) ;
        Zinv.Draw( arg1, cuts ) ;
    
        sig4t1500_[b]->Write();
        sig4t1200_[b]->Write();
        
        sig4q1000_[b]->Write();
        sig4q1400_[b]->Write();
        
        sig4b1500_[b]->Write();
        sig4b1000_[b]->Write();
        
        qcd_[b]->Write();
        WJ_[b]->Write();
        tt_[b]->Write();
        ZI_[b]->Write();
    }
}
//THIS DEFINES THE BINNING and PRODUCES THE LATEX TABLE
void fillEventYields(TString Options="Signal", float mu=1.0, float lumi=4.0){
    TH3F*sig4t1200_[4];
    TH3F*sig4t1500_[4];
    
    TH3F*sig4b1500_[4];
    TH3F*sig4b1000_[4];
    TH3F*sig4q1400_[4];
    TH3F*sig4q1000_[4];
    
    TH3F*qcd_[4];
    TH3F*tt_[4];
    TH3F*WJ_[4];
    TH3F*ZI_[4];
    TFile*f0=new TFile(TString::Format("Bins4DBINS_Lumi%2.2ffb.root", lumi).Data());
    for(int b=0; b<4; ++b){
        
        sig4t1500_[b]=(TH3F*)f0->Get(TString::Format("sig4t1500__b%d",b).Data());
        sig4t1200_[b]=(TH3F*)f0->Get(TString::Format("sig4t1200__b%d",b).Data());
        
        sig4b1500_[b]=(TH3F*)f0->Get(TString::Format("sig4b1500__b%d",b).Data());
        sig4b1000_[b]=(TH3F*)f0->Get(TString::Format("sig4b1000__b%d",b).Data());
        
        sig4q1400_[b]=(TH3F*)f0->Get(TString::Format("sig4q1400__b%d",b).Data());
        sig4q1000_[b]=(TH3F*)f0->Get(TString::Format("sig4q1000__b%d",b).Data());
        
        qcd_[b]=(TH3F*)f0->Get(TString::Format("qcd__b%d",b).Data());
        tt_[b]=(TH3F*)f0->Get(TString::Format("tt__b%d",b).Data());
        WJ_[b]=(TH3F*)f0->Get(TString::Format("WJ__b%d",b).Data());
        ZI_[b]=(TH3F*)f0->Get(TString::Format("ZI__b%d",b).Data());
    }
    
    //signal strength
    FILE* fp = fopen(  "OutputTable.tex", "w" ) ;
    
    
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
                        
                        qcd[ibin]=qcd_[nb]->GetBinContent( ij, mhti, hti );
                        zi[ibin]=ZI_[nb]->GetBinContent( ij, mhti, hti );
                        wj[ibin]=WJ_[nb]->GetBinContent( ij, mhti, hti );
                        ttbar[ibin]=tt_[nb]->GetBinContent( ij, mhti, hti );
                        //for now observed data is set to total bkg yield
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
                        
                        qcd[ibin]=qcd_[nb]->GetBinContent( ij, mhti, 2 )+qcd_[nb]->GetBinContent( ij, mhti, 3 );
                        zi[ibin]=ZI_[nb]->GetBinContent( ij, mhti, 2 )+ZI_[nb]->GetBinContent( ij, mhti, 3 );
                        wj[ibin]=WJ_[nb]->GetBinContent( ij, mhti, 2 )+WJ_[nb]->GetBinContent( ij, mhti, 3 );
                        ttbar[ibin]=tt_[nb]->GetBinContent( ij, mhti, 2)+tt_[nb]->GetBinContent( ij, mhti, 3);
                        
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
                        qcd[ibin]=qcd_[nb]->GetBinContent( ij, mhti, 1 )+qcd_[nb]->GetBinContent( ij, mhti, 2 );
                        zi[ibin]=ZI_[nb]->GetBinContent( ij, mhti, 1 )+ZI_[nb]->GetBinContent( ij, mhti, 2 );
                        wj[ibin]=WJ_[nb]->GetBinContent( ij, mhti, 1 )+WJ_[nb]->GetBinContent( ij, mhti, 2 );
                        ttbar[ibin]=tt_[nb]->GetBinContent( ij, mhti, 1)+tt_[nb]->GetBinContent( ij, mhti, 2);
                        
                        if(hti==3){
                            boxcount=5;
                            sig4t1500[ibin]=sig4t1500_[nb]->GetBinContent( ij, mhti, hti );
                            sig4t1200[ibin]=sig4t1200_[nb]->GetBinContent( ij, mhti, hti );
                            sig4q1400[ibin]=sig4q1400_[nb]->GetBinContent( ij, mhti, hti );
                            sig4q1000[ibin]=sig4q1000_[nb]->GetBinContent( ij, mhti, hti );
                            sig4b1500[ibin]=sig4b1500_[nb]->GetBinContent( ij, mhti, hti );
                            sig4b1000[ibin]=sig4b1000_[nb]->GetBinContent( ij, mhti, hti );
                            qcd[ibin]=qcd_[nb]->GetBinContent( ij, mhti, hti );
                            zi[ibin]=ZI_[nb]->GetBinContent( ij, mhti, hti );
                            wj[ibin]=WJ_[nb]->GetBinContent( ij, mhti, hti );
                            ttbar[ibin]=tt_[nb]->GetBinContent( ij, mhti, hti );
                        }
                        ++ibin;
                    }
                    fprintf(fp, "HT-MHTBin%d jetbin%d btag%d & %4.2f & %4.2f & %4.2f & %4.2f & %4.2f & %4.2f & %4.2f & %4.2f  & %4.2f & %4.2f  \\\\ \n", boxcount,ij, nb,qcd[ibin-1], ttbar[ibin-1],zi[ibin-1],wj[ibin-1],sig4t1500[ibin-1],sig4t1200[ibin-1],sig4q1400[ibin-1],sig4q1000[ibin-1],sig4b1500[ibin-1],sig4b1000[ibin-1] );
                    std::cout<<"Ibin "<<ibin<<std::endl;
                }
            }
        }
    }
    fprintf(fp,"\\hline\n");
    fprintf(fp,"\\end{tabular}}\n");
    fprintf(fp,"\\caption{TEST}\n");
    fprintf(fp,"\\end{table}\n");
    fprintf(fp,"\\end{document}\n"); //made Latex File with Yields
    f0->Close();
    fclose(fp);
}

//THis prints the data cards with specified Uncertainties (entered by hand for now)
void MakeCombineDataCards(int mGlu, int MLSP, float mu=1.0, float lumi=4, TString Options="", int bin=0){
    float sig[totalbins];
    float obs[totalbins];
    fillEventYields("Signal", mu, lumi);
    
    for(int i=0; i<totalbins; ++i){
        if(Options=="T1tttt" && mGlu==1500)sig[i]=sig4t1500[i];
        if(Options=="T1tttt" && mGlu==1200)sig[i]=sig4t1200[i];
        if(Options=="T1qqqq" && mGlu==1400)sig[i]=sig4q1400[i];
        if(Options=="T1qqqq"  && mGlu==1000)sig[i]=sig4q1000[i];
        if(Options=="T1bbbb" && mGlu==1500)sig[i]=sig4b1500[i];
        if(Options=="T1bbbb" && mGlu==1000)sig[i]=sig4b1000[i];
        obs[i]=(qcd[i]+ zi[i]+wj[i]+ttbar[i] + (mu*sig[i]));
    }
    float qcdscale=10.0;
    float ttbarScale=1.0;

    TString str=(TString::Format("./DataCards/SensStudyLumi%2.2f_Bin%d_M%d_m%d_%s.dat",lumi,bin, mGlu, MLSP,Options.Data())).Data();
    // const char outputfilename[100]=str.Data();
    
    FILE* fp = fopen(  str.Data(), "w" ) ;
    
    fprintf(fp, "imax %d number of channels\n", 3);//signal region PLUS 3 control bins
    fprintf(fp, "jmax %d number of backgrounds (QCD, Zinv, WJttbar)\n",3);//4 bkg processes
    fprintf(fp, "kmax * nuissance\n");
    fprintf(fp, "------------\n");
    fprintf(fp, "bin Bin%d BinContQ%d BinContW%d ", bin,bin, bin);
    //4 bins
   fprintf(fp, "\n observation %g %g %g ", obs[bin], qcdscale*qcd[bin],ttbarScale*(wj[bin]+ttbar[bin]));
   //4 Expected Count bins (MC)
    fprintf(fp, "\nbin Bin%d  Bin%d  Bin%d  Bin%d ", bin,bin, bin, bin);
    fprintf(fp, "BinContQ%d  BinContQ%d  BinContQ%d  BinContQ%d ",bin, bin,bin, bin);
    fprintf(fp, "BinContW%d  BinContW%d  BinContW%d  BinContW%d ", bin,bin, bin, bin);
    //fprintf(fp, "BinContT%d  BinContT%d  BinContT%d  BinContT%d  BinContT%d ",bin, bin,bin, bin, bin);
    
    fprintf(fp, "\nprocess sig QCD Zinv WJttbar ");
    fprintf(fp, "sig QCD Zinv WJttbar  ");
    fprintf(fp, "sig QCD Zinv WJttbar  ");
    
    fprintf(fp, "\nprocess %d %d %d %d ", 0, 1,2,3);
    fprintf(fp, "%d %d %d %d ",0, 1,2,3);
    fprintf(fp, "%d %d %d %d ",0, 1,2,3);
    
    //NOW THIS IS MY EXPECTED SIGNAL REGION!
    fprintf(fp, "\nrate %g ", sig[bin]);
    if(qcd[bin]>0.0000000000000000001)fprintf(fp, " %g ", qcd[bin]);
    else fprintf(fp, " %g ",0.001);
    
    fprintf(fp, " %g ", zi[bin]);
    if(wj[bin]+ttbar[bin]>0.0000000000000000001)fprintf(fp, " %g ",wj[bin]+ttbar[bin]);
    else fprintf(fp, " %g ",0.001);
    

    
    
    //QCD Region 1
    fprintf(fp, " %g ",0.);
    if(qcd[bin]>0.0000000000000000001)fprintf(fp, " %g ",qcdscale*qcd[bin]);
    else fprintf(fp, " %g ",qcdscale*0.001);
    //fprintf(fp, " %g ",10.);
    fprintf(fp, " %g %g ",0., 0.);
    
    //WJ/TTbar Region 1
    fprintf(fp, " %g %g %g",0.,0.,0.0);
    if(wj[bin]+ttbar[bin]>0.0000000000000000001)fprintf(fp, " %g ",ttbar[bin]+wj[bin]);
    else fprintf(fp, " %g ", ttbarScale*0.001);
    fprintf(fp, "\n");
   

    float logUErr=100.;
if(qcd[bin]*qcdscale>0.0000000000000000001){
    fprintf(fp, "rateBqcd%d lnU - %8.1f - - ",bin, logUErr );
    fprintf(fp, " - %8.1f - - ",logUErr);
    fprintf(fp, " - - - -\n ");
    }
else {
	logUErr=10000;
    fprintf(fp, "rateBqcd%d lnU - %8.1f - - ",bin, logUErr );
    fprintf(fp, " - %8.1f - - ",logUErr);
    fprintf(fp, " - - - -\n ");

}
    
    fprintf(fp, "LogBqcd%d lnN - %g - -  ",bin, 1.3 );
    fprintf(fp, " - - - -  ");
    fprintf(fp, " - - - -  \n");
    
    if(ttbar[bin]*ttbarScale>0.0000000000000000001){
        logUErr=100;
    fprintf(fp, "rateBW%d lnU - - - %8.1f  ",bin, logUErr );
    fprintf(fp, " - - - -  ");
    fprintf(fp, " - - - %8.1f  \n ",logUErr);
    }
    else{
	logUErr=10000;
    fprintf(fp, "rateBW%d lnU - - - %8.1f  ",bin, logUErr );
    fprintf(fp, " - - - -  ");
    fprintf(fp, " - - - %8.1f  \n ",logUErr);	

    }
    fprintf(fp, "LogBW%d lnN - - - %g  ",bin, 1.3 );
    fprintf(fp, " - - - -  ");
    fprintf(fp, " - - - -  \n");
    

    
    fprintf(fp, "LogBZ%d lnN - - %g - ",bin, 1.3 );
    fprintf(fp, " - - - - ");
    fprintf(fp, " - - - - ");
    fprintf(fp, " - - - - \n");

    
}
