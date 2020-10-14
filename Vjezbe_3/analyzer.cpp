#include "ElementaryParticle.h"

int main (){
	/*ElementaryParticle *Z;
	Z=new ElementaryParticle("Z boson",92,1);
	Z->set_fourvector_momentum(1,2,3,92);
	Z->printInfo();
	Z->bosonDecay(1);*/
	
	ElementaryParticle *Higgs;
	Higgs=new ElementaryParticle("Higgs boson",125,1);
	Higgs->set_fourvector_momentum(1,2,3,125);
	Higgs->transversal_momentum(1,2);
	Higgs->printInfo();
	Higgs->bosonDecay(1);
	
	ElementaryParticle *top;
	top=new ElementaryParticle("top quark",173,0);
	top->set_fourvector_momentum(1,2,3,173);
	top->transversal_momentum(1,2);
	top->printInfo();
	top->bosonDecay(0);
	
	return 0;
}