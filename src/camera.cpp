#include "camera.h"

#include <cmath>
#include <QtGui>

Camera::Camera():
  m_phi(0),
  m_theta(0) {
}

void Camera::mouseMove(const int x, const int y) {
  m_theta += x * MOUSESENS;
  m_phi += y * MOUSESENS;

  const Point3d up(0,0,1);

  if(m_phi > 89)
    m_phi = 89;
  else if(m_phi < -89)
    m_phi = -89;

  const float r_tmp = cos(m_phi * PI/180);
  m_forward.setZ(sin(m_phi * PI/180));
  m_forward.setX(r_tmp * cos(m_theta * PI/180));
  m_forward.setY(r_tmp * sin(m_theta * PI/180));

  m_left = up.cross(m_forward);
  m_left.normalize();

  update();
}

void Camera::keyPress(const int key) {
  switch(key) {
    case Qt::Key_Z:
      m_position += m_forward * KEYSENS;
      break;
    case Qt::Key_S:
      m_position -= m_forward * KEYSENS;
      break;
    case Qt::Key_Q:
      m_position += m_left * KEYSENS;
      break;
    case Qt::Key_D:
      m_position -= m_left * KEYSENS;
      break;
  }

  update();
}
  
void Camera::wheelUp() {
  const Point3d up(0,0,1);
  m_position += up * KEYSENS;

  update();
}

void Camera::wheelDown() {
  const Point3d up(0,0,1);
  m_position -= up * KEYSENS;

  update();
}

void Camera::update() {
  m_target = m_position + m_forward;
}
