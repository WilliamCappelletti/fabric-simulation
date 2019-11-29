#include <iostream>
#include "Ressort.h"
using namespace std;

  // constructeur //
  
  Ressort::Ressort(Masse* m1, Masse* m2, double ke, double lz, bool est_tissu, SupportADessin* support)
  : Dessinable(support), m_depart(m1), m_arrivee(m2), k(ke), l0(lz)
  {
	  if (not est_tissu) {
		  m1->ajoute_ressort(this);
		  m2->ajoute_ressort(this);
	  }
	  /*
	  cout << "----------------------" << endl 
			<< " Constructeur ressort "<< endl
			<< m1 << " " << m2 << endl
			<< m_depart << " " << m_arrivee << endl
			<< "-------------------------" << endl;
	  */
  }
  
  // constructeur de copie //
  
  Ressort::Ressort(Ressort const& r)
  : Dessinable(r.support), m_depart(r.m_depart), m_arrivee(r.m_arrivee), k(r.k), l0(r.l0)
  {}
  
  
  // destructeur //
  
  Ressort::~Ressort(){
	  m_depart->enleve_ressort(this);
	  m_arrivee->enleve_ressort(this);
  }
  
  // accesseurs //
  
   double Ressort::get_k() const {
	  return k;
  }
  
  double Ressort::get_l0() const {
	  return l0;
  }
  
  Masse* Ressort::get_m_depart() const {
	  return m_depart;
  }
  
  Masse* Ressort::get_m_arrivee() const {
	  return m_arrivee;
  }

  // méthodes //

  Vecteur3D Ressort::force_rappel(Masse* A){
	  if(A==m_depart){
		  Vecteur3D l(m_arrivee->get_position()-A->get_position());
		  Vecteur3D force(l.normalise()*(l.norme()-l0));
		  return force*k;
	  }
	  if(A==m_arrivee){
		  Vecteur3D l(m_depart->get_position()-A->get_position());
		  Vecteur3D force(l.normalise()*(l.norme()-l0));
		  return force*k;
	  }
	  else{
		  Vecteur3D z(0.0, 0.0, 0.0);
		  return z;
	  }
  }
  
  void Ressort::update_masses() {
	  m_depart->ajoute_ressort(this);
	  m_arrivee->ajoute_ressort(this);
  }
  
  bool Ressort::check_masses(){
	  bool control(false);
	  bool control2(false);
	  
	  if (m_depart->check_masses(this)) { control = true; }
	  else {cerr << "La masse " << m_depart << " ne sait pas d'etre attachee au ressort " << this << "!" << endl;}
	  
	  if (m_arrivee->check_masses(this)) { control2 = true; }
	  else {cerr << "La masse " << m_arrivee << " ne sait pas d'etre attachee au ressort " << this << "!" << endl;}
	  
	  return (control and control2);
  }
  
  // surcharges //
  
  std::ostream& operator<<(std::ostream& cout, Ressort const& r) // opérateur d'affichage        
  {
	  const Ressort* that(&r);
	  cout << "Ressort " << that << " :" << endl;
	  cout << r.get_k() << " # constante de raideur" << endl;
	  cout << r.get_l0() << " # longueur au repos" << endl;
	  cout << "Masse de départ : Masse " << r.get_m_depart() << " :" << endl;
	  cout << *(r.get_m_depart()) << endl;
	  cout << "Masse d'arrivée : Masse " << r.get_m_arrivee() << " :" << endl;
	  cout << *(r.get_m_arrivee()) << endl;

	  return cout;
  }
