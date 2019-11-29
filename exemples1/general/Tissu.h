#ifndef HERCULES
#define HERCULES

#include <vector>
#include "Vecteur3D.h"
#include "Masse.h"
#include "Ressort.h"
#include "Int_Euler.h"
#include "Int_New.h"
#include "Int_Runge.h"
#include "Dessinable.h"

typedef std::vector<unsigned int> Dependances;

class TissuCompose;
class Contrainte;
class Systeme;

class Tissu : public Dessinable {
	public:
	
	// constructeur:
	
	explicit Tissu(std::vector<Masse>& liste_init,
					std::vector<Dependances> const& couples,
					double ke = 1.0, double lz = 1.0, SupportADessin* = nullptr); //On a toujours besoin de la liste des masses 
																		          //et des leurs dépendances
	
	explicit Tissu(Masse*, SupportADessin* = nullptr);				//cela nous sert pour créer des tissus d'une seule masse sans trop
																	//de données inutiles
	
	
	// destructeur:
	virtual ~Tissu();												//puisqu'on aura du polymorphisme il est mieux de l'avoir
	
	// methodes:
	
	friend std::ostream& operator<<(std::ostream&, Tissu const&);
	
	void affiche_ressorts() const ;
	
	void affiche_masses() const ;
	
	void mise_a_jour_forces();
	void evolue(Integrateur*, double const&, std::vector<Masse*> contraintes = std::vector<Masse*>({}));
	
    virtual void dessine() override { support->dessine(*this); }
    
		//methodes auxiliaires pour le dessin
		
    void dessine_tissu() const;
    void dessine_tissu_masses() const;	
    void dessine_tissu_ressorts() const;
    
    std::vector<Masse*> check_contrainte(Contrainte*) const;	//Retourne la liste de ses masses qui sont soumises à la containte
																//pasée en paramètre
    
    void couper(Vecteur3D centre, double R);					//évolution de methode trou(size_t)
	
	friend class TissuCompose;									//ça simplifie beaucoup le codage
	
	protected:
	
	//attributs:
	
	std::vector<Masse*> masses;
	std::vector<Ressort> ressorts;
	// double l_ressorts;
	
	//methodes:
	
	void connecte(size_t m1_index, size_t m2_index, double ke = 1.0, double lz = 1.0);
	void connecte_masses();
	bool check();
	
	explicit Tissu(SupportADessin*);							//ce constructeur par défaut pour initialiser un tissu vide peut etre 
																//appelé seulement par ses souclasses !
	
};
	
std::ostream& operator<<(std::ostream&, Tissu const&);
	
	
class TissuChaine : public Tissu {
	public:
	
	//constructeur:
	
	explicit TissuChaine(double masse, double cf, double k, double l0,
							std::vector<Vecteur3D> table_pos, SupportADessin* = nullptr);
	
	//destructeur : (pour vider la mémoire alloquée)
	
	~TissuChaine();
	
	protected: 
	
} ;
	
class TissuRectangle : public Tissu {
	public:
	
	//constructeur:
	
	explicit TissuRectangle(double masse, Vecteur3D largeur, Vecteur3D longueur, Vecteur3D origine,
							double cf, double densite, double k, double l0, SupportADessin* = nullptr);
	
	//destructeur : (pour vider la mémoire alloquée)
	
	~TissuRectangle();
	
	//methodes :
	
	void accroche(unsigned short int i = 2);				//pour immobiliser une coté (pour la convention voire "Tissu.cc")
	
	protected: 
	
	int X;
	int Y;
} ;

class TissuDisque : public Tissu {
	public:
	
	//constructeur:
	
	explicit TissuDisque(double masse, Vecteur3D centre, Vecteur3D radius, double pas, double cf, double k,
							int phi = 20, SupportADessin* = nullptr);
							
							
	//destructeur: (pour vider la mémoire alloquée)
	
	~TissuDisque();
	
	protected:
	
	Vecteur3D radius;
	double R;
	int phi;			//phi est le pas angulaire de la toile, int pouréviter problèmes avec les positions des masses
	int C_masses;		//est le nombre des masses sur la circumpherence
	int R_masses;		//est le nombre des masses sur le radium
} ;

class TissuCompose : public Tissu {
	public:
	
	//constructeur:
	
	explicit TissuCompose(std::vector<Tissu*> composantes, double l, double ke, SupportADessin* = nullptr);
	
	//operateurs:
	
	void operator+=(Tissu*);
	
	protected:
	
	//std::vector<Tissu*> composantes;
	double l;
	double ke;
	int nbr_composantes;
	
	void raccommode();
} ;


#endif //HERCULES
