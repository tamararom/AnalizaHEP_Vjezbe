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
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

void Analyzer::PlotHistogram(){
   double t_sum, tau_3, tau_4;
   t_sum=0;
   double sigma_fit, sigma_analyt, sigma_low, sigma_up, min;
   
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  
	  histogram->Fill(t);
	  t_sum=t_sum+t;
   }

   tau_3=t_sum/nentries;
   //cout << ""<<tau;
   
   TF1* f;
   TF1 *f2;
   
   
   f=new TF1("fit0", "[0]*(1/[1]*exp(-x/[1]))", 0,8); //ovako otprilike je islo za prvi zadatak
   //gdje je 0 konstanta koju trazimo isto, a 1 tau
   f->SetParameter(0,200.3);
   f->SetParName(0,"const");
   f->SetParameter(1,1);
   f->SetParName(1,"#tau");
   double tau_1=1.237; //da nam graf
   sigma_fit = f->GetParError(1); //iz zd 1
   
   
 
   f2=new TF1("fit", "(1/x)*[1]*exp(-[0]/x)", 0,8); //LIKELIHOOD ### ZD2 ###
   f2->SetParameter(0,1);
   f2->SetParName(0,"time");
   f2->SetParameter(1,200.3);
   f2->SetParName(1,"const");
   //za ovo ne racunamo gresku jer je jedno mjerenje
   
   
   //****ZD 3*****
   //ZA TAU (tau_3=t_sum/nentries;) DOBIJEMO U ### ZD3: 1.23506, DOK JE U ZD1. BILA 1.237 ###
   sigma_analyt=sqrt(-pow(tau_3,3)/(nentries*tau_3-2*t_sum)); //iz zd 3
   
   TF1* f1; //MAXIMUM-LIKELIHOOD
   f1=new TF1("-2lnL", "-2*([0]*log(1/x)-[1]/x)",1.15,1.3); //-2lnL funkcija
   f1->SetParameter(0,nentries);
   f1->SetParameter(1,t_sum);
   
   //IZ MINIMIZACIJE -2lnL dobijemo TAU isto:
   //cout << "Tau iz minimuma -2lnL: \t" << f1->GetMinimumX();
   //dobijemo 1.23506 ovako! ########## ZD4. ###############
   
   tau_4=f1->GetMinimumX(1.15,1.3,1.E-10,100,false);
   min=f1->GetMinimum(1.15,1.3,1.E-10,100,false);
   sigma_low=tau_4-f1->GetX(min+1,1.15,1.24,1.E-10,100,false); 
   sigma_up=f1->GetX(min+1,1.24,1.3,1.E-10,100,false)-tau_4;
  
   

   
   
   f1->GetXaxis()->SetRangeUser(1.18,1.28);
   TCanvas *canvas1;
   canvas1=new TCanvas("canvas1", "canvas1", 1600, 900);
   //canvas1->Divide(2);
   canvas1->cd(1);
   f1->SetTitle("Distribution; Time [s]; Events/0.5");
   f1->Draw();
   
   gStyle->SetOptFit();
   canvas1->cd(2);
   histogram_fit->Add(histogram);
   histogram_fit->Fit(f, "l");
   histogram_fit->SetTitle("Distribution; Time [s]; Events/0.2");
   histogram_fit->Draw();
   
   
   cout << endl << "\t\t############### Results ###############" << endl;
   cout << " method\t\t\t\t tau \t\tsigma" << endl;
   cout << "----------------------------------------------------------------------------" << endl;
   cout << "exponential fit\t\t\t" << tau_1 << "\t\t-+ " << f->GetParError(1) << endl;
   cout << "analytical result\t\t" << tau_3 << "\t\t-+ " << sigma_analyt << endl;
   cout << "-2lnL\t\t\t\t" << tau_4 << "\t\t- " << sigma_low << "\t+ " << sigma_up << endl;
  
   //5. zd na ruke pisemo i to moze pitat na usmenom a onda kod samo racuna
   
   //canvas1->SaveAs("VJ9_ZD5.png");
	
}

void Analyzer::Bins(){ //######DODATNI ZADATAK#######
/*UPUTE ZA DODATNI ZADATAK*/
//NAPRAVIT T GRAF IZ PRVOG ZD DA VIDIMO KAKO SE MIJENJA OVISNOST PARAMETRA O BROJU BINOVA
//NAPRAVIT JOS MJERENJA I BROJA BINOVA -> NAC NEKI MINIMUM KAD JE NAJPRECIZNIJE
//LOOP ILI RAZLICITE HISTOGRAME
	
	
	//stvaranje
	TGraph *graph;
	graph=new TGraph();
	TH1F *histograms;
	TF1* function;
	
	function = new TF1("fit", "[0]*(1/[1]*exp(-x/[1]))", 0,8);
	function->SetParameter(0,200.3);
	function->SetParName(0, "const");
	function->SetParameter(1,1);
	function->SetParName(1,"tau");
	
	
	double N_bins, t_sum, tau;
	
	 for(N_bins=10;N_bins<=150;N_bins++){
		histograms=new TH1F(" "," ",N_bins,0,8);
		t_sum=0;
		
	 if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  
		histograms->Fill(t);
		//t_sum=t_sum+t; //ovo ide ako bi radila za ZD3 a ne ZD1
	  }
	  //tau=t_sum/nentries;
	  histograms->Fit(function,"l");
	  tau=function->GetParameter(1);
	  graph->SetPoint(N_bins,N_bins,tau);
   }
	
	TCanvas *canvas_x;
	canvas_x =new TCanvas("canvas", "canvas", 1600, 900);
	
	graph->SetMinimum(1.2);
	graph->SetMaximum(1.25);
	graph->GetXaxis()->SetTitle("Number of bins");
	graph->GetYaxis()->SetTitle("#tau / s");
	graph->SetTitle("Fitted #tau dependence of bin number");
	graph->Draw("AC*"); //graph draw optins
	
	canvas_x->SaveAs("ZD_extra.png");
	
}

