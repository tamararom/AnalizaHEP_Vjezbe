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

double Analyzer::Fact(int N){
	unsigned long int factorial=1;
	int i;
	
	
	if(N==0){
		factorial=1;
	}
	else{
		for(i=1;i<=N;i++){
			factorial*=i;
		}
	}

	//cout << "Factorial of " << N << "=" << factorial << endl;
	
	return factorial;
}

double Analyzer::binomial(int r, int N, float p){
	double razlomak;
	double umnozak;
	double binom;
	
	razlomak=Fact(N)/(Fact(r)*Fact(N-r));
	umnozak=pow(p,r)*pow(1-p,N-r);
	
	binom=razlomak*umnozak;
	//cout <<"Binomial is:" << binom << endl;
	
	return binom;
}

double Analyzer::sum_bin_up(int m, int N1, double CL){ //upper limit
	double sum1=0.,sum=0.;
	int j, r1;
	double p_plus;
	
	p_plus=1.;
	
	
	while(sum<((1.-CL)/2.)){
		//cout << "Ulaz u petlju " << endl;
		for(r1=m+1;r1<=N1;r1++){
			sum1=sum1+binomial(r1,N1,p_plus);
			//r1=r1+1;
			//cout << binomial (r1,N1,p1) << endl;
			//r1=2->2->sum, 3->3->sum,4->4->sum
		}
		//cout << "sum: " << sum << endl;
		sum=1.-sum1;
		p_plus=p_plus-0.001;
		//cout << "p: " << p_plus << endl;
		sum1=0.;
	}
	//while(2*(1-sum)<=(1-CL));
	
	//cout << "prob up: " << p_plus << endl;
	return p_plus;
	
	//cout << "Sum = " << sum << endl;
	//return sum;
}


double Analyzer::sum_bin_low(int m2, int N2, double CL){
	int r2;
	double sum2=500.,sum3=0.;
	double p_minus=1.;
	
	if(m2==0){
		return 0;
		//cout << "prob low: " << 0 << endl;
	}
	else{
		while(sum2>((1-CL)/2.)){
			for(r2=0;r2<=m2-1;r2++){
			sum3=sum3+binomial(r2,N2,p_minus);
			}
			sum2=1.-sum3;
			p_minus=p_minus-0.001;
			sum3=0.;
		}
		return p_minus;
		//cout << "prob low: " << p_minus << endl;
	}
	//cout << "prob low: " << p_minus << endl;
}

void Analyzer::CP_10(int N3, double CL){
	double p_upper,p_lower;
	int r;
	for(r=0;r<=N3;r++){
		p_upper=sum_bin_up(r,N3,CL);
		p_lower=sum_bin_low(r,N3,CL);
		cout << "Limits for r="<<r<<" successful outcomes out of 10 events is ["<<p_lower<<","<<p_upper<<"]"<<endl;
	}
}

void Analyzer::draw_CP_belt(int N_,double CL){
	TH1F *upper_h, *lower_h;
	upper_h=new TH1F("upper","upper",N_,0,N_);
	lower_h=new TH1F("lower","lower",N_,0,N_);
	
	int r;
	double p_upper,p_lower;
	for(r=0;r<=N_;r++){
		p_upper=sum_bin_up(r,N_,CL);
		p_lower=sum_bin_low(r,N_,CL);
		//cout << "Limits for r="<<r<<" successful outcomes out of 10 events is ["<<p_lower<<","<<p_upper<<"]"<<endl;
		upper_h->SetBinContent(r,p_upper);
		lower_h->SetBinContent(r,p_lower);
	}
	
	TCanvas *canvas;
	canvas=new TCanvas("CP","CP",1600,900);
	gStyle->SetOptStat(0000);
	
	upper_h->SetMaximum(1.1);
	lower_h->SetMaximum(1.1);
	upper_h->SetMinimum(-0.1);
	lower_h->SetMinimum(-0.1);
	upper_h->GetYaxis()->SetRangeUser(0.,1.1);
	lower_h->GetYaxis()->SetRangeUser(0.,1.1);
	upper_h->GetXaxis()->SetTitle("r / number of successes");
	upper_h->GetYaxis()->SetTitle("p / probability");
	upper_h->SetTitle("Clopper-Pearson confidence belt");
	
	TLine *l1,*l2,*l3;
	TLatex *t1,*t2,*t3;
	
	l1=new TLine(0,sum_bin_up(5,N_,CL),5,sum_bin_up(5,N_,CL));
	l2=new TLine(0,sum_bin_low(5,N_,CL),5,sum_bin_low(5,N_,CL));
	l3=new TLine(5,-0.01,5,sum_bin_up(5,N_,CL));
	t1=new TLatex(0.5*5,sum_bin_up(5,N_,CL)+0.03,"p_{+}");
	t2=new TLatex(0.5*5,sum_bin_low(5,N_,CL)-0.03,"p_{-}");
	t3=new TLatex(5-0.02,-0.1,"r");
	
	l1->SetLineColor(kRed);
	l2->SetLineColor(kRed);
	l3->SetLineColor(kRed);
	l1->SetLineStyle(kDashed);
	l2->SetLineStyle(kDashed);
	l3->SetLineStyle(kDashed);
	t1->SetTextColor(1);
	t2->SetTextColor(1);
	t3->SetTextColor(1);
	t1->SetTextSize(0.03);
	t2->SetTextSize(0.03);
	t3->SetTextSize(0.03);
	
	Int_t color = TColor::GetFreeColorIndex();
	TColor *colour;
	colour=new TColor(color,1.,1.,1.);
	upper_h->SetFillColor(kBlue);
	lower_h->SetFillColor(color);
	
	upper_h->Draw();
	lower_h->Draw("same");
	l1->Draw("same");
	l2->Draw("same");
	l3->Draw("same");
	t1->Draw("same");
	t2->Draw("same");
	t3->Draw("same");
	
	canvas->SaveAs("C-P_belt.pdf");
}

void Analyzer::dice(int N, double CL){
	//1 sigma = 0.6827
	//2 sigma = 0.9544
	srand(time(NULL));
	int i, ii;
	int counter, events=0;
	double p_upper,p_lower;
	
	for(i=0;i<1000;i++){//1000 experiments
		counter=0;
		for(ii=0;ii<N;ii++){//10 throws
			if((rand()%6+1)==6){
				counter++;
			}
		}
		p_upper=sum_bin_up(counter,N,CL);
		p_lower=sum_bin_low(counter,N,CL);
		//this is conf.int.for this CL, where is p_true?
		//p_true is 1./6 
		if(p_upper>=1./6 && p_lower<=1./6){
			events++;
		}
	}
	cout << "Number of experiments that contain p_true in 10 throws in confidence interval of " << CL << " is " << events << endl;
	
}

