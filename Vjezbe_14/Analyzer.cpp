#include "Analyzer.h"
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
#include <TF1.h>
#include <stdlib.h>
#include <TMath.h>
#include <TGraphPainter.h>
#include<TGraphErrors.h>
#include <TLine.h>
#include <TLatex.h>
#include <TRandom.h>
#include <TRandom3.h>

using namespace std;

Analyzer::Analyzer(){
	ChiSquare_histo=new TH1F("CS_h","CS_h",200,0,30);
}

void Analyzer::Generate(){
	TRandom3 *r3 = new TRandom3();
	
	//TH1F *histo = new TH1F("H","H",100,0,700);
	//TH1F *ChiSquare_histo=new TH1F("CS_h","CS_h",200,0,30);
	
	int i, ii, iii;
	double m_H=0.;
	
	TF1 *fit=new TF1("histogram fit","[0]*exp(-x/[1])",0,700);
	fit->SetParameter(0,500);
	fit->SetParName(0,"N_{SM}");
	fit->FixParameter(1,100);
	fit->SetParName(1,"#Zeta_{SM}");
	
	
	for(ii=0;ii<1000;ii++){
		TH1F *histo = new TH1F("H","H",200,0,700); //dodat u ime string +ii da se ne radi memory leak
		for(i=0;i<pow(10,5);i++){
			histo->Fill(r3->Exp(100));
		}
		
		for(iii=10;iii<690;iii=iii+5){ //stavimo od 10 da moze ici i lijevo
			m_H=iii/1.;
			
			//cout << m_H << endl;

			histo->Fit(fit,"Q","",m_H-10.,m_H+10.); //quiet -> nece ispisivati rez fita
			ChiSquare_histo->Fill(fit->GetChisquare());
		}
		//cout << fit->GetChisquare() << endl;
	}
	
	TCanvas *C=new TCanvas("","",1600,900);
	//C->Divide(2,1);
	
	/*C->cd(1);
	histo->Draw();
	fit->Draw("same");
	
	C->cd(2);*/
	gStyle->SetOptStat(0);
	ChiSquare_histo->GetXaxis()->SetTitle("#chi^{2}");
	ChiSquare_histo->GetYaxis()->SetTitle("PDF");
	ChiSquare_histo->SetTitle("PDF of test statistic");
	ChiSquare_histo->Draw();
	
	C->SaveAs("ZD1.pdf");
}

void Analyzer::PValueScan(){
	TRandom3 *r3 = new TRandom3();
	
	//TH1F *histo = new TH1F("H","H",100,0,700);
	//TH1F *ChiSquare_histo=new TH1F("CS_h","CS_h",200,0,30);
	
	int i, ii, iii;
	double m_H=0.;
	double p1=-1., p2=190.,p3=0.5;
	double ChiSquare;
	int k=0;
	double pValue=0.;
	
	TF1 *fit=new TF1("histogram fit","[0]*exp(-x/[1])",0,700);
	fit->SetParameter(0,500);
	fit->SetParName(0,"N_{SM}");
	fit->FixParameter(1,100);
	fit->SetParName(1,"#Zeta_{SM}");
	
	TGraph *scan=new TGraph();
	
	for(iii=10;iii<=690;iii=iii+5){
			m_H=iii/1.;
			//stvaranje histograma mora biti u skroz vanjskoj petlji pa smo ga premjestili ovdje
			TH1F *histo = new TH1F("H","H",200,0,700); //dodat u ime string +ii da se ne radi memory leak 
		for(ii=0;ii<1;ii++){ //broj eksperimenata
			//TH1F *histo = new TH1F("H","H",200,0,700); //dodat u ime string +ii da se ne radi memory leak
			for(i=0;i<pow(10,4);i++){ //broj dogadaja
				if(r3->Rndm()>(p1*(m_H-p2)*(m_H-p2)+p3)){ //razdvajanje signala i pozadine
					histo->Fill(r3->Exp(100)); //pozadina
				}
				else{//signal
					histo->Fill(r3->Gaus(m_H,0.0236*m_H));
				}
			}
			
			//for(iii=10;iii<690;iii=iii+5){ //stavimo od 10 da moze ici i lijevo do 0
				//m_H=iii/1.;
				
				//cout << m_H << endl;

				histo->Fit(fit,"Q","",m_H-10.,m_H+10.); //quiet -> nece ispisivati rez fita
				//ChiSquare_histo->Fill(fit->GetChisquare());
				ChiSquare=fit->GetChisquare();
				pValue=ChiSquare_histo->Integral(ChiSquare_histo->FindBin(ChiSquare),200)/ChiSquare_histo->Integral();
				scan->SetPoint(k,m_H,pValue);
				k++;
			//cout << fit->GetChisquare() << endl;
		}
	}
	
	TCanvas *C=new TCanvas("","",1600,900);
	//C->Divide(2,1);
	
	/*C->cd(1);
	histo->Draw();
	fit->Draw("same");
	
	C->cd(2);*/
	gPad->SetLogy();
	scan->SetMinimum(0.00001);
	scan->GetXaxis()->SetTitle("m_{H}");
	scan->GetYaxis()->SetTitle("p-value");
	scan->SetTitle("P-value scan");
	scan->Draw("AL*");
	
	C->SaveAs("ZD2.pdf");
	
	
}


