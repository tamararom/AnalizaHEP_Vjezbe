#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include<THStack.h>


//dodano
#include <TH1F.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector> //ovdje izmjenjeno iz " "
#include <iostream>
#include <TGraph.h>
#include <TH2F.h>
#include <TGraphPainter.h>
#include<TGraphErrors.h>

using namespace std;

class Analyzer{
	public:
	
	Analyzer();
	void Draw();
	
};