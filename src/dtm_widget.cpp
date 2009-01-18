#include "dtm_widget.h"

#include <QtGui>

DTMWidget::DTMWidget(QWidget* parent):
  QGLWidget(parent),
  current(0),
  last(0) {
  resize(800, 600);
  setAutoBufferSwap(true);

  refresh.setInterval(1000/FPS);
  refresh.setSingleShot(true);
  connect(&refresh, SIGNAL(timeout()), this, SLOT(update()));
  refresh.start();

  ticks.start();

  //dtm.load("data/grd_618000_6755000_2.grd");
  dtm.load("data/test.grd");
  dtm.test();
}

void DTMWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void DTMWidget::resizeGL(const int w, const int h) {
  glViewport(0, 0, w, h);
  gluPerspective(45, float(w/h), 0.001, 1000);
}

void DTMWidget::paintGL() {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  camera.look();

  dtm.draw();

  //glBegin(GL_TRIANGLES);
  //glColor3f(1, 1, 1);
  //glVertex3f(0, 0, 0.1);
  //glVertex3f(0, 1, 0.1);
  //glVertex3f(1, 0, 0.4);
  //glEnd();

  //glBegin(GL_TRIANGLE_FAN);
  //glColor3f(0, 0, 1);
  //glVertex3f(0, 1, 0);
  //glVertex3f(0.5, 0, -0.5);
  //glVertex3f(-0.5, 0, -0.5);
  //glEnd();

  //glBegin(GL_TRIANGLE_FAN);
  //glColor3f(0, 1, 0);
  //glVertex3f(0, 1, 0);
  //glVertex3f(-0.5, 0, -0.5);
  //glVertex3f(-0.5, 0, 0.5);
  //glEnd();

  //glBegin(GL_TRIANGLE_FAN);
  //glColor3f(0, 1, 1);
  //glVertex3f(0, 1, 0);
  //glVertex3f(-0.5, 0, 0.5);
  //glVertex3f(0.5, 0, 0.5);
  //glEnd();

  //glBegin(GL_TRIANGLE_FAN);
  //glColor3f(1, 0, 0);
  //glVertex3f(0, 1, 0);
  //glVertex3f(0.5, 0, 0.5);
  //glVertex3f(0.5, 0, -0.5);
  //glEnd();
}

void DTMWidget::mouseMoveEvent(QMouseEvent* e) {
  if(e->buttons() == Qt::LeftButton) {
    QCursor::setPos(QPoint(mapToGlobal(QPoint(width()/2, height()/2))));

    int relx = e->globalX() - QCursor::pos().x();
    int rely = e->globalY() - QCursor::pos().y();

    camera.mouseMove(relx, rely);
  }
}

void DTMWidget::mousePressEvent(QMouseEvent* e) {
  if(e->button() == Qt::LeftButton) {
    setCursor(QCursor(Qt::BlankCursor));
    QCursor::setPos(QPoint(mapToGlobal(QPoint(width()/2, height()/2))));
  }
}

void DTMWidget::mouseReleaseEvent(QMouseEvent* e) {
  if(e->button() == Qt::LeftButton)
    setCursor(QCursor(Qt::ArrowCursor));
}

void DTMWidget::wheelEvent(QWheelEvent* e) {
  if(e->orientation() == Qt::Vertical)
    camera.wheel(e->delta() > 0);
}

void DTMWidget::keyPressEvent(QKeyEvent* e) {
  camera.keyPress(e->key(), true);
}

void DTMWidget::keyReleaseEvent(QKeyEvent* e) {
  camera.keyPress(e->key(), false);
}

void DTMWidget::update() {
  current += ticks.restart();
  const uint elapsed = current - last;
  last = current;

  QTime ti;
  ti.start();

  camera.animate(elapsed);
  updateGL();

  const uint stop = current + ti.elapsed();
  if ((stop - last) < 1000/FPS)
    refresh.setInterval(1000/FPS - (stop - last));
  else
    refresh.setInterval(0);

  refresh.start();
}
