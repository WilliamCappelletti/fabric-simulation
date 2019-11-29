#include <iostream>
#include <memory>
#include "Systeme.h"
#include "Tissu.h"
//#include "Contrainte.h"

using namespace std;

 // constructeur //
 
 Systeme::Systeme(vector<Tissu*> & entree, vector<int> & i, vector<Masse*> & contr, SupportADessin* support, int const& c, int const& n)
 :Dessinable(support), compteur_graphique(c), compteur_numerique(n)
 {
	 for(auto & t:entree){
		 tissus.push_back(t);
		 t->Dessinable::set_support(support);
	 }
	 for(auto & contrainte : contr) {
		 contraintes.push_back(contrainte);
		 contrainte->Dessinable::set_support(support);
	 }
	 for(auto integrateur : i) {
		 if(integrateur==1) integrateurs.push_back(new IntegrateurEuler);
		 if(integrateur==2) integrateurs.push_back(new IntegrateurNewmark);
		 if(integrateur==3) integrateurs.push_back(new IntegrateurRunge); 
	 }
 }
 
 Systeme::~Systeme() {
	 
	for(auto & i : integrateurs) delete i;
	
	 } 
 
 // méthodes //
 
 void Systeme::cout_tissus() const{
	 for(auto const& t: tissus){
		 cout << "Tissu : " << &t << endl;
		 cout << *t << endl;
	 } 
 }
 
 std::vector<Tissu> Systeme::get_tissus() const{
	 vector<Tissu> exit;
	 for(auto const& t: tissus){
		 exit.push_back(*t);
	 } 
	 return exit;
 }
 
 void Systeme::evolue(double const& dt) {
	 for(auto & t : tissus){
		 t->mise_a_jour_forces();
	 }
	 for(size_t i(0); i < contraintes.size(); ++i) {
		 contraintes[i]->mise_a_jour_forces();
		 
		 for(auto & t : tissus) {
			 contraintes[i]->appliquer(t, dt);
		 }
		 
		 for(size_t j(i+1); j < contraintes.size(); ++j){
			 Tissu* t(new Tissu(contraintes[j], support));
			 contraintes[i]->appliquer(t, dt);
		 }
		 
		 integrateurs[compteur_numerique]->evolue(contraintes[i], dt, contraintes);
	 }
	 for(auto & t : tissus){
		 t->evolue(integrateurs[compteur_numerique], dt, contraintes);
	 }
 }
 
void Systeme::dessine_systeme() const {
	 
	 for(auto & c : contraintes){
		 c->dessine();
	 }
	 
	 if(compteur_graphique == 0){
		 for(auto & t : tissus){
			 t->dessine();
		 }
	 }
	 if(compteur_graphique == 1){
		 for(auto & t : tissus){
			 t->dessine_tissu_ressorts();
		 }
	 }
	 if(compteur_graphique == 2){
		 for(auto & t : tissus){
			 t->dessine_tissu_masses();
		 }
	 }	 
 }
 /*
 void Systeme::ressorts() const {
	 for(auto & t : tissus){
		 t->set_dessin();
	 }
 }
 */
 
 void Systeme::operator+=(Masse* c) {
	 if(c != nullptr) {
		 contraintes.push_back(c);
	 }
 }
 
  void Systeme::augmente_compteur_graphique() {
	 ++compteur_graphique;
	 if(compteur_graphique>2) compteur_graphique = 0;
}

void Systeme::augmente_compteur_numerique() {
	 ++compteur_numerique;
	 if(compteur_numerique>=integrateurs.size()) compteur_numerique = 0;
}

unsigned int Systeme::get_CN() const{
	return compteur_numerique;
}
