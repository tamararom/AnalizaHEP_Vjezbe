#include<iostream>
using namespace std;

class ElementaryParticle {

   public:
    string nameOfParticle;
    double massOfParticle;
    int boson;
	double px;
	double py;
	double pz;
	double E;
	double pt;
	
	
	//pozivanje konstruktora
	ElementaryParticle (string x, double m, int b);
	//override konstruktor
	ElementaryParticle();
	
	//dodjeljivanje vrijednosti komponenti kolicine gibanja
	double set_fourvector_momentum (double p_x, double p_y, double p_z, double m);
	//racunanje tranzverzalne kolicine gibanja
	double transversal_momentum (double p_x, double p_y);
	
	//bozon raspad
	void bosonDecay(ElementaryParticle *p1, ElementaryParticle *p2);
	//dodjeljivanje klasi
	void printInfo();
};