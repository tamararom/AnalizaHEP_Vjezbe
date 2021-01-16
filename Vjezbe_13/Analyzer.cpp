#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TH1F.h>
#include <TMath.h>
#include <TLegend.h>
#include <iostream>
#include <Riostream.h>
#include <TColor.h>
#include <TLorentzVector.h>
#include <vector>
#include <TGraph.h>
#include <TH2F.h>
#include <TLine.h>
#include <TLatex.h>

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
	
	TRandom *height1;
	height1=new TRandom();
	
	int i, ii;
	double sum_height=0.;
	double sum_height2=0.;
	int bin_number;
	double p_value;
	double zscore;
	
	
	TH1F *testStat = new TH1F("test statistic PDF", "test statistic PDF", 500,160,170);
	TH1F *data = new TH1F(" ", " ", 500,160,170);


	medium_height = 0.;
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  data->Fill(height);
	  sum_height2=sum_height2+height;
   }
   medium_height=sum_height2/nentries;
   
   //cout << medium_height << endl; // this is t_observed
 
   for(i=0;i<1000000;i++){
	   sum_height=0.;
	   for(ii=0;ii<100;ii++){
		sum_height=sum_height+height1->Gaus(164.7,7.1);
	   }
	   testStat->Fill(sum_height/100);
   }
   //normalizacija
   testStat->Scale(1./testStat->Integral());
   
   
   
   //zelim p-value od 5% jer imamo mali uzorak tj na 0.05 odbacujem
   bin_number=testStat->FindBin(medium_height);
   p_value=testStat->Integral(bin_number,500);
   
   cout <<"P value:" << p_value << endl;
   //dobijem 5e-06 znaci da sam simulirala dosta lose podatke
   //tj pet puta u milijun dobijem to
   
   zscore=TMath::Sqrt(2)*TMath::ErfcInverse(2*p_value);
   cout <<"Significancy:" << zscore << endl; 
   //sigma je 4.4, dakle blizu smo 5 sigma
   
   gStyle->SetOptStat(000);
   TCanvas *canvas;
   canvas=new TCanvas("canvas","canvas",1600,900);
   
   testStat->GetXaxis()->SetTitle("t statistic");
   testStat->GetYaxis()->SetTitle("PDF");
   
   testStat->Draw("histo");
   TLine *line = new TLine(medium_height, 0., medium_height, 0.0105);
   //line->SetLineColor(kBlack);
   line->Draw();
   TLatex *text=new TLatex(medium_height,-0.001,"t_{obs}");
   text->Draw();
   
   canvas->SaveAs("ZD1.pdf");
   
}

void Analyzer::Comparison(TString name, double mu, double sigma){
	TRandom *height_;
	height_=new TRandom();
	
	int i, ii;
	double sum_Spain=0., sum_otherCountry=0.;
	double p_valueSpain, p_valueOther;
	double CL;
	
	TH1F *h_spain=new TH1F("","",500,150,180);
	TH1F *h_other=new TH1F("","",500,150,180);
	
	for(i=0;i<1000000;i++){
	   sum_Spain=0.;
	   sum_otherCountry=0.;
	   for(ii=0;ii<100;ii++){
		sum_Spain=sum_Spain+height_->Gaus(168.0,7.0);
		sum_otherCountry=sum_otherCountry+height_->Gaus(mu,sigma);
	   }
	   h_spain->Fill(sum_Spain/100);
	   h_other->Fill(sum_otherCountry/100);
   }
   h_spain->Scale(1./h_spain->Integral());
   h_other->Scale(1./h_other->Integral());
   
   
   p_valueSpain=h_spain->Integral(h_spain->FindBin(medium_height),500);
   p_valueOther=h_other->Integral(h_other->FindBin(medium_height),500);
   cout << "P-value data vs. Spain: " << p_valueSpain << endl;
   cout << "P-value data vs. " << name <<": " << p_valueOther << endl;
   
	if(name=="Netherlands"){
		CL=1-(h_other->Integral(0,h_other->FindBin(medium_height))/p_valueSpain);
		cout << "Rejecting Netherlands with confidence: " << CL*100 << "%" << endl;
	}
	else{
		CL=1-(p_valueOther/(h_spain->Integral(0,h_spain->FindBin(medium_height))));
		cout << "Rejecting " << name << " with confidence: " << CL*100 << "%" << endl; 
	}
	
	TCanvas *canvas1;
	canvas1=new TCanvas("","",1600,900);
	
	h_other->SetTitle("H0 vs H1");
	h_spain->SetTitle("H0 vs H1");
	h_other->GetXaxis()->SetTitle("t statistic");
    h_other->GetYaxis()->SetTitle("PDF");
	h_spain->GetXaxis()->SetTitle("t statistic");
    h_spain->GetYaxis()->SetTitle("PDF");
	h_spain->SetLineColor(kRed);
	
	if(name=="Italy"){
		h_other->Draw("histo");
		h_spain->Draw("histo same");
	}
	else{
		h_spain->Draw("histo");
		h_other->Draw("histo same");
	}
	
	TLine *line = new TLine(medium_height, 0., medium_height, 0.033);
	//line->SetLineColor(kBlack);
	line->Draw();
	TLatex *text=new TLatex(medium_height,-0.002,"t_{obs}");
	text->Draw();
	
	TLegend *legend=new TLegend(0.7,0.8,0.9,0.9);
	legend->AddEntry(h_spain, "Spain", "f");
	legend->AddEntry(h_other, name, "f");
	legend->Draw();

	
	
	
	canvas1->SaveAs("Spain_"+name+".pdf");
	
	
}
