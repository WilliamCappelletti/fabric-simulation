#include <QApplication>
#include "glwidget.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  
  
  //Contraintes:
  
  
  Crochet c1(Vecteur3D(0.0, 15.0, 10.0),
             Vecteur3D(1/3.0, 0.0, 0.0),
             Vecteur3D(0.0, 0.0, 0.0));
       
  Masse* ptr1 = &c1;
  
  Crochet c2(Vecteur3D(0.0, 10.0, 10.0),
             Vecteur3D(1/3.0, 0.0, 0.0),
             Vecteur3D(0.0, 1.0, 0.0));
       
  Masse* ptr2 = &c2;
  
  Crochet c3(Vecteur3D(0.0, 5.0, 10.0),
             Vecteur3D(1/3.0, 0.0, 0.0),
             Vecteur3D(0.0, 2.0, 0.0));
       
  Masse* ptr3 = &c3;
  
  Crochet c4(Vecteur3D(0.0, 0.0, 10.0),
             Vecteur3D(1/3.0, 0.0, 0.0),
             Vecteur3D(0.0, 3.0, 0.0));
       
  Masse* ptr4 = &c4;
  
  Crochet c5(Vecteur3D(0.0, -5.0, 10.0),
             Vecteur3D(1/3.0, 0.0, 0.0),
             Vecteur3D(0.0, 4.0, 0.0));
       
  Masse* ptr5 = &c5;
  
  Crochet c6(Vecteur3D(0.0, -10.0, 10.0),
             Vecteur3D(1/3.0, 0.0, 0.0),
             Vecteur3D(0.0, 5.0, 0.0));
       
  Masse* ptr6 = &c6;
  
  Crochet c7(Vecteur3D(0.0, -15.0, 10.0),
             Vecteur3D(1/3.0, 0.0, 0.0),
             Vecteur3D(0.0, 6.0, 0.0));
       
  Masse* ptr7 = &c7;
  
  
  vector<Masse*> contraintes = {ptr1, ptr2, ptr3, ptr4, ptr5, ptr6, ptr7};
  
  
  //Tissus:
  
  TissuRectangle test1(0.25,						    //masse
					  Vecteur3D(0.0, 30.0, 0.0), 	//l
					  Vecteur3D(0.0, 0.0, -12.0),	//L
					  Vecteur3D(0.0, -15.0, 10.0),	//origine
					  0.5,						//coefficient de frottement
					  1.5,						//densité de masses
					  100,						    //coefficient ressort
					  1/1.5);						//longueur ressorts
  
  
  Tissu* ptr_test1 = &test1;
  
  
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
