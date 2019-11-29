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
	
	std::vector<Tissu> get_tissus() const;          // Retourne la liste des tissus présents dans le système
	                                                // méthode dérivée d'une première version et obsolète        
	
	void cout_tissus() const;                       // Affiche les tissus du système
	
	void evolue(double const&);                     // Méthode d'évolution du système
	
	void dessine_systeme() const;                   // Méthodes auxiliaires pour l'affichage graphique
	void augmente_compteur_graphique();
	
	void augmente_compteur_numerique();             // Méthodes auxiliaires pour le calcul numérique
	unsigned int get_CN() const;
	size_t integrateur() const { return integrateurs.size(); }
	size_t contrainte() const { return contraintes.size(); }
	
    virtual void dessine() override { support->dessine(*this); }
    
    std::string nom_integrateur() const {return integrateurs[compteur_numerique]->mon_nom();}  // toujours pour le calcul 
    double coefficient() const {return integrateurs[compteur_numerique]->mon_dt();}            // et pour la graphique
	
	void operator+=(Masse*);
	
	private: 
	
	std::vector<Tissu*> tissus;
    std::vector<Integrateur*> integrateurs;
    std::vector<Masse*> contraintes;
    unsigned int compteur_graphique;
    unsigned int compteur_numerique;
};

#endif //SYSTEM
