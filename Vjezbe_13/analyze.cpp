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
	
	a->Comparison("France",164.7,7.1);
	a->Comparison("Italy",166.1,6.5);
	a->Comparison("Netherlands",170.3,7.5);
	
	return 0;
}