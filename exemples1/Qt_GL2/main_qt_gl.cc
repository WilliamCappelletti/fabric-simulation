#include <QApplication>
#include "glwidget.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  
  
  //Contraintes:
  
  
  Corp c1(Vecteur3D(7.0, -10.0, 15.0),
             Vecteur3D(2.0, 0.0, 0.0),
             0.25,
             0.15,
             Vecteur3D(0.0, 20.0, 0.0));
  
  Corp c2(Vecteur3D(0.0, 17.0, 15.0),
             Vecteur3D(2.0, 0.0, 0.0),
             0.35,
             0.15,
             Vecteur3D(0.0, 0.0, 0.0));
  
  
  Masse* ptr1 = &c1;
  Masse* ptr2 = &c2;
 
  
  vector<Masse*> contraintes = {ptr1, ptr2};
  
  
  
  //Tissus:
  
 
  TissuRectangle test1(0.25,						    //masse
					  Vecteur3D(0.0, 10.0, 2.0), 	//l
					  Vecteur3D(20.0, 0.0, 0.0),	//L
					  Vecteur3D(-10.0, 0.0, -2.0),	//origine
					  0.15,						//coefficient de frottement
					  1.0,						//densité de masses
					  80,						    //coefficient ressort
					  1.0);						//longueur ressorts
  
  
  TissuRectangle test2(0.25,						    //masse
					  Vecteur3D(0.0, 10.0, 10.0), 	//l
					  Vecteur3D(20.0, 0.0, 0.0),	//L
					  Vecteur3D(-10.0, 10.5, 0.5),	//origine
					  0.15,						//coefficient de frottement
					  1.0,						//densité de masses
					  80,						    //coefficient ressort
					  1.0);						//longueur ressorts
  
  

  Tissu* ptr_test1 = &test1;
  Tissu* ptr_test2 = &test2;
   
  
  test1.accroche(3);
  test1.accroche(1);
  
  test2.accroche(3);
  test2.accroche(2);
  test2.accroche(1);
  
  
  vector<Tissu*> init({ptr_test1, ptr_test2});
  
  TissuCompose test3(init, 1.0, 80);
  
  Tissu* ptr_test3 = &test3;
  
  init.clear();
  init = {ptr_test3};
  
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
