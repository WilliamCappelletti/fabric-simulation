#include "Contraintes.h"
#include <cmath>

using namespace std;

Contrainte::Contrainte(Vecteur3D O, Vecteur3D R, Vecteur3D v, double m, double cf, SupportADessin* support)
:Masse(m, O, v, cf, true, support), R(R)
{}

bool Contrainte::est_vincole(Masse* m) {
	if(!m->est_contrainte()) {
		if((m->get_position() - position).norme() <= R.norme()) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if((m->get_position() - position).norme() <= R.norme() + (m->get_rayon()).norme()) {
			return true;
		}
		else {
			return false;
		}
	}
}

Crochet::Crochet(Vecteur3D O, Vecteur3D R, Vecteur3D v)
:Contrainte(O, R, v)
{}

void Crochet::appliquer(Tissu* tissu, double dt) {
	vector<Masse*> cibles = tissu->check_contrainte(this);
	for(auto & m : cibles) {
		m->ajoute_force(-(m->get_force_subie()));
		m->set_vit(v);
	}
}

Impulsion::Impulsion(Vecteur3D O, Vecteur3D R, double t1, double t2, Vecteur3D F, std::vector<Tissu*> cibles)
:Contrainte(O, R), F(F)
{
	if(t1 <= t2) {
		t_start = t1;
		t_end = t2;
	}
	else {
		t_start = t2;
		t_end = t1;
	}
	
	for(auto tissu : cibles) {
		vector<Masse*> tmp = tissu->check_contrainte(this);
		for(auto & m : tmp) {
			masses.push_back(m);
		}
	}
}

void Impulsion::appliquer(Tissu* tissu, double dt) {
	if((dt >= t_start) and (dt <= t_end)) {
		vector<Masse*> cibles = tissu->check_contrainte(this);
		for(auto & cible : cibles){
			for(auto m : masses) {
				if(cible ==  m) {
					cible->ajoute_force(F);
				}
			}
		}
	}
}

Impulsion_sinusoidale::Impulsion_sinusoidale(Vecteur3D O, Vecteur3D R, double t1, double t2, Vecteur3D F, 
										double pace, std::vector<Tissu*> cibles)
:Impulsion(O, R, t1, t2, F, cibles), F0(F), pace(pace)
{}


void Impulsion_sinusoidale::appliquer(Tissu* tissu, double dt) {
	F=F0*(sin(2*M_PI*pace*(dt - t_start)));
	Impulsion::appliquer(tissu, dt);
}

Objet::Objet(Vecteur3D O, Vecteur3D R, Vecteur3D v, double m, double cf)
:Contrainte(O, R, v, m, cf)
{}

Objet::~Objet() {}

void Objet::appliquer(Tissu* tissu, double dt) {
	vector<Masse*> cibles = tissu->check_contrainte(this);
	for(auto & m : cibles) {
		Vecteur3D P(position-m->get_position());
		Vecteur3D V(m->get_v());
		Vecteur3D F(m->get_force_subie());
		
		if((F*P) > 0.0) {
			double proj_F((F*P)/(P*P));
			F = -(P*proj_F);
		}
		else {
			F *= 0.0;
		}		
		
		if((V*P) > 0.0) {
			double proj_V((V*P)/(P*P));
			V-=(P*proj_V);
			
			double proj_v((v*P)/(P*P));
			V+=(P*proj_v);
		}
		
		if((force_subie*P) < 0.0) {
			double proj_force_subie((force_subie*P)/(P*P));
			F += (P*proj_force_subie);
		}
		
		m->ajoute_force(F);
		
		
		m->set_vit(V);
	}
}

Sphere::Sphere(Vecteur3D O, Vecteur3D R, Vecteur3D v)
:Objet(O, R, v)
{}

Corp::Corp(Vecteur3D O, Vecteur3D R, double m, double cf, Vecteur3D v)
:Objet(O, R, v, m, cf)
{}

void Corp::appliquer(Tissu* tissu, double dt) {
	vector<Masse*> cibles = tissu->check_contrainte(this);
	
	for(auto & m : cibles) {
		Vecteur3D P(position-m->get_position());
		
		Vecteur3D F(m->get_force_subie());
		
		if((F*P) > 0.0) {
			double proj_F((F*P)/(P*P));
			F = (P*proj_F);
		}
		else {
			F *= 0.0;
		}
		
		force_subie += F;
		
	}
	
	Objet::appliquer(tissu, dt);
}




