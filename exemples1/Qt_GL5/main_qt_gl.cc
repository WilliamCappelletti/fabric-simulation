#include <QApplication>
#include "glwidget.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  
  Sphere c1(Vecteur3D(5.0, -5.0, 10.0),
             Vecteur3D(10.0, 0.0, 0.0));
  Sphere c3(Vecteur3D(10.0, 7.0, -5.0),
             Vecteur3D(15.0, 0.0, 0.0));
  Sphere c2(Vecteur3D(25.0, 0.0, 0.0),
            Vecteur3D(25.0,0,0));
                
  Masse* ptr1 = &c1;
  Masse* ptr2 = &c2;
  Masse* ptr3 = &c3;
  vector<Masse*> contraintes({ptr1, ptr2, ptr3});
  
  TissuRectangle test(0.5,						    //masse
					  Vecteur3D(0.0, 30.0, 0.0), 	//l
					  Vecteur3D(25.0, 0.0, 0.0),	//L
					  Vecteur3D(0.0, -10.0, 40.0),	//origine
					  0.1,						//coefficient de frottement
					  0.75,						//densité de masses
					  100,						    //coefficient ressort
					  1/0.75);						//longueur ressorts


  Tissu* ptr_test = &test;
  vector<Tissu*> init({ptr_test});
  
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
