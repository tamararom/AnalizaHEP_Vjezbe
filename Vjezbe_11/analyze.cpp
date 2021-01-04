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
	
	//a->Fact(4);
	//a->binomial(12,30,0.3); //r,N,p idu u zagradi redom
	
	//a->sum_bin_up(1,4,0.6827);//r,N,p+/- idu u zagradi redom
	//a->sum_bin_low(1,4,0.6827);
	
	//a->CP_10(10,0.6827);
	
	//a->draw_CP_belt(10,0.6827);
	
	a->dice(10,0.9544);
	//1 sigma = 0.6827
	//2 sigma = 0.9544
	
	return 0;
}