#ifndef AUTRE_ATELIER_COLORIAGE
#define AUTRE_ATELIER_COLORIAGE

class Systeme;
class Tissu;
class Masse;
class Ressort;
class Contrainte;
class SupportADessin{
	
	public:
	
  virtual ~SupportADessin() {}

  virtual void dessine(Tissu       const&) = 0;
  virtual void dessine(Systeme     const&) = 0;
  virtual void dessine(Masse       const&) = 0;
  virtual void dessine(Ressort     const&) = 0;
  virtual void dessine(Contrainte  const&) = 0;
	
};

#endif //AUTRE_ATELIER_COLORIAGE
