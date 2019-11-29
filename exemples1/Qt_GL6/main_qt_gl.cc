#include <QApplication>
#include "glwidget.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  
  
  //Contraintes:
  
  
  Corp c1(Vecteur3D(7.0, 11.0, 10.0),
             Vecteur3D(2.0, 0.0, 0.0),
             0.25,
             0.25,
             Vecteur3D(0.0, 0.0, 0.0));
  
  Corp c2(Vecteur3D(-9.0, -1.0, 10.0),
             Vecteur3D(2.0, 0.0, 0.0),
             0.25,
             0.25,
             Vecteur3D(0.0, 0.0, 1.0));
             
  
  Masse* ptr1 = &c1;
  Masse* ptr2 = &c2;
  
  
  vector<Masse*> contraintes = {ptr1, ptr2};
  
  
  
  //vector<Masse*> contraintes;
  
  //Tissus:
  
 
  TissuRectangle test1(0.2,						    //masse
					  Vecteur3D(0.0, 30.0, 0.0), 	//l
					  Vecteur3D(30.0, 0.0, 0.0),	//L
					  Vecteur3D(-15.0, -15.0, 0.0),	//origine
					  0.25,						//coefficient de frottement
					  1.0,						//densité de masses
					  100,						    //coefficient ressort
					  1.0);						//longueur ressorts
  
  

  Tissu* ptr_test1 = &test1;
   
  
  test1.accroche(3);
  test1.accroche(2);
  test1.accroche(1);
  test1.accroche(0);
  
  
  vector<Tissu*> init({ptr_test1});
  
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
