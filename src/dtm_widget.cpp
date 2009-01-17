#include "dtm_widget.h"

#include <QtGui>

#include "camera.h"

DTMWidget::DTMWidget(QWidget *parent):
  QGLWidget(parent) {
  resize(800, 600);
  c = new Camera();
}

void DTMWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
}

void DTMWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  gluPerspective(45, float(w/h), 0.001, 1000);
}

void DTMWidget::paintGL() {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(
    c->position.x, c->position.y, c->position.z,
    c->target.x, c->target.y, c->target.z,
    0, 0, 1
  );

  //if(m->x != -1 && m->y != -1)
  //  glutWarpPointer(m->x,m->y);

  //drawPyramide();
  //drawDTM();


  glBegin(GL_TRIANGLE_FAN);
  glColor3f(0, 0, 1);
  glVertex3f(0, 1, 0);
  glVertex3f(0.5, 0, -0.5);
  glVertex3f(-0.5, 0, -0.5);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  glColor3f(0, 1, 0);
  glVertex3f(0, 1, 0);
  glVertex3f(-0.5, 0, -0.5);
  glVertex3f(-0.5, 0, 0.5);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  glColor3f(0, 1, 1);
  glVertex3f(0, 1, 0);
  glVertex3f(-0.5, 0, 0.5);
  glVertex3f(0.5, 0, 0.5);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  glColor3f(1, 0, 0);
  glVertex3f(0, 1, 0);
  glVertex3f(0.5, 0, 0.5);
  glVertex3f(0.5, 0, -0.5);
  glEnd();

}

void DTMWidget::mouseMoveEvent(QMouseEvent *e) {
  QCursor::setPos(QPoint(mapToGlobal(QPoint(width()/2, height()/2))));

  int relx = QCursor::pos().x() - e->globalX();
  int rely = QCursor::pos().y() - e->globalY();

  c->mouseMove(relx, rely);
  updateGL();
}

void DTMWidget::mousePressEvent(QMouseEvent *) {
  QCursor::setPos(QPoint(mapToGlobal(QPoint(width()/2, height()/2))));

  // TODO cacher le pointeur
}


void DTMWidget::wheelEvent(QWheelEvent *e) {
  if(e->orientation() == Qt::Vertical && e->delta() > 0) 
    c->wheelUp();
  else if(e->orientation() == Qt::Vertical && e->delta() < 0) 
    c->wheelDown();

  updateGL();
}

void DTMWidget::keyPressEvent(QKeyEvent *e) {
  c->keyPress(e->key());
  updateGL();
}
