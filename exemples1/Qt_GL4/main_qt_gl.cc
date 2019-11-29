#include <QApplication>
#include "glwidget.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  
  
  //Contraintes:
  
  Crochet c1(Vecteur3D(0.0, 0.0, 0.0),
             Vecteur3D(4.5, 0.0, 0.0),
             Vecteur3D(0.0, 0.0, 0.0));
             
      
  Masse* ptr1 = &c1;
    
  vector<Masse*> contraintes = {ptr1};
  
  
  //Tissus:
  
	TissuDisque test1(0.15,							//masse
						Vecteur3D(0.0, 0.0, 0.0),	//centre
						Vecteur3D(0.0, 0.0, 9),	//radius*normale
						0.3,						//pas
						0.25,						//cf
						100,						//raideur des ressorts
						15);						//(angle)
	
	TissuDisque test2(0.15,							//masse
						Vecteur3D(0.0, 0.0, -3.0),	//centre
						Vecteur3D(0.0, 0.0, 8.0),	//radius*normale
						0.3,						//pas
						0.25,						//cf
						100,						//raideur des ressorts
						15);						//(angle)
	
	
	
  Tissu* ptr_test1 = &test1;
  Tissu* ptr_test2 = &test2;
  
  test1.couper(Vecteur3D(0.0, 0.0, 0.0), 4.0);
  test2.couper(Vecteur3D(0.0, 0.0, 0.0), 4.0);
  
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
