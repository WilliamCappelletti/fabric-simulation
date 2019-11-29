#ifndef INTEGRATEUR_NEWMARK
#define INTEGRATEUR_NEWMARK

#include "Integrateur.h"
#include "Vecteur3D.h"
#include <vector>

class IntegrateurNewmark : public Integrateur {
	public:
	
	virtual ~IntegrateurNewmark() {}
	
	// méthode d'intégration //
	
	virtual void evolue(Masse*, double const&, std::vector<Masse*> contraintes = std::vector<Masse*>({})) override ;
	virtual std::string mon_nom() const override {return "Integrateur de Newmark";}
	virtual double mon_dt() const {return 2.0;}
};

#endif //INTEGRATEUR_NEWMARK	
