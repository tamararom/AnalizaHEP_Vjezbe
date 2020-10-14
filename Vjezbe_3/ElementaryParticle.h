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
	//dodjeljivanje vrijednosti komponenti kolicine gibanja
	double set_fourvector_momentum (double p_x, double p_y, double p_z, double m);
	//racunanje tranzverzalne kolicine gibanja
	double transversal_momentum (double p_x, double p_y);
	//dodjeljivanje klasi
	void printInfo();
};