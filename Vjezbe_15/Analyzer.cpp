#define Analyzer_cxx
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
#include <TMultiGraph.h>

using namespace std;

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

	TLorentzVector *Higgs;
	Higgs=new TLorentzVector();
	
	//TH1F *mass=new TH1F(" "," ",100,0,700);
	
	TF1 *fit;
	fit=new TF1("","[0]*exp(-x/[1])",0,700);
	fit->SetParameter(0,500);
	fit->SetParName(0,"N_{SM}");
	fit->FixParameter(1,100);
	fit->SetParName(1,"#Zeta_{SM}");
	


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  
	  
	  Higgs->SetPxPyPzE(particle1_px+particle2_px,particle1_py+particle2_py,particle1_pz+particle2_pz,particle1_E+particle2_E);
	  mass->Fill(Higgs->M());
   }
   
   TCanvas *C;
   C=new TCanvas("","",1600,900);
   
   gStyle->SetOptStat(0);
   mass->Fit(fit);
   mass->SetMarkerStyle(20);
   mass->SetMarkerSize(0.6);
   mass->GetXaxis()->SetTitle("m_{H}");
   mass->GetYaxis()->SetTitle("Events/7GeV");
   mass->Draw("EP");

   fit->Draw("same");
   
   C->SaveAs("ZD1.pdf");
}

void Analyzer::Statistic(){
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
	
	//C->SaveAs("StatisticPDF.pdf");
}


void Analyzer::pValue(){
	TRandom3 *r3 = new TRandom3();
	
	//TH1F *histo = new TH1F("H","H",100,0,700);
	//TH1F *ChiSquare_histo=new TH1F("CS_h","CS_h",200,0,30);
	
	int i, ii, iii;
	double m_H=0.;
	double p1=-1., p2=190.,p3=0.5;
	double ChiSquare, ChiSquareObs=0.;
	int k=0;
	double pValue=0., pValueObs=0.;
	
	TF1 *fit=new TF1("histogram fit","[0]*exp(-x/[1])",0,700);
	fit->SetParameter(0,500);
	fit->SetParName(0,"N_{SM}");
	fit->FixParameter(1,100);
	fit->SetParName(1,"#Zeta_{SM}");
	
	TGraph *scan=new TGraph();
	TGraph *obs=new TGraph();
	
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
				ChiSquare=fit->GetChisquare();
				pValue=ChiSquare_histo->Integral(ChiSquare_histo->FindBin(ChiSquare),200)/ChiSquare_histo->Integral();
				scan->SetPoint(k,m_H,pValue);
				//ChiSquare_histo->Fill(fit->GetChisquare());
				mass->Fit(fit,"Q","",m_H-10.,m_H+10.);
				ChiSquareObs=fit->GetChisquare();
				pValueObs=ChiSquare_histo->Integral(ChiSquare_histo->FindBin(ChiSquareObs),200)/ChiSquare_histo->Integral();
				obs->SetPoint(k,m_H,pValueObs);
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
	//scan->SetMinimum(0.00001);
	
	
	/*scan->GetXaxis()->SetTitle("m_{H}");
	scan->GetYaxis()->SetTitle("p-value");
	scan->SetTitle("P-value scan");*/
	scan->SetLineColor(kBlack);
	scan->SetMarkerColor(kBlack);
	scan->SetLineStyle(kDashed);
	scan->SetLineWidth(2);
	scan->SetMarkerStyle(20);
	scan->SetMarkerSize(0.6);
	
	//obs->Draw("AL*");
	/*obs->GetXaxis()->SetTitle("m_{H}");
	obs->GetYaxis()->SetTitle("p-value");
	obs->SetTitle("P-value scan");*/
	obs->SetLineColor(kRed);
	obs->SetMarkerColor(kRed);
	obs->SetLineWidth(2);
	obs->SetMarkerStyle(20);
	obs->SetMarkerSize(0.6);
	
	//scan->Draw("AL*");
	//obs->Draw("same");
	
	TMultiGraph *TheoryObs;
	TheoryObs=new TMultiGraph();
	TheoryObs->Add(scan);
	TheoryObs->Add(obs);
	TheoryObs->SetTitle("P-value scan");
	TheoryObs->SetMinimum(0.00001);
	TheoryObs->Draw("ALP");
	TheoryObs->GetXaxis()->SetRangeUser(0,700);
	TheoryObs->GetXaxis()->SetTitle("m_{H}");
	TheoryObs->GetYaxis()->SetTitle("p-value");
	
	TLegend *legend=new TLegend(0.75,0.1,0.9,0.25);
	legend->AddEntry(scan, "Expected", "f");
	legend->AddEntry(obs, "Observed", "f");
	legend->Draw();
	
	
	C->SaveAs("ZD2.pdf");
}