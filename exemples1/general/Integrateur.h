#ifndef INTEGRATEUR
#define INTEGRATEUR

//#include "Tissu.h"
#include "Masse.h"
#include <vector>
#include <string>

class Integrateur {
	public:
	
	// destructeur virtuel
	
	virtual ~Integrateur();
	
	// méthode d'intégration //
	
	virtual void evolue(Masse*, double const&, std::vector<Masse*> contraintes = std::vector<Masse*>({})) = 0;
	virtual std::string mon_nom() const = 0;
	virtual double mon_dt() const = 0;
		
};

#endif //INTEGRATEUR	
