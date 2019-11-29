#include "Contraintes.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

int main() {
	
	// TEST CHAINE
	vector<Vecteur3D> chaine = {Vecteur3D(0.0, 0.0, 0.0)};
	
	TissuChaine test1(1.0, 0.0, 100, 1.0, chaine);
	
	Crochet c1(Vecteur3D(0.0, 0.0, 0.0), Vecteur3D(1.0, 0.0, 0.0));
	
	Impulsion c2(Vecteur3D(0.0, 0.0, 0.0), Vecteur3D(1.0, 0.0, 0.0), 0.0, 10.0, 
					Vecteur3D(1.0, 0.0, 0.0), {&test1});
	
	
	Impulsion_sinusoidale c3(Vecteur3D(0.0, 0.0, 0.0), Vecteur3D(1.0, 0.0, 0.0), 0.0, 10.0, 
					Vecteur3D(1.0, 0.0, 0.0), 1.0, {&test1});
	
	Tissu* ptr_t = &test1;
	Contrainte* ptr_c = &c1;
	
	ptr_c->appliquer(ptr_t, 0.0);
	
	cout << test1 << endl;	
	
	ptr_c = &c2;
	ptr_c->appliquer(ptr_t, 0.0);
	
	cout << test1 << endl;	
	
	ptr_c = &c3;
	ptr_c->appliquer(ptr_t, 0.75);
	
	cout << test1 << endl;	
	
	return 0;
}
