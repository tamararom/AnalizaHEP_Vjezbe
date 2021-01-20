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
#include <TGraphPainter.h>
#include<TGraphErrors.h>

using namespace std;
int main(){
	Analyzer *a;
	
	a=new Analyzer();
	
	a->Loop();
	a->Statistic();
	a->pValue();
	

	
	return 0;
}