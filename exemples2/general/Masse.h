#ifndef TARZAN
#define TARZAN

#include "Vecteur3D.h"
#include "Dessinable.h"
#include <vector>

class Ressort;
class Masse : public Dessinable {
	public:
	// constructeur:
	
	explicit Masse(double masse, Vecteur3D position0 = Vecteur3D(0.0, 0.0, 0.0),
										Vecteur3D v0 = Vecteur3D(0.0, 0.0, 0.0), 
										double cf=0.0,
										bool f = true,
										SupportADessin* = nullptr);
	
	// constructeur de copie:
	
	//explicit Masse(Masse const&);
	
	// destructeur:
	
	~Masse();
	
	// accesseurs:
	
	double get_m() const;
	Vecteur3D get_v() const;
	Vecteur3D get_position() const;
	Vecteur3D get_force_subie() const;
	double get_cf() const;
	size_t nbr_ressorts() const;		// donne le nombre de ressorts connecté à Masse
	
	// manipulateurs
	
	void set_pos(Vecteur3D const&);
	void set_vit(Vecteur3D const&);
	void set_masse(double const&);
	void set_cf(double const&);
	void fixe();
	
	// methodes:
	
	void ajoute_force(Vecteur3D const&);
	Vecteur3D acceleration();
	void mise_a_jour_forces();
	void ajoute_ressort(Ressort*);
	void enleve_ressort(Ressort*);
	void cout_ressorts() const;
	void est_fixe();
	void force_normale();
	
	bool check_ressorts() const;
	
	bool check_masses(Ressort*) const;
	
	bool check_connection(Masse*) const;
	
	virtual void dessine() override { support->dessine(*this); }
	
	Vecteur3D force_totale() ;

	
	// methodes virtuelles pour les contraintes:
	
	virtual void appliquer(Tissu*, double) {}
	virtual bool est_contrainte() const { return false; }
	virtual Vecteur3D get_rayon() const { return Vecteur3D(0.0, 0.0, 0.0); }
	virtual bool est_vincole(Masse*) {return false;}
	
	protected:
	
	virtual double g() const { return 0.0; }
	
	double m;					// masse
	Vecteur3D position;
	Vecteur3D v;				//vitesse
	double cf;					//coeff. de frottement
	Vecteur3D force_subie;
	std::vector <Ressort*> ressorts;
	bool est_mobile; 
	
};

std::ostream& operator<<(std::ostream&, Masse const&);

#endif //TARZAN
