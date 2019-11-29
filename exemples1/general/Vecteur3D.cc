#include <cmath>
#include <iostream>
#include "Vecteur3D.h"
using namespace std;

    // Constructeur par défaut et cartésien //
	
	Vecteur3D::Vecteur3D(double X, double Y, double Z)
	: x(X), y(Y), z(Z)
	{}
	
	// Constructeur de copie //
	
	Vecteur3D::Vecteur3D(Vecteur3D const& vect)
	: x(vect.x), y(vect.y), z(vect.z)
	{}

    // Accesseurs //

    double Vecteur3D::getx() const {
		return x;
	}
	
	double Vecteur3D::gety() const {
		return y;
	}
	
	double Vecteur3D::getz() const {
		return z;
	}	

    //Autres méthodes //

	void Vecteur3D::set_coord(double a, double b, double c){
		x=a;
		y=b;
		z=c;
	}
	
	bool Vecteur3D::compare(Vecteur3D vecteur) const {
		if(vecteur.x==x and vecteur.y==y and vecteur.z==z){
		return true;
	}else{
		return false;
		}
	}
	
	Vecteur3D Vecteur3D::addition(Vecteur3D vecteur) const{
		Vecteur3D vect(x+vecteur.x, y+vecteur.y, z+vecteur.z);
		return vect;
	}
	
	Vecteur3D Vecteur3D::soustraction(Vecteur3D vecteur) const{
		Vecteur3D vect(x-vecteur.x, y-vecteur.y, z-vecteur.z);
		return vect;
	}
	
	Vecteur3D Vecteur3D::oppose() const{
		Vecteur3D vect(-x,-y,-z);
		return vect;
	} 
	
	Vecteur3D Vecteur3D::mult(double k) const{
		Vecteur3D vect(k*x,k*y,k*z);
		return vect;
	}
	
	double Vecteur3D::prod_scal(Vecteur3D vecteur) const{
		return x*vecteur.x+y*vecteur.y+z*vecteur.z;
	}
	
	Vecteur3D Vecteur3D::prod_vect(Vecteur3D vecteur) const{
		Vecteur3D vect((y*vecteur.z-z*vecteur.y),(z*vecteur.x-x*vecteur.z),(x*vecteur.y-y*vecteur.x));
		return vect;
	}
	
	double Vecteur3D::norme(){
		return sqrt(x*x+y*y+z*z);
	}
	
	double Vecteur3D::norme2(){
		return x*x+y*y+z*z;
	}
	
	Vecteur3D Vecteur3D::normalise() const {
		double n(sqrt(x*x+y*y+z*z));
		Vecteur3D vect(x/n, y/n, z/n);
		return vect;
	}
	
	// Surcharges internes //

    bool Vecteur3D::operator==(Vecteur3D const& vect) const{                             // égalité
		if(vect.x==x and vect.y==y and vect.z==z){
		return true;
	}else{
		return false;
		}
	}
	
	bool Vecteur3D::operator!=(Vecteur3D const& vect) const{
		if(vect.x!=x or vect.y!=y or vect.z!=z){
		return true;
	}else{
		return false;
		}
	}
	
	Vecteur3D& Vecteur3D::operator+=(Vecteur3D const& vect){
		x += vect.x;
		y += vect.y;
		z += vect.z;
		return *this;
	}
	
	Vecteur3D& Vecteur3D::operator-=(Vecteur3D const& vect){
		x -= vect.x;
		y -= vect.y;
		z -= vect.z;
		return *this;
	}
		
	Vecteur3D Vecteur3D::operator^(Vecteur3D const& vect) const {                         // produit vectoriel
		Vecteur3D vect1((y*vect.z-z*vect.y),(z*vect.x-x*vect.z),(x*vect.y-y*vect.x));
		return vect1;
	}
	
    const Vecteur3D Vecteur3D::operator*(double a) {             // produit par un scalaire qui retourne un vecteur 
		Vecteur3D vect(x*a, y*a, z*a);                           // et qui ne modifie pas l'argument
		return vect;
	}
	
	const Vecteur3D Vecteur3D::operator/(double a) {             // division par un scalaire qui retourne un vecteur 
		Vecteur3D vect(x/a, y/a, z/a);                           // et qui ne modifie pas l'argument
		return vect;
	}
	
	void Vecteur3D::operator*=(double a) {                       // produit par scalaire qui modifie le vecteur  
		x *= a;
		y *= a;
		z *= a;
	}
	
	
	// Surcharges externes //
	
	std::ostream& operator<<(std::ostream& cout, Vecteur3D const& vect) // opérateur d'affichage        
  {
	  cout << vect.getx() << " " << vect.gety() << " " << vect.getz();
	  return cout;
  }
  
  Vecteur3D operator+(Vecteur3D v1, Vecteur3D const& v2){               // somme
	  v1 += v2;
	  return v1;
  }
  
  Vecteur3D operator-(Vecteur3D v1, Vecteur3D const& v2){               // soustraction d'un vecteur
	  v1 -= v2;
	  return v1;
  }
  
  Vecteur3D operator-(Vecteur3D vec) {                                  // opposé
		Vecteur3D vect(-vec.getx(),-vec.gety(),-vec.getz());
		return vect;
	}
	
  double operator*(Vecteur3D const& vect, Vecteur3D const& vect2) {            // produit scalaire
	   return vect2.getx()*vect.getx()+vect2.gety()*vect.gety()+vect2.getz()*vect.getz();
	 }
  
