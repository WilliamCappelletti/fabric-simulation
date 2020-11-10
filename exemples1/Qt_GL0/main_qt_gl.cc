#include <QApplication>
#include "glwidget.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
  QApplication a(argc, argv); 		//A ne pas modifier !
  
  
  //Tissus:
  
  
	vector<Tissu*> init;
 
	// TEST CHAINE
	
	vector<Vecteur3D> chaine = {Vecteur3D(1.5, 0.0, 0.0),		//Dans ce vecteur on déclare les positions des composantes
								Vecteur3D(1.5, 1.0, 0.0),
								Vecteur3D(1.5, 1.5, 0.0)};
	
	TissuChaine tissu1(1.0,							//masse des composantes
						0.0,						//coeff de frottement
						100,						//raideur des ressorts
						1.0,						//longueur à vide des ressorts
						chaine);				
	
	Tissu* ptr_tissu1(&tissu1);
	init.push_back(ptr_tissu1);					//ATTENTION! ce tissu fera partie d'un tissu composé,
													//décommenter si vous décidez de faire autrement
	
	
	/*
	//TEST RECTANGLE
	TissuRectangle tissu2(1.0,						//masse
						Vecteur3D(0.0, 1.0, 0.0), 	//l (largeur)
						Vecteur3D(1.0, 0.0, 0.0),	//L (longueur)
						Vecteur3D(0.0, 0.0, 0.0),	//origine
						0.0,						//cf
						1.0,						//densité
						100,						//raideur des ressorts
						0.5);						//longuer à vide des ressorts
	
	Tissu* ptr_tissu2(&tissu2);
	//init.push_back(ptr_tissu2);					//ATTENTION! ce tissu fera partie d'un tissu composé,
													//décommenter si vous décidez de faire autrement
	*/
	
	/*
	//TEST DISCQUE
	
	TissuDisque tissu3(1.0,							//masse
						Vecteur3D(0.0, 0.0, 0.0),	//centre
						Vecteur3D(0.0, 0.0, 30.0),	//radius*normale
						0.75,						//pas
						0.0,						//cf
						100,						//raideur des ressorts
						20);						//(angle) (facultatif)
	
	Tissu* ptr_tissu3(&tissu3);
	init.push_back(ptr_tissu3);
	 
	*/
	
	/*
	//TEST COMPOSE
	
	vector<Tissu*> liste = {ptr_tissu1, ptr_tissu2};		//liste d'initialisation du tissu composé
	
	TissuCompose tissu4(liste, 
						1.0,						//longueur à vide des nouveaux ressorts et distance maximale pour 
													//que deux masses soient attachées
						100);						//raideur des ressorts
	
	Tissu* ptr_tissu4(&tissu4);
	init.push_back(ptr_tissu4);
	*/
	
	
    //Contraintes:
  
  vector<Masse*> contraintes;
  
  /*
  Crochet c1(Vecteur3D(-20.0, -20.0, 0.0),			//Centre du crochet
             Vecteur3D(2.0, 0.0, 0.0),				//Rayon 
             Vecteur3D(0.0, 0.0, 0.0));				//(Vitesse)
           
  
  Masse* ptr_c1(&c1);
  contraintes.push_back(ptr_c1);
  */
  
  /*  
  Impulsion c2(Vecteur3D(0.0, 10.0, 0.0),			//Centre de l'impulsion
				Vecteur3D(2.0, 0.0, 0.0),			//Rayon
				0.0,								//temps initial d'application
				10.0,								//temps final
				Vecteur3D(0.0, 0.0, 10.0),			//Force à appliquer
				init);								//Liste des tissus cibles (ici on l'applique à tous ceux qui sont 
													//à portée
  Masse* ptr_c2(&c2);
  contraintes.push_back(ptr_c2);
  */
  
  /*   
  Impulsion_sinusoidale c3(Vecteur3D(0.0, 20.0, 0.0),		//Centre de l'impulsion
							Vecteur3D(25.0, 0.0, 0.0),		//Rayon
							0.0,							//temps initial d'application
							10.0,							//temps final
							Vecteur3D(0.0, 0.0, 10.0),		//Force à appliquer
							23.0,							//Fréquence d'application
							init);							//Liste des tissus cibles (ici on l'applique à tous ceux qui sont 
															//à portée
  
  Masse* ptr_c3(&c3);
  contraintes.push_back(ptr_c3);
  */
  
  /*
  Sphere c4(Vecteur3D(-20.0, -20.0, 0.0),			//Centre de la sphère
             Vecteur3D(2.0, 0.0, 0.0),				//Rayon 
             Vecteur3D(0.0, 0.0, 10.0));			//(Vitesse)             
  
  Masse* ptr_c4(&c4);
  contraintes.push_back(ptr_c4);
  */
  
  
  /*
  Corp c5(Vecteur3D(7.0, 11.0, 10.0),				//Centre
             Vecteur3D(2.0, 0.0, 0.0),				//Rayon
             0.25,									//Masse
             0.25,									//coeff. de frottement
             Vecteur3D(0.0, 0.0, 0.0));				//(vitesse)
  
  
  Masse* ptr_c5(&c5);
  contraintes.push_back(ptr_c5);
  */
  
  
  /* On choisit les intégrateurs à utiliser avec un tableau dynamique d'entiers.
   * On impose les contrintes suivantes :
   * 1 --> Integrateur d'Euler
   * 2 --> Integrateur de Newmark
   * 3 --> Integrateur de Runge-Kutta
  */
  
  vector<int> integra({1,2,3});                         
  
  GLWidget w(init, integra, contraintes);
  w.show();
  
  return a.exec();
}
