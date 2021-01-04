#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include<THStack.h>
//dodano
#include <TH1F.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <TGraph.h>
#include <TH2F.h>
#include <TGraphPainter.h>
#include<TGraphErrors.h>

using namespace std;

class Analyzer{
	public:
	
	Analyzer();
	double Fact(int N);
	double binomial(int r, int N, float p);
	double sum_bin_up(int m1, int N1);
	double sum_bin_low(int m2, int N2);
	void CP_10(int N3);
	void draw_CP_belt(int N_);
	
	
};