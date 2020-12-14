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

using namespace std;

Analyzer::Analyzer(){
}

void Analyzer::Draw(){
	TCanvas* canvas;
	canvas= new TCanvas("canvas","canvas", 1600,900);
	canvas->Divide(2);
	gStyle->SetStatY(0.9);                
	// Set x-position (fraction of pad size)
	gStyle->SetStatX(0.5);
	// Set width of stat-box (fraction of pad size)
	gStyle->SetStatW(0.2);                
	gStyle->SetStatH(0.2); 	
	
	int N=5;
	double a[5]={9.8,21.2,34.5,39.9,48.5};
	double a_err[5]={1.0,1.9,3.1,3.9,5.1};
	double F[5]={1.,2.,3.,4.,5.}; 
	double F_err[5]={0.,0.,0.,0.,0.};
	double sigma_m;
	double min;
	double theta;
	double sigma_low, sigma_up;
	int i;
	double sum1=0.,sum2=0., theta_analy;


	// ## ZADATAK 1 ##
	TF1* fit;
	fit=new TF1("fit function", "1/[0]*x",0,6);
	fit->SetParameter(0,0.1);
	fit->SetParName(0,"mass");
	sigma_m = fit->GetParError(0);
	
	
	TGraphErrors *graph;
	graph=new TGraphErrors(N,F,a,F_err,a_err);
	graph->SetTitle("F-a graph with errors");
	graph->GetXaxis()->SetTitle("F [N]");
	graph->GetYaxis()->SetTitle("a [m/s^{2}]");
	graph->SetMarkerStyle(21);
	canvas->cd(1);
	graph->Draw("AP");
	
	graph->Fit(fit);
	
	TF1* chi_square;
	chi_square=new TF1("chi_square","(pow(([0]-[1]*x),2)/([2]*[2]))+(pow(([3]-[4]*x),2)/([5]*[5]))+(pow(([6]-[7]*x),2)/([8]*[8]))+(pow(([9]-[10]*x),2)/([11]*[11]))+(pow(([12]-[13]*x),2)/([14]*[14]))",9.7,10.9);
	chi_square->SetTitle("Chi-Square");
	
	chi_square->SetParameter(0,a[0]);
	chi_square->SetParameter(1,F[0]);
	chi_square->SetParameter(2,a_err[0]);
	chi_square->SetParameter(3,a[1]);
	chi_square->SetParameter(4,F[1]);
	chi_square->SetParameter(5,a_err[1]);
	chi_square->SetParameter(6,a[2]);
	chi_square->SetParameter(7,F[2]);
	chi_square->SetParameter(8,a_err[2]);
	chi_square->SetParameter(9,a[3]);
	chi_square->SetParameter(10,F[3]);
	chi_square->SetParameter(11,a_err[3]);
	chi_square->SetParameter(12,a[4]);
	chi_square->SetParameter(13,F[4]);
	chi_square->SetParameter(14,a_err[4]);
	
	theta=chi_square->GetMinimumX(8,11,1.E-10,100,false);
    min=chi_square->GetMinimum(8,11,1.E-10,100,false);
    sigma_low=theta-chi_square->GetX(min+1,8,11,1.E-10,100,false); 
    sigma_up=chi_square->GetX(min+1,8,11,1.E-10,100,false)-theta;
	
	
	
	canvas->cd(2);
	chi_square->GetXaxis()->SetTitle("#hat{#theta} [kg^{-1}]");
	chi_square->GetYaxis()->SetTitle("#chi^{2}");
	chi_square->Draw();
	
	cout << "Parameter theta by chi-square: " << chi_square->GetMinimumX() <<endl;
	cout << "Mass by chi-square: "<<1/(chi_square->GetMinimumX())<<endl;
	cout << "" << endl;
	cout << "chi_square theta sigma:\t\t\t\t" << theta << "\t\t- " << sigma_low << "\t+ " << sigma_up << endl;
	cout << "chi_square mass sigma:\t\t\t\t" << 1/(chi_square->GetMinimumX()) << "\t\t-+ " << sigma_up/(theta*theta) << endl;
	
	//analiticki
	for(i=0;i<5;i++){
		sum1=sum1+F[i]*a[i]/pow(a_err[i],2);
		sum2=sum2+pow(F[i]/a_err[i],2);
	}
	theta_analy=sum1/sum2;
	
	cout << " " << endl;
	cout << "Theta analytical:\t\t" << theta_analy << "\t+-" << 1/sqrt(sum2) << endl;
	//masa je izvedena velicina 
	cout << "Mass analytical:\t\t" << 1/theta_analy << "\t+-" << 1/(sqrt(sum2))/pow(theta_analy,2) << endl;
	
	
	TLine* line1;
	line1=new TLine(9.7,chi_square->Eval(theta)+1,10.9,chi_square->Eval(theta)+1);
	line1->SetLineStyle(kDashed);
	line1->Draw();
	
	TLine *line2;
    TLine *line3;
	TLine *line0;
	
	line2=new TLine(theta-sigma_low,2.05,theta-sigma_low,chi_square->Eval(theta)+1);
	line2->SetLineStyle(kDashed);
	line2->Draw();
	TLatex *t2;
	t2=new TLatex (theta-sigma_low-0.03,2.0,"#hat{#theta}-#sigma");
	t2->SetTextSize(0.025);
	t2->Draw();
	
	
	line3= new TLine(theta-sigma_up,2.05,theta-sigma_up,chi_square->Eval(theta)+1);
	line3->SetLineStyle(kDashed);
	line3->Draw();
	TLatex *t3;
	t3=new TLatex(theta-sigma_up-0.05,2.0,"#hat{#theta}+#sigma");
	t3->SetTextSize(0.025);
	t3->Draw();
	
	
	line0= new TLine(theta,2.05,theta,chi_square->Eval(theta)+0.009);
	line0->SetLineStyle(kDashed);
	line0->Draw();
	TLatex *t0;
	t0=new TLatex(theta-0.01,2.0,"#hat{#theta}");
	t0->SetTextSize(0.025);
	t0->Draw();
	
	
	gStyle->SetOptFit();
	canvas->SaveAs("VJ10_.png");
}