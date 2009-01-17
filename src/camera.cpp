#include "camera.h"

#include <cmath>
#include <QtGui>

Camera::Camera() {
  phi = 0;
  theta = 0;
}

void Camera::mouseMove(int x, int y) {
  theta += x * mousesens;
  phi += y * mousesens;

  Point3d up(0,0,1);

  if(phi > 89)
    phi = 89;
  else if(phi < -89)
    phi = -89;

  float r_tmp = cos(phi * pi/180);
  forward.z = sin(phi * pi/180);
  forward.x = r_tmp * cos(theta * pi/180);
  forward.y = r_tmp * sin(theta * pi/180);

  left = up.cross(forward);
  left.normalize();

  update();
}

void Camera::keyPress(int key) {
  switch(key) {
    case Qt::Key_Z:
      position += forward * keysens;
      break;
    case Qt::Key_S:
      position -= forward * keysens;
      break;
    case Qt::Key_Q:
      position += left * keysens;
      break;
    case Qt::Key_D:
      position -= left * keysens;
      break;
  }

  update();
}
  
void Camera::wheelUp() {
  Point3d up(0,0,1);
  position += up * keysens;

  update();
}

void Camera::wheelDown() {
  Point3d up(0,0,1);
  position -= up * keysens;

  update();
}

void Camera::update() {
  target = position + forward;
}
