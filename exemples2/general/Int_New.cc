#include <iostream>
#include <vector>
#include <cmath>
#include "Int_New.h"
#include "Tissu.h"
using namespace std;


void IntegrateurNewmark::evolue(Masse* m, double const& dt, std::vector<Masse*> contraintes){
	
	// variables auxiliaires //
	
	Vecteur3D chi_prime;
	Vecteur3D chi;
	Vecteur3D xi;
	double epsilon = pow(10.0, -6.0);
	
	Tissu* t(new Tissu(m));
	
	// initialisation //
	
	Vecteur3D v1(m->get_v());
	Vecteur3D p1(m->get_position());
	chi_prime = m->acceleration();
	
	// boucle //
	
	do{
		xi = m->get_position();
		bool libre(true);
		for(auto & c : contraintes){
			if(c->est_vincole(m)) libre = false;
		}
		if(libre) m->mise_a_jour_forces();
		/*
		for(auto & c : contraintes){
			c->appliquer(t, dt);
		}*/
		chi = m->acceleration();
		m->set_vit(v1+(chi+chi_prime)*(0.5*dt));
		m->set_pos(p1+v1*dt+(chi_prime+chi*0.5)*((dt*dt)/3));
	}while((m->get_position() - xi).norme() >= epsilon);	
}
	
