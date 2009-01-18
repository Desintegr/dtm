#include "camera.h"

#include <cmath>

#include <QtGui>
#include <QtOpenGL>

Camera::Camera():
  m_phi(0),
  m_theta(0),
  m_wheelactive(false) {
}

void Camera::mouseMove(const int x, const int y) {
  m_theta -= x * SENSITIVITY;
  m_phi -= y * SENSITIVITY;

  if(m_phi > 89)
    m_phi = 89;
  else if(m_phi < -89)
    m_phi = -89;

  const float r_tmp = cos(m_phi * PI/180);
  m_forward.setZ(sin(m_phi * PI/180));
  m_forward.setX(r_tmp * cos(m_theta * PI/180));
  m_forward.setY(r_tmp * sin(m_theta * PI/180));

  const Point3d up(0,0,1);
  m_left = up.cross(m_forward);
  m_left.normalize();

  m_target = m_position + m_forward;
}

void Camera::keyPress(const int key, const bool state) {
  m_keystates[key] = state;
}

void Camera::wheel(const bool dir) {
  m_wheelactive = true;
  m_wheeltime = WHEELTIME;
  m_wheeldir = (dir ? 1 : -1);
}

void Camera::look() const {
  gluLookAt(m_position.x(), m_position.y(), m_position.z(),
            m_target.x(), m_target.y(), m_target.z(),
            0, 0, 1);
}

void Camera::animate(const uint step) {
  double realspeed = (m_keystates[Qt::Key_Shift]?10*SPEED:SPEED);

  if(m_keystates[Qt::Key_Z])
    m_position += m_forward * (realspeed * step);
  if(m_keystates[Qt::Key_S])
    m_position -= m_forward * (realspeed * step);
  if(m_keystates[Qt::Key_Q])
    m_position += m_left * (realspeed * step);
  if(m_keystates[Qt::Key_D])
    m_position -= m_left * (realspeed * step);

  if(m_wheelactive) {
    if (step > m_wheeltime)
      m_wheelactive = false;
    else
      m_wheeltime -= step;

    m_position += Point3d(0,0,m_wheeldir * realspeed * step);
  }

  m_target = m_position + m_forward;
}
