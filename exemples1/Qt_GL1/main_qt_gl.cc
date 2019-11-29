#include <QApplication>
#include "glwidget.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  
  

  //Tissus:
  
 
  TissuRectangle test1(0.5,						    //masse
					  Vecteur3D(0.0, 40.0, 0.0), 	//l
					  Vecteur3D(40.0, 0.0, 0.0),	//L
					  Vecteur3D(-20.0, -20.0, 0.0),	//origine
					  0.25,						//coefficient de frottement
					  0.5,						//densité de masses
					  100,						    //coefficient ressort
					  2.0);						//longueur ressorts
  
  

  Tissu* ptr_test1 = &test1;
   
    
  vector<Tissu*> init({ptr_test1});
  
    //Contraintes:
  
  
  Crochet c1(Vecteur3D(-20.0, -20.0, 0.0),
             Vecteur3D(2.0, 0.0, 0.0),
             Vecteur3D(0.0, 0.0, 0.0));
             
                          
  Crochet c2(Vecteur3D(20.0, -20.0, 0.0),
             Vecteur3D(3.0, 0.0, 0.0),
             Vecteur3D(0.0, 0.0, 1.0));
     
     
             
  Impulsion_sinusoidale c3(Vecteur3D(0.0, 20.0, 0.0),
							Vecteur3D(25.0, 0.0, 0.0),
							0.0,
							10.0,
							Vecteur3D(0.0, 0.0, 10.0),
							23.0,
							init);
  
  Masse* ptr1 = &c1;
  Masse* ptr2 = &c2;
  Masse* ptr3 = &c3;
   
  vector<Masse*> contraintes = {ptr1, ptr2, ptr3};
  
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
