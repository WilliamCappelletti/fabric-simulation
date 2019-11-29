#ifndef starwars
#define starwars

#include "Tissu.h"

class Contrainte : public Masse {
	public:
	
	//Constructeurs:
	
	explicit Contrainte(Vecteur3D O, Vecteur3D R, Vecteur3D v = Vecteur3D(0.0, 0.0, 0.0),
							double m = 0.0, double cf = 0.0, SupportADessin* = nullptr);
	
	//Methodes:
	
	virtual void appliquer(Tissu*, double) override = 0;
	virtual bool est_vincole(Masse*);									//nous dit si la masse passée est vincolée
	
	virtual void dessine() override { support->dessine(*this); }
	
	Vecteur3D get_centre() const {return position;} 
	virtual Vecteur3D get_rayon() const override {return R;}
	
	virtual bool est_contrainte() const override { return true; }
	
	protected:
	
	//centre d'application Hérité par Masse
	
	virtual double g() const { return 9.81; }							//pour les simulations
	
	Vecteur3D R;			//rayon
};

class Crochet : public Contrainte {
	public:
	
	//Constructeurs:
	
	explicit Crochet(Vecteur3D O, Vecteur3D R, Vecteur3D v = Vecteur3D(0.0, 0.0, 0.0));
	
	//Methodes:
	
	virtual void appliquer(Tissu*, double) override;
	
	protected:
	
};

class Impulsion : public Contrainte {
	public:
	
	//Constructeurs:
	
	explicit Impulsion(Vecteur3D O, Vecteur3D R, double t1, double t2, Vecteur3D F, 
						std::vector<Tissu*> cibles);
	
	//Methodes:
	
	virtual void appliquer(Tissu*, double) override;
	
	protected:
	
	double t_start;
	double t_end;
	Vecteur3D F;					//force à appliquer
	std::vector<Masse*> masses;		//cibles
	
};


class Impulsion_sinusoidale : public Impulsion {
	public:
	
	//Constructeurs:
	
	explicit Impulsion_sinusoidale(Vecteur3D O, Vecteur3D R, double t1, double t2, Vecteur3D F0, 
										double pace, std::vector<Tissu*> cibles);
	
	//Methodes:
	
	virtual void appliquer(Tissu*, double) override;
	
	protected:
	
	Vecteur3D F0;		//Force maximale
	double pace;		//fréquence
};


//EXTENSIONS! ces contraintes se comportent comme de vrais objets

class Objet : public Contrainte {
	public:
	
	//Constructeurs:
	
	explicit Objet(Vecteur3D O, Vecteur3D R, Vecteur3D v = Vecteur3D(0.0, 0.0, 0.0),
							double m = 0.0, double cf = 0.0);
	
	virtual ~Objet() = 0;
	
	//Methodes:
	
	virtual void appliquer(Tissu*, double) override;
	
	protected:
	
};

class Sphere : public Objet {
	public:
	
	explicit Sphere(Vecteur3D O, Vecteur3D R, Vecteur3D v = Vecteur3D(0.0, 0.0, 0.0));
	
	virtual ~Sphere() override {}
	
	
	protected:
	
};

class Corp : public Objet {
	public:
	
	//Constructeurs:
	
	explicit Corp(Vecteur3D O, Vecteur3D R, double m,
					double cf, Vecteur3D v = Vecteur3D(0.0, 0.0, 0.0));
	
	virtual ~Corp() override {}
	
	//Methodes
	
	virtual void appliquer(Tissu*, double) override;
	
	protected:
	
	
};



#endif //starwars
