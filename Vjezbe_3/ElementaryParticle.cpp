#include "ElementaryParticle.h"
#include <math.h>

ElementaryParticle::ElementaryParticle(string x, double m, int b){
		nameOfParticle=x;
		massOfParticle=m;
		boson=b;
}

//"override" konstruktor
ElementaryParticle::ElementaryParticle(){
		nameOfParticle="";
		massOfParticle=0;
		boson=0;
}

void ElementaryParticle::printInfo(){
	cout << "Name of the particle: " << nameOfParticle << endl; //endl kao end line
	cout << "Mass of the particle: " << massOfParticle << endl; 
	cout << "Is it a boson (yes=1, no=0): " << boson << endl;
	cout << "Energy of the particle: " << E << endl;
	cout << "Transversal momentum of the particle: " << pt << endl;
}

double ElementaryParticle::set_fourvector_momentum(double p_x, double p_y, double p_z, double m){
		double E_;
		px=p_x;
		py=p_y;
		pz=p_z;
		massOfParticle=m;
		E_=sqrt(pow(px*px+py*py+pz*pz,2)+m*m);
		E=E_;
}

double ElementaryParticle::transversal_momentum(double p_x, double p_y){
	double p_t;
	px=p_x;
	py=p_y;
	p_t=sqrt(p_x*p_x+p_y*p_y);
	pt=p_t;
}

void ElementaryParticle::bosonDecay(ElementaryParticle *p1, ElementaryParticle *p2){
	if(boson==0)
		cout << "Boson decay is not possible, particle is not a boson!" << endl;
	
}
