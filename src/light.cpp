#include "light.h"

#include <QtOpenGL>

#include "dtm.h"

Light::Light(DTM* dtm):
  m_dtm(dtm) {

  float ambient[4] = {0.5, 0.5, 0.5, 1.0};
  float specular[4] = {1.0, 1.0, 1.0, 1.0};
  float shininess[1] = {50.};

  glShadeModel (GL_SMOOTH);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void Light::set() {
  m_position[0] = (float)m_dtm->ncols()/2;
  m_position[1] = (float)m_dtm->nrows()/2;
  m_position[2] = (float)m_dtm->ncols()/2;
  m_position[3] = 1;

  glLightfv(GL_LIGHT0, GL_POSITION, m_position);
}