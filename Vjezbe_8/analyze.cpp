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


int main(){
	Analyzer *analysis;
	
	analysis=new Analyzer();
	
	//analysis->Loop();
	
	analysis->PlotHistogram("/home/public/data/ggH125/ZZ4lAnalysis.root");
	analysis->PlotHistogram("/home/public/data/qqZZ/ZZ4lAnalysis.root");
	//analysis->Drawing();
	
	analysis->Fit();
	analysis->FitMaxLike();
	
	
	return 0;
}