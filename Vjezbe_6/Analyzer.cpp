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

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  
	  
	  
	  /*for (int i=0; i<4; i++){ //4 leptona, Pt-transversalni moment
	  cout << LepPt->at(i) << endl;
	  }*/
	  
	  
   }
}


void Analyzer::PlotHistogram()
{
	TH1F *histo0, *histo1, *histo2, *histo3, *histo4;
	
	histo0=	new TH1F("pt1", "Transversal momenta of decayed particles", 250,0,140); //prvi broj je koliko ima binova?
	//drugi je odakle krece, treci dokle ide
	//prvi string " " je naslov u legendi, drugi je naslov histograma
	histo1=	new TH1F("pt2", " ", 250,0,140);
	histo2=	new TH1F("pt3", " ", 250,0,140);
	histo3=	new TH1F("pt4", " ", 250,0,140);
	histo4=new TH1F("4leptons", "mass reconstruction", 100, 90,140);
	
	TLorentzVector *particle0;
	TLorentzVector *particle1;
	TLorentzVector *particle2;
	TLorentzVector *particle3;
	TLorentzVector *Z1;
	TLorentzVector *Z2;
	TLorentzVector *Higgs;
	
	particle0= new TLorentzVector();
	particle1=new TLorentzVector();
	particle2=new TLorentzVector();
	particle3=new TLorentzVector();
	Z1=new TLorentzVector();
	Z2=new TLorentzVector();
	Higgs=new TLorentzVector();
	
	double w, L;
	L=137;
	
	if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) { //vrti petlju po branchevima
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  
	  
	  //cout << px1;
	  
	  //punjenje histograma
	  
	  /*histo0->Fill(LepPt->at(0)); //u zagrade cime ga zelim fillovat
	  histo1->Fill(LepPt->at(1));
	  histo2->Fill(LepPt->at(2));
	  histo3->Fill(LepPt->at(3));*/
	  
	  particle0->SetPtEtaPhiM(LepPt->at(0),LepEta->at(0),LepPhi->at(0),0);
	  particle1->SetPtEtaPhiM(LepPt->at(1),LepEta->at(1),LepPhi->at(1),0);
	  particle2->SetPtEtaPhiM(LepPt->at(2),LepEta->at(2),LepPhi->at(2),0);
	  particle3->SetPtEtaPhiM(LepPt->at(3),LepEta->at(3),LepPhi->at(3),0);
	  
	  *Z1=*particle0+*particle1;
	  *Z2=*particle2+*particle3;
	  
	  //cout << histogram->GetBinContent(40) << endl;
	  
	  //*1000 JER JE JEDNO U PIKO A DRUGO U FEMTOBARNIMA NA -1
	  w=(L*1000*xsec*overallEventWeight)/histogram->GetBinContent(40);
	  *Higgs=*Z1+*Z2;
	  histo4->Fill(Higgs->M(),w);
	  
   }
   
	//stvaram platno za crtanje histograma
	
	/*TCanvas *canvas1;
	canvas1=new TCanvas("canvas1", "canvas1", 800, 1000); //dimenzija pixela x i y
	
	//c1->cd(); ako zelim da ovaj bude u kojeg ce crtat jer Draw po defaultu crta u zadnje stvoreni Canvas
	//canvas1->Divide(2,2);
	//canvas1->cd(1);
	
	histo0->Draw(); //stvaram histogram
	histo1->Draw("same");
	histo2->Draw("same");
	histo3->Draw("same");
	
	//postavljam naslove osi u histogramu
	histo1->GetXaxis()->SetTitle("Transversal momentum [GeV/c]");
	histo1->GetYaxis()->SetTitle("Events");
	
	
	//mijenjam boje histograma
	histo0->SetLineColor(kRed);
	histo0->SetFillColor(kRed);
	histo1->SetLineColor(kBlue);
	histo2->SetLineColor(kYellow);
	histo3->SetLineColor(kGreen);
	
	//postavljanje legende
	gStyle->SetOptStat(0000);
	TLegend *legend = new TLegend(.75,.75,1.0,.95);  //x1,y1,x2,y2 are the coordinates of the Legend
	legend->SetHeader("Results of my simulation", "C"); //C for centering
    legend->AddEntry(histo0,"First lepton");
    legend->AddEntry(histo1,"Second lepton");
	legend->AddEntry(histo2,"Third lepton");
	legend->AddEntry(histo3,"Fourth lepton");
	
    legend->Draw();
	
	
	//spremam histogram u razlicite formate
	canvas1->SaveAs("VJ6.pdf");
	canvas1->SaveAs("VJ6.png");
	canvas1->SaveAs("VJ6.root");*/
	
	
	TCanvas *canvas2;
	canvas2=new TCanvas("canvas2", "canvas2", 800,1000);
	histo4->Draw("HISTO");
	
	histo4->GetXaxis()->SetTitle("mass_{4l} [GeV]");
	histo4->GetYaxis()->SetTitle("Events");
	
	cout << histo4->Integral() << endl;
	
	gStyle->SetOptStat(0000);
	TLegend *legend = new TLegend(.75,.75,1.0,.95);  //x1,y1,x2,y2 are the coordinates of the Legend
	//legend->SetHeader("Results of my simulation", "C"); //C for centering
    legend->AddEntry(histo4,"gluon-gluon fusion");
	legend->Draw();
	
	
	canvas2->SaveAs("VJ6_zd4.pdf");
}

