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
	
	analysis->PlotHistogram();
	
	
	
	return 0;
}