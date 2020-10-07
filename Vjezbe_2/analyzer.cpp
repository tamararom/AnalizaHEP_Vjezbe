#include "ElementaryParticle.h"

int main (){
	ElementaryParticle *Z;
	Z=new ElementaryParticle("Z boson",92,1);
	Z->printInfo();
	
	ElementaryParticle *Higgs;
	Higgs=new ElementaryParticle("Higgs boson",125,1);
	Higgs->printInfo();
	
	ElementaryParticle *top;
	top=new ElementaryParticle("top quark",173,0);
	top->printInfo();
	
	return 0;
}