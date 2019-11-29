#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QTime>            // Classe pour gérer le temps
#include <QLabel>
#include "vue_opengl.h"
#include "Systeme.h"

class GLWidget : public QGLWidget {
	
public:
  GLWidget(std::vector<Tissu*>& entree, std::vector<int> & i, std::vector<Masse*> & contr, QWidget* parent = nullptr)
    : QGLWidget(parent), c(entree, i, contr, &vue)
  {}
  virtual ~GLWidget() {}

private:
  // Les 3 méthodes clés de la classe QGLWidget à réimplémenter
  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;
  void ecrire() const;

  // Méthodes de gestion d'évènements
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void timerEvent(QTimerEvent* event)  override;
  virtual void mousePressEvent(QMouseEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent* event)  override;

  // Méthodes de gestion interne
  void pause();

  // Vue : ce qu'il faut donner au contenu pour qu'il puisse se dessiner sur la vue
  VueOpenGL vue;

  // Timer
  int timerId;
  
  // Label
  QLabel *label = new QLabel;
  bool l = true;
  
  // pour faire évoluer les objets avec le bon "dt"
  QTime chronometre;
  
  // position souris
  QPoint lastMousePosition;

  // objets à dessiner, faire évoluer
  Systeme c;
};

#endif // GLWIDGET_H
