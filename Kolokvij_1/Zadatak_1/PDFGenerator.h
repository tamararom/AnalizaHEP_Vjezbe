#include<iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include<THStack.h>
#include <TH1F.h>

using namespace std;

class PDFGenerator {

   public:

	PDFGenerator();
	void GenerateQuadraticPDF(int N);
};