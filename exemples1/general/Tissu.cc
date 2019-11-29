#include <iostream>
#include <cmath>
#include "Ressort.h"
#include "Tissu.h"
#include "Contraintes.h"
#include "Systeme.h"

using namespace std;

Tissu::Tissu(vector<Masse>& liste_init, vector <Dependances> const& couples, double ke, double lz, SupportADessin* support)
: Dessinable(support)
{		
	for(unsigned short int i(0); i < liste_init.size(); ++i) {
		masses.push_back(&(liste_init[i]));
		liste_init[i].Dessinable::set_support(support);
	}
	for(auto & couple : couples) {
		this->connecte(couple[0], couple[1], ke, lz);
	}
	connecte_masses();
	for(auto & masse : masses) {
		masse->mise_a_jour_forces();
	}
	
	if(not check()) {
		cerr << "Condition des tissus non verifiée" << endl;
		throw string("Condition des tissu non verifiée");
	}
	
}

Tissu::Tissu(Masse* masse, SupportADessin* support)
:Dessinable(support)
{
	if(masse != nullptr) {
		masses.push_back(masse);
	}
	
	if(not check()) {
		cerr << "Condition des tissus non verifiée" << endl;
		throw string("Condition des tissu non verifiée");
	}
}
		

Tissu::Tissu(SupportADessin* support)
: Dessinable(support)
{}

Tissu::~Tissu() {}

void Tissu::connecte(size_t m1_index, size_t m2_index, double ke, double lz) {		
	ressorts.push_back(Ressort(masses[m1_index], masses[m2_index], ke, lz, true));
}

void Tissu::connecte_masses() {
	for(auto & ressort : ressorts) {
		ressort.update_masses();
	}
}

bool Tissu::check() {
	if(masses.size() > 1 and masses.size() != 0) {
		for(auto & masse : masses) {
			if (masse->nbr_ressorts() == 0) { 
				cerr << "La masse " << masse << " n'a pas de ressorts!" << endl;
				return false;
			}
			else {
				if (not masse->check_ressorts()) { return false; }
			}
		}
		for(auto & ressort : ressorts) {
			if (ressort.get_m_depart() == ressort.get_m_arrivee()) { 
				cerr << "Le ressort " << &ressort << "est attache a la meme masse!" << endl;
				return false; }
			else {
				if (not ressort.check_masses()) { return false; }
			}
		}
	}
	else if(masses.size() == 0) {
		cerr << "Le tissu n'as pas de masses!" << endl;
		return false;
	}
	return true;
}

void Tissu::affiche_ressorts() const {
	for(auto & r : ressorts) {
		cout << r << endl;
	}
}

void Tissu::affiche_masses() const {
	for(auto & m : masses) {
		cout << *m << endl;
	}
}
void Tissu::mise_a_jour_forces() {
	for (auto & m:masses){
		m->mise_a_jour_forces();
	}
}

void Tissu::evolue(Integrateur* integra, double const& dt, std::vector<Masse*> contraintes) {
	for (auto & m:masses){
		integra->evolue(m, dt, contraintes);
    }
   	Tissu::dessine();
}

void Tissu::dessine_tissu() const {
	 for(auto & m : masses){
		 m->Dessinable::set_support(support);
		 m->dessine(); 
	 }
	 for(auto r : ressorts){
		 r.Dessinable::set_support(support);
		 r.dessine();
	 }
}

void Tissu::dessine_tissu_masses() const {
	 for(auto & m : masses){
		 m->Dessinable::set_support(support);
		 m->dessine(); 
	 }
}

void Tissu::dessine_tissu_ressorts() const {
	 for(auto r : ressorts){
		 r.Dessinable::set_support(support);
		 r.dessine();
	 }
}

vector<Masse*> Tissu::check_contrainte(Contrainte* c) const {
	vector<Masse*> sortie;
	for(auto & masse : masses) {
		if (c->est_vincole(masse)) {
			sortie.push_back(masse);
		}
	}
	return sortie;
}

void Tissu::couper(Vecteur3D centre, double R) {
	vector<size_t> a_couper;
	vector<Masse*> cibles;
	
	for (size_t i(0); i < masses.size(); ++i) {
		if((masses[i]->get_position() - centre).norme() <= R) {
			a_couper.push_back(i);
			cibles.push_back(masses[i]);
		}
	}
	
	
	for (size_t i(masses.size()); i > 0; --i) {
		for(auto cible : a_couper) {
			if(i-1 == cible) {
				masses[i-1] = masses.back();
				masses.pop_back();
			}
		}
		
	}
	
	
	
	a_couper.clear();
	
	for(size_t i(0); i < ressorts.size(); ++i) {
		for(auto & cible : cibles) {
			if(cible->check_masses(&ressorts[i])) {
				bool y_est(false);
				for(auto indice : a_couper) {
					if(i == indice) {
						y_est = true;
					}
				}
				
				if(!y_est) {
					a_couper.push_back(i);
				}
			}
		}
				
		
		ressorts[i].get_m_depart()->enleve_ressort(&ressorts[i]);
		ressorts[i].get_m_arrivee()->enleve_ressort(&ressorts[i]);
		
	}
	
	
	for (size_t i(ressorts.size()); i > 0; --i) {
		for(auto cible : a_couper) {
			if(i-1 == cible) {
				ressorts[i-1] = ressorts.back();
				ressorts.pop_back();
			}
		}
		
	}
	
	for(auto & cible : cibles) {
		delete cible;
	}
	
	connecte_masses();
}
		
				
		
		

std::ostream& operator<<(std::ostream& out, Tissu const& tissu){
	out << "--- MASSES ---" << endl;
	for (auto & m : tissu.masses) {
		out << *m << endl;
	}
	
	/*
	out << endl << "--- RESSORTS ---" << endl;
	for (auto & r : tissu.ressorts) {
		out << r << endl;
	}
	*/
	
	return out;
}
	
	
TissuChaine::TissuChaine(double masse, double cf, double k, double l0, vector<Vecteur3D> table_pos, SupportADessin* support)
:Tissu(support)
{
	for(auto & pos : table_pos) {
		masses.push_back(new Masse(masse, pos, Vecteur3D(0.0, 0.0, 0.0), cf, true, support));
	}
	for(size_t i(1); i < masses.size(); ++i) {
		connecte(i-1, i, k, l0);
	}
	connecte_masses();	
	
	if(not check()) {
		cerr << "Condition des tissus non verifiée" << endl;
		throw string("Condition des tissu non verifiée");
	}
}

TissuChaine::~TissuChaine() {
	while(masses.size() > 0) {
		delete masses.back();
		masses.pop_back();
	}
}

TissuRectangle::TissuRectangle(double masse, Vecteur3D l, Vecteur3D L, Vecteur3D origine,
							double cf, double densite, double k, double l0, SupportADessin* support)
:Tissu(support)
{
	double proj_l((l*L)/(L*L));
	
	 if(L*proj_l != l) {		//on vérifie non colinéaires
		 
		// l -= L*proj_l;
		 
		 X = (L.norme()*densite);
		 Y = (l.norme()*densite);
		 
		 L *= 1.0/X;
		 l *= 1.0/Y;
		 
		 ++X; //pour ajouter la masse à l'extrémité
		 ++Y;
		 
		for(int y(0); y < Y; ++y) {
			for(int x(0); x < X; ++x) {
				masses.push_back(new Masse(masse, (origine + L*x + l*y), Vecteur3D(0.0, 0.0, 0.0), cf, true, support));
			}
		}
		
		//cout << masses.size() << endl;
		
		for(int y(0); y < Y; ++y) {
			for(int x(0); x < X-1; ++x) {
				connecte(x+y*(X), x+1+y*(X), k, l0);
				// cout << x+y*(X) << "<->" << x+1+y*(X) << endl;
			}
		}
		
		cout << endl;
		
		for(int y(0); y < Y-1; ++y) {
			for(int x(0); x < X; ++x) {
				connecte(x+y*(X), x+(y+1)*(X), k, l0);
				// cout << x+y*(X) << "<->" << x+(y+1)*(X) << endl;
			}
		}
		
		connecte_masses();
	}			 
	
	if(not check()) {
		cerr << "Condition des tissus non verifiée" << endl;
		throw string("Condition des tissu non verifiée");
	} 
}

TissuRectangle::~TissuRectangle() {
	while(masses.size() > 0) {
		delete masses.back();
		masses.pop_back();
	}
}

void TissuRectangle::accroche(unsigned short int i) {
	if(i <= 3) {
		if( i == 0) {						//coté -l
			for(int k(0); k < X; ++k) {
				masses[k]->fixe();
			}
		}
		if( i == 1) {						//coté +L
			for(int k(0); k < Y; ++k) {
				masses[X-1+k*X]->fixe();
			}
		}
		if( i == 2) {						//coté +l
			for(int k(0); k < X; ++k) {
				masses[k+(Y-1)*X]->fixe();
			}
		}
		if ( i == 3) {						//coté -L
			for(int k(0); k < Y; ++k) {
				masses[k*X]->fixe();
			}
		}
	}
}

TissuDisque::TissuDisque(double m, Vecteur3D centre, Vecteur3D radius, double pas, double cf, double k,
							int alpha, SupportADessin* support)
:Tissu(support)
{
	Vecteur3D v0(0.0, 0.0, 0.0);
	
	masses.push_back(new Masse(m, centre, v0, cf, true, support));
	
	C_masses = 360/alpha;
	phi = 360/(C_masses);
	R = radius.norme();
	R_masses = R/pas +1;
	
	Vecteur3D r(1.0, 0.0, 0.0);
	
	double proj_radius((r*radius)/(radius*radius));
	
	if(radius*proj_radius == r) {
		r += Vecteur3D(-1.0, 1.0, 0.0);
	}
	else {
		r -= radius*proj_radius;
	}
	
	r=r.normalise();
	radius=radius.normalise();
	
	//on cree les masses
	
	for(int i(0); i < C_masses; ++i) {
		double d((radius*r)*(1-cos(M_PI*phi/180*i)));
		Vecteur3D u(r*cos(M_PI*phi/180*i) + radius*(d) +(radius^r)*sin(M_PI*phi/180*i));		//Formule de rodriguez
		
		for(int j(1); j < R_masses; ++j) {
			masses.push_back(new Masse(m, (centre + u*(j*pas)), v0, cf, true, support));
		}
	}
	//on connecte les radiums
	for(int i(0); i < C_masses; ++i) {
		connecte(0, i*(R_masses-1)+1, k, pas);
		for(int j(1); j < R_masses-1; ++j) {
			connecte(j+i*(R_masses-1), j+1+i*(R_masses-1), k, pas);
		}
	}
	
	//on connecte les circumferences
	for(int i(0); i < C_masses-1; ++i) {
		for(int j(1); j < R_masses; ++j) {
			connecte(j+(i)*(R_masses-1), j+(i+1)*(R_masses-1), k, (masses[j+(i)*(R_masses-1)]->get_position() - masses[j+(i+1)*(R_masses-1)]->get_position()).norme());
		}
	}
	//on ferme les circumferences
	for(int j(1); j < R_masses; ++j) {
		connecte(j, j+(R_masses-1)*(C_masses-1), k, (masses[j]->get_position() - masses[j+(R_masses-1)*(C_masses-1)]->get_position()).norme());
	}
	
	
	connecte_masses();
	
	if(not check()) {
		cerr << "Condition des tissus non verifiée" << endl;
		throw string("Condition des tissu non verifiée");
	}
}

TissuDisque::~TissuDisque() {
	while(masses.size() > 0) {
		delete masses.back();
		masses.pop_back();
	}
}

TissuCompose::TissuCompose(std::vector<Tissu*> composantes, double l, double ke, SupportADessin* support)
:Tissu(support), l(l), ke(ke), nbr_composantes(0)
{
	for(auto & tissu:composantes) {
		++nbr_composantes;
		*this+= tissu;
	}
	
	if(not check()) {
		cerr << "Condition des tissus non verifiée" << endl;
		throw string("Condition des tissu non verifiée");
	}
}


void TissuCompose::raccommode() {
	int nbr(0);
	for(size_t i(0); i < masses.size(); ++i) {
		for(size_t j(i+1); j < masses.size(); ++j) {
			if((masses[i]->get_position() - masses[j]->get_position()).norme() <= l) {
				if(not masses[i]->check_connection(masses[j])) {
					connecte(i, j, ke, l);
					++nbr;
				}
			}
		}
	}
	
	for(auto & r:ressorts) {
		r.get_m_depart()->enleve_ressort(&r);
		r.get_m_arrivee()->enleve_ressort(&r);
	}
	
	connecte_masses();
	
	if (nbr_composantes > 1 and nbr == 0) {
		cerr << "Deux tissu ne pouvaient pas etre attaches!" << endl;
		throw string("pas connexe");
	}
}

void TissuCompose::operator+=(Tissu* tissu) {
	for(auto & m:tissu->masses) {
			masses.push_back(m);
	}
	
	for(auto & r:tissu->ressorts) {
		r.get_m_depart()->enleve_ressort(&r);
		r.get_m_arrivee()->enleve_ressort(&r);
		ressorts.push_back(r);
	}
	
	connecte_masses();
	raccommode();
}


