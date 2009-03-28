#include "point3d.h"

#include <cmath>

Point3d::Point3d(const float x, const float y, const float z):
  m_x(x),
  m_y(y),
  m_z(z)
{
}

Point3d & Point3d::operator+=(const Point3d &p)
{
  m_x += p.x();
  m_y += p.y();
  m_z += p.z();
  return *this;
}

Point3d Point3d::operator+(const Point3d &p) const
{
  return Point3d(*this) += p;
}

Point3d & Point3d::operator-=(const Point3d &p)
{
  m_x -= p.x();
  m_y -= p.y();
  m_z -= p.z();
  return *this;
}

Point3d Point3d::operator-(const Point3d &p) const
{
  return Point3d(*this) -= p;
}

Point3d & Point3d::operator*=(const float f)
{
  m_x *= f;
  m_y *= f;
  m_z *= f;
  return *this;
}

Point3d Point3d::operator*(const float f) const
{
  return Point3d(*this) *= f;
}

Point3d & Point3d::operator/=(const float f)
{
  m_x /= f;
  m_y /= f;
  m_z /= f;
  return *this;
}

Point3d Point3d::operator/(const float f) const
{
  return Point3d(*this) /= f;
}

Point3d Point3d::cross(const Point3d &p) const
{
  return Point3d(m_y * p.z() - m_z * p.y(),
      m_z * p.x() - m_x * p.z(),
      m_x * p.y() - m_y * p.x());
}

Point3d & Point3d::normalize()
{
  const float r = 1. / sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
  m_x *= r;
  m_y *= r;
  m_z *= r;
  return *this;
}
