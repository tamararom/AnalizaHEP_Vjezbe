// Program to illustrate the working of
// objects and class in C++ Programming

#include <iostream>
using namespace std;


// create a class
class ElementaryParticle {

   public:
    string nameOfParticle;
    double massOfParticle;
    int boson;

	//definicija konstruktora
	ElementaryParticle (string x, double m, int b){
		nameOfParticle=x;
		massOfParticle=m;
		boson=b;
	}

	void printInfo(){
	cout << "Name of the particle: " << nameOfParticle << endl; //endl kao end line
	cout << "Mass of the particle: " << massOfParticle << endl; 
	cout << "Is it a boson (yes=1, no=0): " << boson << endl;
}
	
};

int main() {
	// create object of ElementaryParticle class
    //ElementaryParticle Higgs;
	//ElementaryParticle top;
	
	//ovo mi je za preko pokazivaca
	/*ElementaryParticle *Zboz; //pokazivac na objekt
	ElementaryParticle Z;
	Zboz=&Z;*/
	
	string name="Z boson";
	double mass=92;
	int boson=1;
	/* ovo je za zadatak 6.C) 
	ElementaryParticle Z(name,mass,boson);
	Z.printInfo();*/
	
	ElementaryParticle *Z;
	Z=new ElementaryParticle(name,mass,boson);
	Z->printInfo();

    //Higgs
	//Higgs.nameOfParticle = "H";
	//Higgs.massOfParticle = 125;
	//Higgs.boson = 1;

	
	//quark
	//top.nameOfParticle = "t";
    //top.massOfParticle = 173;
    //top.boson = 0;
	
	
	/* //ovo mi je za preko pokazivaca (Zadatak 6. B))
	//Z bozon
	Zboz->nameOfParticle="Z bozon";
	Zboz->massOfParticle=92;
	Zboz->boson=1;*/
	
	//Higgs.printInfo();
	//top.printInfo();
	//Zboz->printInfo(); ovo mi je za preko pokazivaca
	
	

    return 0;
}