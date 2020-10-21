#include "Analyzer.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
using namespace std;

int main (){
	Analyzer *analysis;
	
	analysis=new Analyzer();
	analysis->data();
		
	return 0;
}