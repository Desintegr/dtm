#include "camera.h"

#include <cmath>

#include <QtGui>
#include <QtOpenGL>

Camera::Camera() {
  m_phi = 0;
  m_theta = 0;
  m_wheelactive = false;
}

void Camera::vectorFromAngles() {
  if(m_phi>89)
    m_phi = 89;
  else if(m_phi<-89)
    m_phi = -89;

  const float r_tmp = cos(m_phi*PI/180);
  m_forward.setZ(sin(m_phi*PI/180));
  m_forward.setX(r_tmp*cos(m_theta*PI/180));
  m_forward.setY(r_tmp*sin(m_theta*PI/180));

  const Point3d up(0, 0, 1);
  m_left = up.cross(m_forward);
  m_left.normalize();
}

void Camera::mouseMove(const int x, const int y) {
  m_theta -= x * SENSITIVITY;
  m_phi -= y * SENSITIVITY;

  vectorFromAngles();

  m_target = m_position + m_forward;
}

void Camera::keyPress(const int key, const bool state) {
  m_keystates[key] = state;
}

void Camera::wheel(const bool dir) {
  m_wheelactive = true;
  m_wheeltime = WHEELTIME;
  m_wheeldir = (dir?1:-1);
}

void Camera::look() const {
  gluLookAt(m_position.x(), m_position.y(), m_position.z(),
            m_target.x(), m_target.y(), m_target.z(),
            0, 0, 1);
}

void Camera::animate(const uint step) {

  // orientation

  if(m_keystates[Qt::Key_Up]) {
    m_phi += (SPEED/2*step);
    vectorFromAngles();
  }
  if(m_keystates[Qt::Key_Down]) {
    m_phi -= (SPEED/2*step);
    vectorFromAngles();
  }
  if(m_keystates[Qt::Key_Left]) {
    m_theta += (SPEED/2*step);
    vectorFromAngles();
  }
  if(m_keystates[Qt::Key_Right]) {
    m_theta -= (SPEED/2*step);
    vectorFromAngles();
  }

  // position

  const float realspeed = (m_keystates[Qt::Key_Shift]?10*SPEED:SPEED);

  if(m_keystates[Qt::Key_Z])
    m_position += m_forward*(realspeed*step);
  if(m_keystates[Qt::Key_S])
    m_position -= m_forward*(realspeed*step);
  if(m_keystates[Qt::Key_Q])
    m_position += m_left*(realspeed*step);
  if(m_keystates[Qt::Key_D])
    m_position -= m_left*(realspeed*step);

  // hauteur

  if(m_keystates[Qt::Key_PageUp])
    m_position += Point3d(0, 0, realspeed*step);
  if(m_keystates[Qt::Key_PageDown])
    m_position -= Point3d(0, 0, realspeed*step);

  // molette

  if(m_wheelactive) {
    if (step>m_wheeltime)
      m_wheelactive = false;
    else
      m_wheeltime -= step;

    m_position += Point3d(0, 0, m_wheeldir*realspeed*step);
  }

  m_target = m_position + m_forward;
}

void Camera::clearKeyStates() {
  m_keystates.clear();
}
