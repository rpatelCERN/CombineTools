void DummyCard(){
for(int i=0; i<10; ++i){
 	FILE* fp = fopen(  TString::Format("DummyPL_%1.2f.dat", i*0.1).Data(), "w");
        fprintf(fp,"max 1 number of channels \n");
	fprintf(fp,"jmax 1 number of backgrounds (QCD, Zinv, WJ, ttbar) \n");
	fprintf(fp,"kmax * nuissance\n");
	fprintf(fp,"------------\n");
	fprintf(fp,"bin 71\n");
	fprintf(fp,"observation 4\n");
	fprintf(fp,"bin 71 71\n");
	fprintf(fp,"process sig bkg\n");
	fprintf(fp,"process 0 1\n");
	fprintf(fp,"rate 4.0 0.0\n");
	fprintf(fp,"BqcdgmN gmN 0 - 1.0\n");
	fprintf(fp,"BqcdLog lnN  - %1.2f\n", 1+i*0.1);
}

}
