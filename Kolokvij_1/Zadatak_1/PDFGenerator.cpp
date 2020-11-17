#include "PDFGenerator.h"
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <Riostream.h>
#include <TColor.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <vector>
#include <TGraph.h>
#include <TH2F.h>

PDFGenerator::PDFGenerator(){
	cout<<"Objekt je uspjesno kreiran"<<endl;
}

void PDFGenerator::GenerateQuadraticPDF(int N){
	srand(time(NULL));
	//N je koliko cemo imati dogadaja ukupno
	double x,y;
	double i;
	int u, a;
	int included=0;
	TH1F* histo;
	histo=new TH1F("histo", "histo",50,-2,2);
	
	for(i=0;i<N;i++){
		i=-1.+(1.-(-1.))*(rand()%100)/100; //generiranje broja od -1 do 1 do dvije decimale
		//cout<<" "<<i<<endl; //provjera je li se generira broj u trazenom intervalu
		
		x=-1.+(1.-(-1.))*(rand()%100)/100;
		u=0.+(3./4-(-0.))*(rand()%100)/100;
		if(u<=((-3./4)*x*x+3./4)){
			included=included+1;
			a=(int)included/N;
			histo->Fill(a);
		}
		
	}
	TCanvas *canvas;
	canvas=new TCanvas("canvas", "canvas", 1600, 900);
	histo->Draw("histo");
	
	
	canvas->SaveAs("Zad_1.png");
	
}