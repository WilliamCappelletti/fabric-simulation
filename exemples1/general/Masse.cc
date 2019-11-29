#include <iostream>
#include "Masse.h"
#include "Ressort.h"
#include "Dessinable.h"

using namespace std;


// constructeurs:

Masse::Masse(double masse, Vecteur3D position0, Vecteur3D v0, double c, bool f, SupportADessin* support)
: Dessinable(support), m(masse), position(position0), v(v0), cf(c), est_mobile(f)
{
	if(masse < 0.0) {
		cerr << "Une masse ne peut pas etre négative! " << endl;
		throw string("Masse négative");
	}
	Vecteur3D temp(0.0, 0.0, -g()*m);
	force_subie = temp;
}

// constructeur de copie:
/*
Masse::Masse(Masse const& copie)
:m(copie.get_m()), position(copie.get_position()), v(copie.get_v()), cf(copie.get_cf())
{}
*/

// destructeur:

Masse::~Masse() {}

// accesseurs:

double Masse::get_m() const {
	return m;
}

Vecteur3D Masse::get_v() const {
	return v;
}

Vecteur3D Masse::get_position() const{
	return position;
}

Vecteur3D Masse::get_force_subie() const {
	return force_subie;
}

double Masse::get_cf() const {
	return cf;
}

size_t Masse::nbr_ressorts() const {
	return ressorts.size();
}

void Masse::cout_ressorts() const {
	for(auto r : ressorts) {
		cout << r << endl;
	}
}

// methodes:

void Masse::ajoute_force(Vecteur3D const& df) {
	force_subie += df;
}

Vecteur3D Masse::acceleration() {
	if(m!=0) {
		return force_subie/m;
	}
	else { return Vecteur3D(0.0, 0.0, 0.0); }
}

void Masse::mise_a_jour_forces() {
	Vecteur3D P(0.0, 0.0, -m*g());
	
	force_subie = P - v*cf;
	
	if (ressorts.size() > 0) {
		for(auto r : ressorts) {
			ajoute_force(r->force_rappel(this));
		}
	}
	
	est_fixe();
}

void Masse::ajoute_ressort(Ressort* r) {
	ressorts.push_back(r);
}

void Masse::enleve_ressort(Ressort* a){
	for(auto& r : ressorts){
		if(r==a){
			r = ressorts.back();
			ressorts.pop_back();
		}
	}
}

bool Masse::check_ressorts() const{
	for(auto r : ressorts) {
		if (r->get_m_depart() != this) {
			if (r->get_m_arrivee() != this) { 
				cerr << "Le ressort " << r << " de la masse " << this << " n'est pas attaché à elle!" << endl;
				return false; }
		}
	}
	return true;
}

bool Masse::check_masses(Ressort* ptr) const{
	for (auto r : ressorts) {
		if (r==ptr) { return true;}
	}
	return false;
}

bool Masse::check_connection(Masse* ptr) const{
	for(auto r : ressorts) {
		if (r->get_m_depart() == ptr) { return true; }
		if (r->get_m_arrivee() == ptr) { return true; }
		}
		
	return false;
}

void Masse::est_fixe() {
	Vecteur3D z;
	if(!est_mobile) {
		force_subie = z;
		v = z;
	}
}

void Masse::force_normale() {
	ajoute_force(Vecteur3D(0.0, 0.0, g()*(get_m())));
}	  
	  

// manipulateurs
	
	void Masse::set_pos(Vecteur3D const& p){
		position=p;
	}
	void Masse::set_vit(Vecteur3D const& vit ){
		v=vit;
	}
	void Masse::set_masse(double const& masse){
		m=masse;
	}
	void Masse::set_cf(double const& co){
		cf=co;
	}
	
	void Masse::fixe(){
		est_mobile = false;
	}

std::ostream& operator<<(std::ostream& cout, Masse const& masse) {
	cout << "Masse " << &masse << " :" << endl;
	cout << masse.get_m() << " # masse" << endl;
	cout << masse.get_cf() << " # lambda" << endl;
	cout << masse.get_position() << " # position" << endl;
	cout << masse.get_v() << " # vitesse" << endl;
	cout << masse.get_force_subie() << " # force" << endl;
	cout << masse.nbr_ressorts() << " ressorts" << endl;
	if(masse.nbr_ressorts()>0){
		masse.cout_ressorts();
	}
	return cout;
}

// ajout d'un moment //

Vecteur3D Masse::force_totale() {
	Vecteur3D F(force_subie);
	Vecteur3D P(0.0, 0.0, -m*9.81);
	
	F = P - v*cf;
	
	if (ressorts.size() > 0) {
		for(auto r : ressorts) {
			F+=(r->force_rappel(this));
		}
	}
	
	Vecteur3D z;
	if(!est_mobile) {
		F = z;
		v = z;
	}
	
	return F;
}




