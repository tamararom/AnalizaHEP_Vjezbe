#include "Analyzer.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Analyzer::Analyzer(){ 
	/*iteration=0;
	particle1="";
	particle2="";
	px1=py1=pz1=E1=0;
	px2=py2=pz2=E2=0;*/
}

void Analyzer::data(){
	ifstream outfile;
	outfile.open("Analysis.txt");
	
	string line;
	int numberOfEvents;
	string nameParticle1, nameParticle2;
	double px1,py1,pz1,pt1,E1,px2,py2,pz2,pt2,E2;
	
	if(outfile.is_open())
	{
		while(getline(outfile,line)){
			stringstream linestream(line);
			
			linestream >> numberOfEvents >> nameParticle1 >> px1 >> py1 >> pz1 >> pt1 >> E1 >> nameParticle2 >> px2 >> py2 >> pz2 >> pt2 >> E2;
			//cout << numberOfEvents << " " << nameParticle << " " << px << " " << py << " " << pz << " " << E << endl;
		}
	}
	outfile.close();
}

void Analyzer::ConvertTxtToRootFile(){
	ifstream input_file;
	input_file.open("Analysis.txt");
	//converting txt input file to output root file
	TFile *root_file = root_file = TFile::Open("Analysis.root","RECREATE");
	//pointer to class object tree
	TTree *tree = new TTree("tree","Vjezbe_4");
	
	//creating branch variables (GRANE STABLA)
	Int_t           numberOfEvents;
	
	Char_t          nameParticle1;
	Double_t        px1;
	Double_t        py1;
	Double_t        pz1;
	Double_t		pt1;
	Double_t        E1;
	
	Char_t          nameParticle2;
	Double_t        px2;
	Double_t        py2;
	Double_t        pz2;
	Double_t		pt2;
	Double_t        E2;
	
	//adding branches to the tree
	tree->Branch("numberOfEvents",&numberOfEvents,"numberOfEvents/I");
	tree->Branch("nameParticle1",&nameParticle1,"nameParticle1/C");
	tree->Branch("px1",&px1,"px1/D");
	tree->Branch("py1",&py1,"py1/D");
	tree->Branch("pz1",&pz1,"pz1/D");
	tree->Branch("pt1",&pt1,"pt1/D");
	tree->Branch("E1" ,&E1, "E1/D");	
	tree->Branch("nameParticle2",&nameParticle2,"nameParticle2/C");
	tree->Branch("px2",&px2,"px2/D");
	tree->Branch("py2",&py2,"py2/D");
	tree->Branch("pz2",&pz2,"pz2/D");
	tree->Branch("pt2",&pt2,"pt2/D");
	tree->Branch("E2", &E2, "E2/D");
	
	string line; //just like the data function
	if(input_file.is_open())
	{
		while(getline(input_file,line)){
			stringstream linestream(line);
			
			linestream >> numberOfEvents >> nameParticle1 >> px1 >> py1 >> pz1 >> pt1 >> E1 >> nameParticle2 >> px2 >> py2 >> pz2 >> pt2 >> E2;
			cout << numberOfEvents << " " << nameParticle1 << " " << px1 << " " << py1 << " " << pz1 << " " << pt1 << " " << E1 << " " << nameParticle2 << " " << px2 << " " << py2 << " " << pz2 << " " << pt2 << " " << E2 <<endl;
			tree->Fill();
		}
	}
	tree->Print();
	tree->Write();
	input_file.close();
	delete root_file;
}