#include "ElementaryParticle.h"

int main (){
	/*ElementaryParticle *Z;
	Z=new ElementaryParticle("Z boson",92,1);
	Z->set_fourvector_momentum(1,2,3,92);
	Z->printInfo();*/
	
	ElementaryParticle *Higgs;
	Higgs=new ElementaryParticle("Higgs boson",125,1);
	Higgs->set_fourvector_momentum(1,2,3,125);
	Higgs->transversal_momentum(1,2);
	Higgs->printInfo();
	
	/*ElementaryParticle *top;
	top=new ElementaryParticle("top quark",173,0);
	top->set_fourvector_momentum(1,2,3,173);
	top->printInfo();*/
	
	return 0;
}