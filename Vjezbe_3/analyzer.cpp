#include "ElementaryParticle.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

int main (){
	srand(time(NULL));
	int i;
	double p_x, p_y, p_z, E_;
	
	/*ElementaryParticle *Z;
	Z=new ElementaryParticle("Z boson",92,1);
	Z->set_fourvector_momentum(1,2,3,92);
	Z->printInfo();
	Z->bosonDecay(1);*/
	
	/*ElementaryParticle *Higgs;
	Higgs=new ElementaryParticle("Higgs boson",125,1);
	Higgs->set_fourvector_momentum(1,2,3,125);
	Higgs->transversal_momentum(1,2);
	Higgs->printInfo();
	//Higgs->bosonDecay(1); za zad2. A)*/
	
	/*ElementaryParticle *top;
	top=new ElementaryParticle("top quark",173,0);
	top->set_fourvector_momentum(1,2,3,173);
	top->transversal_momentum(1,2);
	top->printInfo();
	//top->bosonDecay(0); za zad2. A)*/
	
	ElementaryParticle *Higgs;
	Higgs=new ElementaryParticle("Higgs boson",125,1);
	Higgs->set_fourvector_momentum(100,200,300,125);
	
	
	ElementaryParticle *decayParticle_1, *decayParticle_2;
	decayParticle_1= new ElementaryParticle();
	decayParticle_2= new ElementaryParticle();
	Higgs->bosonDecay(decayParticle_1,decayParticle_2);
	
	/*for(i=1;i<=10000;i++){
		
		decayParticle_1= new ElementaryParticle();
		decayParticle_2= new ElementaryParticle();
		Higgs->bosonDecay(i, decayParticle_1,decayParticle_2);
	}*/
	
	return 0;
}