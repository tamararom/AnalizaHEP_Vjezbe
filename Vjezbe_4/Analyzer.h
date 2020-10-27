#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>

using namespace std;


//ako definiramo klasu u nekom fileu onda se klasa i file moraju zvat isto
class Analyzer {
	
	public:
	/*int iteration;
	string particle1;
	string particle2;
	double px1,py1,pz1,E1,
	double px2,py2,pz2,E2;*/
	
	
	//empty constructor
	Analyzer();
	
	//read function
	void data();
	
	void ConvertTxtToRootFile();
	
	
};