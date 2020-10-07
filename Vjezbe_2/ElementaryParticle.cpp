#include "ElementaryParticle.h"

ElementaryParticle::ElementaryParticle(string x, double m, int b){
		nameOfParticle=x;
		massOfParticle=m;
		boson=b;
}

	void ElementaryParticle::printInfo(){
	cout << "Name of the particle: " << nameOfParticle << endl; //endl kao end line
	cout << "Mass of the particle: " << massOfParticle << endl; 
	cout << "Is it a boson (yes=1, no=0): " << boson << endl;
}
	