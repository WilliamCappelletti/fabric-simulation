#include <QApplication>
#include "glwidget.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  
  
  //Contraintes:
  
  
  Sphere c1(Vecteur3D(-15.0, 0.0, 0.0),
             Vecteur3D(5.0, 0.0, 0.0),
             Vecteur3D(4.5, 0.0, 0.0));
       
  Masse* ptr1 = &c1;
  
  vector<Masse*> contraintes = {ptr1};
  
  
  //Tissus:
  
  TissuRectangle test1(0.25,						    //masse
					  Vecteur3D(0.0, 20.0, 0.0), 	//l
					  Vecteur3D(0.0, 0.0, -12.0),	//L
					  Vecteur3D(0.0, -10.0, 10.0),	//origine
					  0.5,						//coefficient de frottement
					  1.25,						//densité de masses
					  100,						    //coefficient ressort
					  1/1.25);						//longueur ressorts
  
  TissuRectangle test2(0.25,						    //masse
					  Vecteur3D(0.0, 20.0, 0.0), 	//l
					  Vecteur3D(0.0, 0.0, -9.0),	//L
					  Vecteur3D(15.0, -10.0, 10.0),	//origine
					  0.5,						//coefficient de frottement
					  1.5,						//densité de masses
					  100,						    //coefficient ressort
					  1/1.5);						//longueur ressorts

  
  Tissu* ptr_test1 = &test1;
  Tissu* ptr_test2 = &test2;
  
  
  test1.accroche(3);
  test2.accroche(3);
  
  
  vector<Tissu*> init({ptr_test1, ptr_test2});
  

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
