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
	string nameParticle;
	double px,py,pz,E;
	
	if(outfile.is_open())
	{
		while(getline(outfile,line)){
			stringstream linestream(line);
			
			linestream >> numberOfEvents >> nameParticle >> px >> py >> pz >> E;
			cout << numberOfEvents << " " << nameParticle << " " << px << " " << py << " " << pz << " " << E << endl;
		}
	}
	
	
	outfile.close();
}