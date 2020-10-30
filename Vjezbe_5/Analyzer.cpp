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
	  //cout << px1;
   }
}

void Analyzer::PlotHistogram()
{
	TH1F *histo1;
	TH1F *histo2;
	TH1F *histo3;
	histo1=	new TH1F("pt1", "Transversal momenta of decayed particles", 250,0,140); //prvi broj je koliko ima binova?
	//drugi je odakle krece, treci dokle ide
	//prvi string " " je naslov u legendi, drugi je naslov histograma
	histo2=	new TH1F("pt2", " ", 250,0,140);
	histo3=	new TH1F("pt_Higgs", "Higgs transversal momentum", 250,0,140);
	
	//zelimo rekonstruirati Higgsa iz raspadnutih cestica, koristimo klasu TLorentzVector
	TLorentzVector *particle1;
	TLorentzVector *particle2;
	TLorentzVector *Higgs;
	particle1= new TLorentzVector();
	particle2=new TLorentzVector();
	Higgs=new TLorentzVector();
	
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
	  histo1->Fill(pt1); //u zagrade cime ga zelim fillovat
	  histo2->Fill(pt2);
	  
	  particle1->SetPxPyPzE(px1,py1,pz1,E1); //za svaki branch u petlji uzimamo potrebne komponente cestica
	  particle2->SetPxPyPzE(px2,py2,pz2,E2); //na ovaj nacin iz komponenti dobivamo cetverovektore cestica
	  *Higgs=*particle1+*particle2; //jednostavan nacin za dobiti Higgsov cetverovektor iz cestica raspada
	  
	  //nama u biti treba sada histogram TRANSVERSALNE KOL.GIBANJA. HIGGSA!
	  //znaci da trebamo korijen zbroja kvadriranih x i y komponenti iz rekonstruiranog cetverovektora
	  histo3->Fill(sqrt(Higgs->Px()*Higgs->Px()+Higgs->Py()*Higgs->Py()));
	  
	  
   }
	//stvaram platno za crtanje histograma
	TCanvas *canvas1;
	canvas1=new TCanvas("canvas1", "canvas1", 800, 1000); //dimenzija pixela x i y
	//c1->cd(); ako zelim da ovaj bude u kojeg ce crtat jer Draw po defaultu crta u zadnje stvoreni Canvas
	canvas1->Divide(2,2);
	canvas1->cd(1);
	histo1->Draw(); //stvaram histogram
	canvas1->cd(1);
	histo2->Draw("same");
	canvas1->cd(2);
	histo3->Draw("same");
	
	//postavljam naslove osi u histogramu
	histo1->GetXaxis()->SetTitle("Transversal momentum [GeV/c]");
	histo1->GetYaxis()->SetTitle("Events");
	histo3->GetXaxis()->SetTitle("Transversal momentum [GeV/c]");
	histo3->GetYaxis()->SetTitle("Events");
	
	//mijenjam boje histograma
	histo1->SetLineColor(kRed);
	histo1->SetFillColor(kRed);
	histo2->SetLineColor(kBlue);
	histo3->SetLineColor(kYellow);
	
	//postavljanje legende
	gStyle->SetOptStat(0000);
	TLegend *legend = new TLegend(.75,.75,1.0,.95);  //x1,y1,x2,y2 are the coordinates of the Legend
	legend->SetHeader("Results of my simulation", "C"); //C for centering
    legend->AddEntry(histo1,"Decayed particle 1");
    legend->AddEntry(histo2,"Decayed particle 2");
	legend->AddEntry(histo3,"Higgs");
    legend->Draw();
	
	
	//spremam histogram u razlicite formate
	canvas1->SaveAs("P_decayed+Higgs.pdf");
	canvas1->SaveAs("P_decayed+Higgs.png");
	canvas1->SaveAs("P_decayed+Higgs.root");
}
