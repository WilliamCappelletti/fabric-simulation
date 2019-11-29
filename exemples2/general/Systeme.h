#ifndef SYSTEM
#define SYSTEM

#include <vector>
#include <string>
#include "Tissu.h"
#include "SupportADessin.h"
#include "Dessinable.h"
#include "Contraintes.h"


class Integrateur;

class Systeme : public Dessinable {
	public:
	
	// constructeur 
	
	Systeme(std::vector<Tissu*> &, std::vector<int> &, std::vector<Masse*> &, SupportADessin* = nullptr,
				int const& c = 0, int const& n=0);
	~Systeme();
	
	// méthodes //
	
	std::vector<Tissu> get_tissus() const;
	void cout_tissus() const;
	void evolue(double const&);
	void dessine_systeme() const;
	//void ressorts() const;
	void augmente_compteur_graphique();
	void augmente_compteur_numerique();
	unsigned int get_CN() const;
	size_t integrateur() const { return integrateurs.size(); }
	size_t contrainte() const { return contraintes.size(); }
    virtual void dessine() override { support->dessine(*this); }
    std::string nom_integrateur() const {return integrateurs[compteur_numerique]->mon_nom();}
    double coefficient() const {return integrateurs[compteur_numerique]->mon_dt();}
	
	void operator+=(Masse*);
	
	private: 
	
	std::vector<Tissu*> tissus;
    std::vector<Integrateur*> integrateurs;
    std::vector<Masse*> contraintes;
    unsigned int compteur_graphique;
    unsigned int compteur_numerique;
};

#endif //SYSTEM
