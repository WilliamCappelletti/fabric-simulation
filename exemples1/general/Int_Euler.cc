#include <iostream>
#include <vector>
#include "Int_Euler.h"
using namespace std;


// méthode d'intégration //

    void IntegrateurEuler::evolue(Masse* m, double const& dt, std::vector<Masse*> contraintes){
		m->set_vit(m->get_v() + m->acceleration()*dt);
		m->set_pos(m->get_position() + m->get_v()*dt);
	}
	

