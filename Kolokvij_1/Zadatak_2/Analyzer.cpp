#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
/*#include <iostream>
#include <Riostream.h>
#include <TColor.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <vector>
#include <TGraph.h>
#include <TH2F.h>
#include <TH1F.h>
using namespace std;*/

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
	  
	  cout << ele_pt << endl;
   }
}

void Analyzer::Drawing(){
	int i=1;
	
	TH1F *histo_ele_pt;
	histo_ele_pt=new TH1F("Ele_Pt", "Electron_Pt", 70,0,140);
	TH2F *histo_2D=new TH2F("Histo2D", "Ele_pt vs Scl_eta", 30,0,90,90,-3,3);
	
	
	
	//CITANJE DATOTEKE
	
	if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<100000;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  
	  //cout<< ele_pt << endl;
	  
	//if(i<=100){ //crtamo samo do prvih 10^5 dogadaja
	   //cout<<ele_pt<<endl;
	   histo_ele_pt->Fill(ele_pt);
	   histo_2D->Fill(ele_pt,scl_eta);
	   
	   
	   
	//}
	  //i=i+1;
   }
	
	TCanvas *canvas;
	canvas=new TCanvas("canvas", "canvas", 1600, 900);
	canvas->Divide(2);
	
	canvas->cd(1);
	gPad->SetLeftMargin(0.15);
	histo_ele_pt->Draw();
	histo_ele_pt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	histo_ele_pt->GetYaxis()->SetTitle("Events/ 2 GeV ");
	histo_ele_pt->SetLineColor(kRed);
	gStyle->SetOptStat(0000);
	
	canvas->cd(2);
	gPad->SetRightMargin(0.15);
	histo_2D->Draw("COLZ");
	histo_2D->SetTitle("Electron p_{T} vs. Electron ETA");
	histo_2D->GetXaxis()->SetTitle("p_{T} / [Gev/c]");
	histo_2D->GetYaxis()->SetTitle("Eta ");
	
	
	canvas->SaveAs("Zadatak_2.pdf");
	canvas->SaveAs("Zadatak_2.png");
	
	

}