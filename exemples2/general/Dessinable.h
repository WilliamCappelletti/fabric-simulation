#ifndef ATELIER_COLORIAGE
#define ATELIER_COLORIAGE

#include <memory>
#include "SupportADessin.h"

class Dessinable{
	public:
	
	// constructeur, destructeur//
	
	Dessinable(SupportADessin* support)
	: support(support)
	{}
	Dessinable(Dessinable const&) {}
	virtual ~Dessinable() {}
	
	// méthode //
	
	virtual void dessine() = 0;
	virtual void set_support(SupportADessin* s) {support = s;}
	
	protected:
	
	// attribut //
	
	SupportADessin* support;
	//std::unique_ptr<SupportADessin> support;
};

#endif //ATELIER_COLORIAGE
