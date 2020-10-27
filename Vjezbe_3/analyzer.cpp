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
	char filename[]="Analysis.txt";
		remove(filename); //prije unosenja podataka u datoteke, brisemo prethodne
	
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
	
	
	//ZD3.d)
	/*ElementaryParticle *Higgs;
	Higgs=new ElementaryParticle("Higgs boson",125,1);
	Higgs->set_fourvector_momentum(100,200,300,125);
	ElementaryParticle *decayParticle_1, *decayParticle_2;
	decayParticle_1= new ElementaryParticle();
	decayParticle_2= new ElementaryParticle();
	Higgs->bosonDecay(decayParticle_1,decayParticle_2);*/
	
	
	ElementaryParticle *Higgs;
	ElementaryParticle *decayParticle_1, *decayParticle_2;
	decayParticle_1= new ElementaryParticle();
	decayParticle_2= new ElementaryParticle();
	for(i=1;i<=10000;i++){
		//setting components of momenta to random values
		p_x=-100+(100-(-100))*(rand()%1000)/1000;
		p_y=-100+(100-(-100))*(rand()%1000)/1000;
		p_z=-100+(100-(-100))*(rand()%1000)/1000;
		
		Higgs=new ElementaryParticle("Higgs boson",125,1);
		
		Higgs->set_fourvector_momentum(p_x, p_y, p_z, 125);
		Higgs->transversal_momentum(p_x,p_y);
		Higgs->bosonDecay(i,decayParticle_1,decayParticle_2);
		delete Higgs;
	}
	
	delete decayParticle_1;
	delete decayParticle_2;
	return 0;
}