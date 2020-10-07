#include<iostream>
using namespace std;

class ElementaryParticle {

   public:
    string nameOfParticle;
    double massOfParticle;
    int boson;

	//pozivanje konstruktora
	ElementaryParticle (string x, double m, int b);
	//dodjeljivanje klasi
	void printInfo();
};