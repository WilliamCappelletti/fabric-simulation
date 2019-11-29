#ifndef MI_DIMENTICO_COME_CI_SI_SIEDE
#define MI_DIMENTICO_COME_CI_SI_SIEDE

#include "Masse.h"
#include "Dessinable.h"

class Ressort : public Dessinable {
	public:
	
	// constructeurs //
	
	Ressort(Masse* m1, Masse* m2, double ke=1.0, double lz=1.0, bool est_tissu = false, SupportADessin* = nullptr);
	
	Ressort(Ressort const&);
	
	// destructeur //
	
	~Ressort();
	
	// accesseurs //
	
	double get_k() const;
	double get_l0() const;
	Masse* get_m_depart() const;
	Masse* get_m_arrivee() const;
	
	Vecteur3D force_rappel(Masse*);
	void update_masses();
	bool check_masses();
	
	virtual void dessine() override { support->dessine(*this); }
	
	private:
	
	Masse* m_depart;
	Masse* m_arrivee;
	double k;
	double l0;
};

  // surcharges //
  
  std::ostream& operator<<(std::ostream&, Ressort const&);

#endif // MI_DIMENTICO_COME_CI_SI_SIEDE
