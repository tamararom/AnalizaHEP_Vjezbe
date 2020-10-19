#include "ElementaryParticle.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

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
	//cout << "Px, Py and Pz components are: " << px << py << pz << endl;
	cout << "Transversal momentum of the particle: " << pt << endl;
}

double ElementaryParticle::set_fourvector_momentum(double p_x, double p_y, double p_z, double m){
		double E_;
		px=p_x;
		py=p_y;
		pz=p_z;
		massOfParticle=m;
		E_=sqrt(px*px+py*py+pz*pz+m*m);
		E=E_;
}

double ElementaryParticle::transversal_momentum(double p_x, double p_y){
	double p_t;
	px=p_x;
	py=p_y;
	p_t=sqrt(p_x*p_x+p_y*p_y);
	pt=p_t;
}

void ElementaryParticle::bosonDecay(int i, ElementaryParticle *decayParticle_1, ElementaryParticle *decayParticle_2){
	double probability;
	if(boson==0){
		cout << "Boson decay is not possible, particle is not a boson!" << endl;
	}
	else{
		probability=rand()%100;
		if(probability<=21.4){ //W bosons
			//cout << "W boson decay" << endl;
			
			//names and masses
			decayParticle_1->nameOfParticle="W boson     ";
			decayParticle_2->nameOfParticle="W boson     ";
			decayParticle_1->massOfParticle=80.38;
			decayParticle_2->massOfParticle=80.38;
			
			//setting fourvector momenta randomly for decayParticle_1
			decayParticle_1->px=(rand()%100)*1.0/100*px; //ide jos /100 jer zelim u decimalnom zapisu postotak, a ne 7%
			decayParticle_1->py=(rand()%100)*1.0/100*py;
			decayParticle_1->pz=(rand()%100)*1.0/100*pz;
			decayParticle_1->set_fourvector_momentum(decayParticle_1->px,decayParticle_1->py,decayParticle_1->pz,decayParticle_1->massOfParticle);
			
			//setting fourvector momenta randomly for decayParticle_2
			decayParticle_2->px=px-decayParticle_1->px;
			decayParticle_2->py=py-decayParticle_1->py;
			decayParticle_2->pz=pz-decayParticle_1->pz;
			decayParticle_2->set_fourvector_momentum(decayParticle_2->px,decayParticle_2->py,decayParticle_2->pz,decayParticle_2->massOfParticle);
		}
		else if(probability>21.4 && probability<=27.8){ //tau leptons
			//cout << "Tau leptons decay" << endl;
			
			//names and masses
			decayParticle_1->nameOfParticle="Tau lepton  ";
			decayParticle_2->nameOfParticle="Tau lepton  ";
			decayParticle_1->massOfParticle=1.776;
			decayParticle_2->massOfParticle=1.776;
			
			//setting fourvector momenta randomly for decayParticle_1
			decayParticle_1->px=(rand()%100)*1.0/100*px; //ide jos /100 jer zelim u decimalnom zapisu postotak, a ne 7%
			decayParticle_1->py=(rand()%100)*1.0/100*py;
			decayParticle_1->pz=(rand()%100)*1.0/100*pz;
			decayParticle_1->set_fourvector_momentum(decayParticle_1->px,decayParticle_1->py,decayParticle_1->pz,decayParticle_1->massOfParticle);
			
			//setting fourvector momenta randomly for decayParticle_2
			decayParticle_2->px=px-decayParticle_1->px;
			decayParticle_2->py=py-decayParticle_1->py;
			decayParticle_2->pz=pz-decayParticle_1->pz;
			decayParticle_2->set_fourvector_momentum(decayParticle_2->px,decayParticle_2->py,decayParticle_2->pz,decayParticle_2->massOfParticle);
		}
		else if(probability>27.8 && probability<=30.4){ //Z bosons
			//cout << "Z bosons decay" << endl;
			
			//names and masses
			decayParticle_1->nameOfParticle="Z boson     ";
			decayParticle_2->nameOfParticle="Z boson     ";
			decayParticle_1->massOfParticle=91.19;
			decayParticle_2->massOfParticle=91.19;
			
			//setting fourvector momenta randomly for decayParticle_1
			decayParticle_1->px=(rand()%100)*1.0/100*px; //ide jos /100 jer zelim u decimalnom zapisu postotak, a ne 7%
			decayParticle_1->py=(rand()%100)*1.0/100*py;
			decayParticle_1->pz=(rand()%100)*1.0/100*pz;
			decayParticle_1->set_fourvector_momentum(decayParticle_1->px,decayParticle_1->py,decayParticle_1->pz,decayParticle_1->massOfParticle);
			
			//setting fourvector momenta randomly for decayParticle_2
			decayParticle_2->px=px-decayParticle_1->px;
			decayParticle_2->py=py-decayParticle_1->py;
			decayParticle_2->pz=pz-decayParticle_1->pz;
			decayParticle_2->set_fourvector_momentum(decayParticle_2->px,decayParticle_2->py,decayParticle_2->pz,decayParticle_2->massOfParticle);
		}
		else{ //b quarks
			//cout << "B quarks decay" << endl;
			
			//names and masses
			decayParticle_1->nameOfParticle="b quark     ";
			decayParticle_2->nameOfParticle="anti b quark";
			decayParticle_1->massOfParticle=4.18;
			decayParticle_2->massOfParticle=4.18;
			
			//setting fourvector momenta randomly for decayParticle_1
			decayParticle_1->px=(rand()%100)*1.0/100*px; //ide jos /100 jer zelim u decimalnom zapisu postotak, a ne 7%
			decayParticle_1->py=(rand()%100)*1.0/100*py;
			decayParticle_1->pz=(rand()%100)*1.0/100*pz;
			decayParticle_1->set_fourvector_momentum(decayParticle_1->px,decayParticle_1->py,decayParticle_1->pz,decayParticle_1->massOfParticle);
			
			//setting fourvector momenta randomly for decayParticle_2
			decayParticle_2->px=px-decayParticle_1->px;
			decayParticle_2->py=py-decayParticle_1->py;
			decayParticle_2->pz=pz-decayParticle_1->pz;
			decayParticle_2->set_fourvector_momentum(decayParticle_2->px,decayParticle_2->py,decayParticle_2->pz,decayParticle_2->massOfParticle);
		}
		//cout << i << decayParticle_1->nameOfParticle << "\t" << decayParticle_1->px << "\t" << decayParticle_1->py << "\t" << decayParticle_1->pz << "\t\n" << decayParticle_1->E << endl;
		//cout << i << decayParticle_2->nameOfParticle << "\t" << decayParticle_2->px << "\t" << decayParticle_2->py << "\t" << decayParticle_2->pz << "\t\n" << decayParticle_2->E << endl;
		ofstream file;
		file.open("Analysis.txt", ios_base::app); //app=append da dodam iduce podatke u petlji
		file << i << "\t" << decayParticle_1->nameOfParticle << "\t" << decayParticle_1->px << "\t" << decayParticle_1->py << "\t" << decayParticle_1->pz << "\t" << decayParticle_1->E << endl;
		file << i << "\t" << decayParticle_2->nameOfParticle << "\t" << decayParticle_2->px << "\t" << decayParticle_2->py << "\t" << decayParticle_2->pz << "\t" << decayParticle_2->E << endl;
		file.close();
	}
}

