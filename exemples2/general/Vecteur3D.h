#ifndef VELO_DI_MAIA
#define VELO_DI_MAIA

#include <iostream>

class Vecteur3D {
	public: 
	
	// Constructeur par défaut et cartésien //
	
	explicit Vecteur3D(double X=0.0, double Y=0.0, double Z=0.0);
	
	// Constructeur de copie //
	
	Vecteur3D(Vecteur3D const&);
		
	// Accesseurs à éliminer si possible //
	
	double getx() const;
	double gety() const;
	double getz() const;
	
	// Autres méthodes //
	
	void set_coord(double a, double b, double c);
	
	bool compare(Vecteur3D vecteur) const; 
	
	Vecteur3D addition(Vecteur3D vecteur) const;
	
	Vecteur3D soustraction(Vecteur3D vecteur) const;
	
	Vecteur3D oppose() const;
	
	Vecteur3D mult(double k) const;
	
	double prod_scal(Vecteur3D vecteur) const;
	
	Vecteur3D prod_vect(Vecteur3D vecteur) const;
	
	double norme();
	
	double norme2();
	
	Vecteur3D normalise() const;
	
	// Surcharges internes //
	
	bool operator==(Vecteur3D const&) const;        // égalité
	bool operator!=(Vecteur3D const&) const;  
	Vecteur3D& operator+=(Vecteur3D const&);        
	Vecteur3D& operator-=(Vecteur3D const&);
    Vecteur3D operator^(Vecteur3D const&) const;    // produit vectoriel
    void operator*=(double);                        // produit par un scalaire qui modifie le vecteur
    const Vecteur3D operator*(double);              // produit par un scalaire qui retourne un vecteur et qui ne modifie pas l'argument
    const Vecteur3D operator/(double);              // division par un scalaire qui retourne un vecteur et qui ne modifie pas l'argument

	private:
	 
	double x;
	double y;
	double z;
};

  // Opérateur d'affichage //
  
  std::ostream& operator<<(std::ostream&, Vecteur3D const&);
  
  // Surcharges externes //
  
  Vecteur3D operator+(Vecteur3D, Vecteur3D const&);      // somme
  Vecteur3D operator-(Vecteur3D, Vecteur3D const&);      // soustraction de vecteurs
  Vecteur3D operator-(Vecteur3D);                        // opposé
  double operator*(Vecteur3D const&, Vecteur3D const&);  // produit scalaire 
  
#endif // VELO_DI_MAIA
