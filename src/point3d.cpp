#include <cmath>

#include "point3d.h"

Point3d::Point3d(float _x, float _y, float _z):
  x(_x),
  y(_y),
  z(_z) {
}


Point3d & Point3d::operator+= (const Point3d & p) {
  x += p.x;
  y += p.y;
  z += p.z;
  return *this;
}

Point3d Point3d::operator+ (const Point3d & p) const {
  return Point3d(*this) += p;
}

Point3d & Point3d::operator-= (const Point3d & p) {
  x -= p.x;
  y -= p.y;
  z -= p.z;
  return *this;
}

Point3d Point3d::operator- (const Point3d & p) const {
  return Point3d(*this) -= p;
}

Point3d & Point3d::operator*= (const float f) {
  x *= f;
  y *= f;
  z *= f;
  return *this;
}

Point3d Point3d::operator* (const float f) const {
    return Point3d(*this) *= f;
}

Point3d & Point3d::operator/= (const float f) {
  x /= f;
  y /= f;
  z /= f;
  return *this;
}

Point3d Point3d::operator/ (const float f) const {
    return Point3d(*this) /= f;
}

Point3d Point3d::cross(const Point3d & p) const {
   return Point3d(y * p.z - z * p.y, 
                  z * p.x - x * p.z,
                  x * p.y - y * p.x);
}

Point3d Point3d::normalize() {
  float r = 1. / sqrt(x * x + y * y + z * z);
  return Point3d(x * r, y * r, z * r);
}
