#include "PDFGenerator.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

int main(){
	PDFGenerator *generator;
	generator=new PDFGenerator();
	
	int N;
	N=10000;
	generator->GenerateQuadraticPDF(N);
	
	
	return 0;
}
