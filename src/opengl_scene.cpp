#include "opengl_scene.h"

#include <QtGui>

#include "point3d.h" // TODO

OpenGLScene::OpenGLScene(QString fileName, QWidget* parent):
  QGLWidget(parent),
  current(0),
  last(0) {
  refresh.setInterval(1000/FPS);
  refresh.setSingleShot(true);
  connect(&refresh, SIGNAL(timeout()), this, SLOT(update()));
  refresh.start();

  ticks.start();

  dtm.load(fileName);
}

void OpenGLScene::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  dtm.initVBO();

  float lmodel_ambient[]={0.5,0.5,0.5,1.0};
  float mat_specular[] = {1.0,1.0,1.0,1.0};
  float mat_shininess[] = { 50. };

  glShadeModel (GL_SMOOTH);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  //texture = QPixmap("data/med2.png");
  //glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
  //bindTexture(texture, GL_TEXTURE_2D);

  //glEnable(GL_TEXTURE_2D);

}

void OpenGLScene::resizeGL(const int w, const int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, float(w/h), 0.001, 10000);
}

#include <QtDebug>
void OpenGLScene::paintGL() {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  camera.look();

  //GLfloat coord_tex[] = {
  //  0.0f, 0.0f, 
  //  500.0f, 0.0f,
  //  500.0f, 500.0f, 
  //  0.0f, 500.0f
  //} ;

  //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  //glTexCoordPointer(2,GL_FLOAT,0,coord_tex);

  dtm.draw();

  float light_position[] = {dtm.m_ncols/2, dtm.m_nrows/2, dtm.maxz, 1};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  swapBuffers();
}

void OpenGLScene::mouseMoveEvent(QMouseEvent* e) {
  if(e->buttons() == Qt::LeftButton) {
    QCursor::setPos(QPoint(mapToGlobal(QPoint(width()/2, height()/2))));

    int relx = e->globalX() - QCursor::pos().x();
    int rely = e->globalY() - QCursor::pos().y();

    camera.mouseMove(relx, rely);
  }
}

void OpenGLScene::mousePressEvent(QMouseEvent* e) {
  if(e->button() == Qt::LeftButton) {
    setCursor(QCursor(Qt::BlankCursor));
    QCursor::setPos(QPoint(mapToGlobal(QPoint(width()/2, height()/2))));
  }
}

void OpenGLScene::mouseReleaseEvent(QMouseEvent* e) {
  if(e->button() == Qt::LeftButton)
    setCursor(QCursor(Qt::ArrowCursor));
}

void OpenGLScene::wheelEvent(QWheelEvent* e) {
  if(e->orientation() == Qt::Vertical)
    camera.wheel(e->delta() > 0);
}

void OpenGLScene::keyPressEvent(QKeyEvent* e) {
  if(e->key() == Qt::Key_Escape)
    releaseKeyboard();
  else
    camera.keyPress(e->key(), true);
}

void OpenGLScene::keyReleaseEvent(QKeyEvent* e) {
  camera.keyPress(e->key(), false);
}

void OpenGLScene::enterEvent(QEvent*) {
  grabKeyboard();
}

void OpenGLScene::leaveEvent(QEvent*) {
  releaseKeyboard();
}

void OpenGLScene::update() {
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
