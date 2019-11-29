#ifndef INTEGRATEUR_RUNGE
#define INTEGRATEUR_RUNGE

#include "Integrateur.h"
#include "Vecteur3D.h"
#include <vector>

class IntegrateurRunge : public Integrateur {
	public:
	
	virtual ~IntegrateurRunge() {}
	
	// méthode d'intégration //
	
	virtual void evolue(Masse*, double const&, std::vector<Masse*> contraintes = std::vector<Masse*>({})) override ;
	virtual std::string mon_nom() const override {return "Integrateur de Runge-Kutta";}
	virtual double mon_dt() const {return 2.0;}
};

#endif //INTEGRATEUR_RUNGE		
