#ifndef INTEGRATEUR_EULER
#define INTEGRATEUR_EULER

#include "Integrateur.h"
#include <vector>

class Integrateur;

class IntegrateurEuler : public Integrateur {
	public:

        virtual ~IntegrateurEuler() {}

	// méthode d'intégration //
	
	virtual void evolue(Masse*, double const&, std::vector<Masse*> contraintes = std::vector<Masse*>({})) override ;
	virtual std::string mon_nom() const override {return "Integrateur de Euler";}
	virtual double mon_dt() const {return 1.0;}
};

#endif //INTEGRATEUR_EULER	
