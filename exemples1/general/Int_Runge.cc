#include <vector>
#include <cmath>
#include "Int_Runge.h"
using namespace std;

void IntegrateurRunge::evolue(Masse* m, double const& dt, std::vector<Masse*> contraintes){
	
	bool libre(true);
	for(auto & c : contraintes){
		if(c->est_vincole(m)) libre = false;
	}
		
	
	Vecteur3D p0(m->get_position());
	Vecteur3D v0(m->get_v());
	
	Vecteur3D k1 = v0;
	Vecteur3D k1_prime = m->acceleration();
	
	Vecteur3D k2 = v0 + k1_prime*(dt/2.0);
	
	m->set_pos(p0+k1*(dt/2.0));
	m->set_vit(v0+k1_prime*(dt/2.0));
	
	//Vecteur3D k2_prime = m->force_totale()*(1.0/m->get_m());
	if(libre) m->mise_a_jour_forces();
	
	Vecteur3D k2_prime = m->acceleration();	
	
	Vecteur3D k3 = v0 + k2_prime*(dt/2.0);
	
	m->set_pos(p0+k2*(dt/2.0));
	m->set_vit(v0+k2_prime*(dt/2.0));
	
	//Vecteur3D k3_prime = m->force_totale()*(1.0/m->get_m());
	if(libre) m->mise_a_jour_forces();
	
	Vecteur3D k3_prime = m->acceleration();
	
	Vecteur3D k4 = v0 + k3_prime*dt;
	
	m->set_pos(p0+k3*dt);
	m->set_vit(v0+k3_prime*dt);
	
	//Vecteur3D k4_prime = m->force_totale()*(1.0/m->get_m());
	if(libre) m->mise_a_jour_forces();
	
	Vecteur3D k4_prime = m->acceleration();
	
	// pas d'intégration //
	
	m->set_pos(p0+(k1+k2*2.0+k3*2.0+k4)*(dt/6.0));
    m->set_vit(v0+(k1_prime+k2_prime*2.0+k3_prime*2.0+k4_prime)*(dt/6.0));
    
}
