#include "Analyzer.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;
int main(){
	Analyzer *analysis;
	
	analysis=new Analyzer();
	
	//analysis->Loop();
	
	analysis->PlotHistogram();
	//analysis->PlotHistogram("/home/public/data/Lifetime/Lifetime.root");
	//->PlotHistogram("/home/public/data/qqZZ/ZZ4lAnalysis.root");
	//analysis->Drawing();
	//analysis->Fit();
	//analysis->FitMaxLike();
	
	
	
	//analysis->Bins();
	
	
	return 0;
}