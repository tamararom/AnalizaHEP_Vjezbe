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


void Analyzer::PlotHistogram(TString path)
{
	
	TFile *f;

// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   f=new TFile(path);
   TDirectory * dir = (TDirectory*)f->Get(path+":/ZZTree");
   dir->GetObject("candTree",tree);
   Init(tree);
    //ovo je novo za dohvatit histogram
   histogram = (TH1F*)f->Get("ZZTree/Counters");

	
	TH1F *histo0, *histo1, *histo2, *histo3; //CANVAS 1,1
	//############## VJ6 ZD 2 ##############
	TH1F *histo02, *histo12, *histo22, *histo32; //CANVAS 1,2
	TH1F *histo03, *histo13, *histo23, *histo33; //CANVAS 1,3
	TH1F *histo04, *histo14, *histo24, *histo34; //CANVAS 1,4
	
	//TRANSVERSAL MOMENTA
	histo0=	new TH1F("LepPt1", "Transversal momentum", 50,0,140); //prvi broj je koliko ima binova?
	//drugi je odakle krece, treci dokle ide
	//prvi string " " je naslov u legendi, drugi je naslov histograma
	
	//### SIRINA BINA JE (TRECI BROJ-DRUGI BROJ)/PRVI BROJ!!!!
	//### ODNOSNO PRVI BROJ JE BROJ BINOVA, DRUGI I TRECI SU INTERVALI 
	//### ZNACI ZA 50,0,140 IMAMO 50 BINOVA, I BIN SIZE JE 2.8 GEV
	histo1=	new TH1F("LepPt2", "Transversal momentum",50,0,140);
	histo2=	new TH1F("LepPt3", "Transversal momentum", 50,0,140);
	histo3=	new TH1F("LepPt4", "Transversal momentum", 50,0,140);
	
	 //############## VJ6 ZD 2 ##############
	//PSEUDORAPIDITY
	histo02=new TH1F("LepEta1", "Pseudorapidity", 80,-4,4);
	histo12=new TH1F("LepEta2", "Pseudorapidity", 80,-4,4);
	histo22=new TH1F("LepEta3", "Pseudorapidity", 80,-4,4);
	histo32=new TH1F("LepEta4", "Pseudorapidity", 80,-4,4);
	//BIN SIZE JE 0.1 GEV
	
	//AZIMUTHAL ANGLE
	histo03=new TH1F("LepPhi1", "Azimuthal angle", 80,-5.2,5.2);
	histo13=new TH1F("LepPhi2", " ", 80,-5.2,5.2);
	histo23=new TH1F("LepPhi3", " ", 80,-5.2,5.2);
	histo33=new TH1F("LepPhi4", " ", 80,-5.2,5.2);
	//BIN SIZE JE 0.13 GEV
	
	//BDT 
	histo04=new TH1F("LepBDT1", "BDT", 30,0,10);
	histo14=new TH1F("LepBDT2", " ", 30,0,10);
	histo24=new TH1F("LepBDT3", " ", 30,0,10);
	histo34=new TH1F("LepBDT4", " ", 30,0,10);
	//BIN SIZE JE 0.33 GEV
	
	
	//#############################  VJ6. ZD3 I ZD4 ############################# 
	//HIGGS ############################# 
	/*TH1F *histo4;
	histo4=new TH1F("4leptons", "Mass reconstruction", 25, 90,140);*/
	//AKO JE BIN SIZE 2GEV A INTERVAL 50 ONDA NAM JE BR BINOVA 2*X=50, X=25
	
	
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
	
	double w, L, signal_discriminator, background_discriminator;
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
	  
	  w=(L*1000*xsec*overallEventWeight)/histogram->GetBinContent(40);
	  
	  //############ VJ6.ZAD2 ###########
	  //TRANSVERSAL MOMENTA
	  histo0->Fill(LepPt->at(0),w); //u zagrade cime ga zelim fillovat
	  histo1->Fill(LepPt->at(1),w);
	  histo2->Fill(LepPt->at(2),w);
	  histo3->Fill(LepPt->at(3),w);
	  
	  //PSEUDORAPIDITY
	  histo02->Fill(LepEta->at(0),w);
	  histo12->Fill(LepEta->at(1),w);
	  histo22->Fill(LepEta->at(2),w);
	  histo32->Fill(LepEta->at(3),w);
	  
	  //AZIMUTHAL ANGLE
	  histo03->Fill(LepPhi->at(0),w);
	  histo13->Fill(LepPhi->at(1),w);
	  histo23->Fill(LepPhi->at(2),w);
	  histo33->Fill(LepPhi->at(3),w);
	  
	  //BDT
	  histo04->Fill(LepBDT->at(0),w);
	  histo14->Fill(LepBDT->at(1),w);
	  histo24->Fill(LepBDT->at(2),w);
	  histo34->Fill(LepBDT->at(3),w);
	  
	  
	  //########## REKONSTRUKCIJA HIGGSA
	  particle0->SetPtEtaPhiM(LepPt->at(0),LepEta->at(0),LepPhi->at(0),0);
	  particle1->SetPtEtaPhiM(LepPt->at(1),LepEta->at(1),LepPhi->at(1),0);
	  particle2->SetPtEtaPhiM(LepPt->at(2),LepEta->at(2),LepPhi->at(2),0);
	  particle3->SetPtEtaPhiM(LepPt->at(3),LepEta->at(3),LepPhi->at(3),0);
	  
	  *Z1=*particle0+*particle1;
	  *Z2=*particle2+*particle3;
	  
	 
	  
	  //cout << histogram->GetBinContent(40) << endl;
	  
	  //*1000 JER JE JEDNO U PIKO A DRUGO U FEMTOBARNIMA NA -1
	  //w=(L*1000*xsec*overallEventWeight)/histogram->GetBinContent(40);
	  *Higgs=*Z1+*Z2;
	  //histo4->Fill(Higgs->M()); //VJEZBE 6 ZADATAK 3
	  if(path.Contains("ggH125")){
	  histogram_signal->Fill(Higgs->M(),w);
	  //c=1 za kinematickog diskriminatora signala
	  signal_discriminator=1/(1+1*p_QQB_BKG_MCFM/p_GG_SIG_ghg2_1_ghz1_1_JHUGen);
	  histogram_signal_discriminator->Fill(signal_discriminator,w);
	  histogram_2D_signal->Fill(Higgs->M(),signal_discriminator,w);
	  }
	  if(path.Contains("qqZZ")){
	  histogram_background->Fill(Higgs->M(),w);
	  //c=70 za kinematickog diskriminatora pozadine
	  background_discriminator=1/(1+70*p_QQB_BKG_MCFM/p_GG_SIG_ghg2_1_ghz1_1_JHUGen);
	  histogram_background_discriminator->Fill(background_discriminator,w);
	  histogram_2D_background->Fill(Higgs->M(),background_discriminator,w);
	  }
	  
   }
   
	//stvaram platno za crtanje histograma
	
	//##### VJEZBE 6 ZADATAK 2 ########
	
	/*TCanvas *canvas1;
	canvas1=new TCanvas("canvas1", "canvas1", 1600, 900); //dimenzija pixela x i y
	*/
	
	
	//c1->cd(); ako zelim da ovaj bude u kojeg ce crtat jer Draw po defaultu crta u zadnje stvoreni Canvas
	/*canvas1->Divide(2,2);
	canvas1->cd(1);
	histo2->Draw("HISTO");
	histo3->Draw("HISTO same");
	histo0->Draw("HISTO same"); //stvaram histogram
	histo1->Draw("HISTO same");
	//postavljam naslove osi u histogramu
	histo2->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	histo2->GetYaxis()->SetTitle("Events/2.8GeV");
	//mijenjam boje histograma
	histo0->SetLineColor(kRed);
	histo0->SetFillColor(kRed);
	histo1->SetLineColor(kBlue);
	histo2->SetLineColor(kYellow);
	histo3->SetLineColor(kGreen);
	//postavljanje legende
	gStyle->SetOptStat(0000);
	TLegend *legend = new TLegend(.75,.75,1.0,.95);  //x1,y1,x2,y2 are the coordinates of the Legend
	//legend->SetHeader(" ", "C"); //C for centering
    legend->AddEntry(histo0,"First lepton");
    legend->AddEntry(histo1,"Second lepton");
	legend->AddEntry(histo2,"Third lepton");
	legend->AddEntry(histo3,"Fourth lepton");
    legend->Draw();
	
	canvas1->cd(2);
	histo32->Draw("HISTO");
	histo12->Draw("HISTO same");
	histo02->Draw("HISTO same");
	histo22->Draw("HISTO same");
	histo32->GetXaxis()->SetTitle("Pseudorapidity");
	histo32->GetYaxis()->SetTitle("Events/0.1");
	histo02->SetLineColor(kRed);
	histo02->SetFillColor(kRed);
	histo12->SetLineColor(kBlue);
	histo22->SetLineColor(kYellow);
	histo32->SetLineColor(kGreen);
	gStyle->SetOptStat(0000);
	TLegend *legend2 = new TLegend(.75,.75,1.0,.95);  //x1,y1,x2,y2 are the coordinates of the Legend
	//legend2->SetHeader(" ", "C"); //C for centering
    legend2->AddEntry(histo02,"First lepton");
    legend2->AddEntry(histo12,"Second lepton");
	legend2->AddEntry(histo22,"Third lepton");
	legend2->AddEntry(histo32,"Fourth lepton");
    legend2->Draw();
	
	
	canvas1->cd(3);
	histo03->Draw("HISTO");
	histo23->Draw("HISTO same");
	histo33->Draw("HISTO same");
	histo13->Draw("HISTO same");
	histo03->GetXaxis()->SetTitle("Azimuthal angle [rad] ");
	histo03->GetYaxis()->SetTitle("Events/0.13rad");
	histo03->SetLineColor(kRed);
	histo03->SetFillColor(kRed);
	histo13->SetLineColor(kBlue);
	histo23->SetLineColor(kYellow);
	histo33->SetLineColor(kGreen);
	gStyle->SetOptStat(0000);
	TLegend *legend3 = new TLegend(.75,.75,1.0,.95);  //x1,y1,x2,y2 are the coordinates of the Legend
	//legend3->SetHeader(" ", "C"); //C for centering
    legend3->AddEntry(histo03,"First lepton");
    legend3->AddEntry(histo13,"Second lepton");
	legend3->AddEntry(histo23,"Third lepton");
	legend3->AddEntry(histo33,"Fourth lepton");
    legend3->Draw();
	
	canvas1->cd(4);
	histo04->Draw("HISTO");
	histo24->Draw("HISTO same");
	histo34->Draw("HISTO same");
	histo14->Draw("HISTO same");
	histo04->GetXaxis()->SetTitle("BDT");
	histo04->GetYaxis()->SetTitle("Events/0.33");
	histo04->SetLineColor(kRed);
	histo04->SetFillColor(kRed);
	histo14->SetLineColor(kBlue);
	histo24->SetLineColor(kYellow);
	histo34->SetLineColor(kGreen);
	gStyle->SetOptStat(0000);
	TLegend *legend4 = new TLegend(.75,.75,1.0,.95);  //x1,y1,x2,y2 are the coordinates of the Legend
	//legend4->SetHeader(" ", "C"); //C for centering
    legend4->AddEntry(histo04,"First lepton");
    legend4->AddEntry(histo14,"Second lepton");
	legend4->AddEntry(histo24,"Third lepton");
	legend4->AddEntry(histo34,"Fourth lepton");
    legend4->Draw();
	
	
	//spremam histogram u razlicite formate
	if(path.Contains("ggH125")){
	canvas1->SaveAs("VJ7_zd1_sg.pdf");}
	/*canvas1->SaveAs("VJ6_zd2.png");
	canvas1->SaveAs("VJ6_zd2.root");*/
	
	
	//#####################VJEZBE 6 ZADATAK 3 ######################################
	/*TCanvas *canvas2;
	canvas2=new TCanvas("canvas2", "canvas2", 800,1000);
	histo4->Draw("HISTO");
	//histo4->Draw(); VJ6.ZAD3.
	
	histo4->GetXaxis()->SetTitle("mass_{4l} [GeV]");
	histo4->GetYaxis()->SetTitle("Events/2GeV");
	
	cout << histo4->Integral() << endl;
	
	gStyle->SetOptStat(0000);
	TLegend *legend = new TLegend(.75,.75,1.0,.95);  //x1,y1,x2,y2 are the coordinates of the Legend
	legend->SetHeader("226.475 reconstructed Higgs bosons", "C"); //C for centering
    legend->AddEntry(histo4,"gluon-gluon fusion");
	legend->Draw();
	
	canvas2->SaveAs("VJ7_zd1.pdf");*/
	
	
	/*if(path.Contains("qqZZ")){
		canvas1->SaveAs("VJ7_zd1_bg.pdf");
	}*/
	
	
	
}

void Analyzer::Drawing(){
	TCanvas *canvas1;
	canvas1=new TCanvas("canvas1", "canvas1", 1600, 900);
	canvas1->Divide(2,2);
	TGraph *ROC = new TGraph();
	
	
	//########## STAKIRANJE ########## 
	//######### VJEZBA 7 ZD 2 #######
	/*THStack *hstack= new THStack();
	hstack->Add(histogram_background);
	hstack->Add(histogram_signal);
	hstack->Draw("HIST");
	histogram_signal->SetFillColor(kRed);
	histogram_background->SetFillColor(kBlue);
	hstack->GetXaxis()->SetTitle("mass / GeV");
	hstack->GetYaxis()->SetTitle("Events/2 GeV");*/
	
	
	//######## VJEZBA 7 ZD 3 #########
	//NORMALIZACIJA HISTOGRAMA
	histogram_signal_discriminator->Scale(1/histogram_signal_discriminator->Integral());
	histogram_background_discriminator->Scale(1/histogram_background_discriminator->Integral());
	
	for(int i=0; i<1000; i++)
	{
		float x=1.-histogram_background_discriminator->Integral(1,i+1);
		float y=1.-histogram_signal_discriminator->Integral(1,i+1);
		if ( x > 0.001 && y > 0.001 && x < 1.0 && y < 1.0) ROC->SetPoint(int(i),x,y);
		
	}
	canvas1->cd(2);
	ROC->SetMinimum(0.95);
    ROC->SetMaximum(1.0);
	ROC->Draw("ap");
	ROC->GetXaxis()->SetLimits(0.00,0.05);
	ROC->GetXaxis()->SetTitle("Background efficiency");
	ROC->GetYaxis()->SetTitle("Signal efficiency");
	ROC->SetTitle("ROC curve");
	ROC->Draw("ap");
	canvas1->Update();
	

	canvas1->cd(1);
	histogram_signal_discriminator->Rebin(50);
	histogram_background_discriminator->Rebin(50);
	histogram_signal_discriminator->Draw("HISTO");
	histogram_background_discriminator->Draw("HISTO same");
	
	//uredivanje histograma
	histogram_signal_discriminator->SetLineColor(kRed);
	histogram_background_discriminator->SetLineColor(kBlue);
	histogram_signal_discriminator->GetXaxis()->SetTitle("D_{kin}");
	histogram_signal_discriminator->GetYaxis()->SetTitle("Events/0.1");
	
	
	gStyle->SetOptStat(0000);
	TLegend *legend = new TLegend(0.4,0.8,0.6,0.9);  //x1,y1,x2,y2 are the coordinates of the Legend
	//legend->SetHeader("226.475 reconstructed Higgs bosons", "C"); //C for centering
    legend->AddEntry(histogram_signal_discriminator,"Signal (fusion)");
	legend->AddEntry(histogram_background_discriminator, "Background");
	legend->Draw();
	
	
	canvas1->cd(3);
	histogram_2D_background->Draw("COLZ");
	histogram_2D_background->SetStats(0);
	histogram_2D_background->SetMinimum(-0.01);
	histogram_2D_background->SetTitle("m_{4l} vs D_{kin} for background");
	histogram_2D_background->GetXaxis()->SetTitle("m_{4l} [GeV]");
	histogram_2D_background->GetYaxis()->SetTitle("D_{kin}");
	
	canvas1->cd(4);
	histogram_2D_signal->Draw("COLZ");
	histogram_2D_signal->SetStats(0);
	histogram_2D_signal->SetMinimum(-0.01);
	histogram_2D_signal->SetTitle("m_{4l} vs D_{kin} for signal");
	histogram_2D_signal->GetXaxis()->SetTitle("m_{4l} [GeV]");
	histogram_2D_signal->GetYaxis()->SetTitle("D_{kin}");
	
	canvas1->SaveAs("VJ7_zd3_zd5.png");
}

