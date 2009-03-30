#ifndef POINT3D_H
#define POINT3D_H

class Point3d
{
public:
  Point3d(const float x=0,
          const float y=0,
          const float z=0);

  float x() const;
  float y() const;
  float z() const;

  void setX(const float x);
  void setY(const float y);
  void setZ(const float z);

  Point3d & operator+=(const Point3d & p);
  Point3d operator+(const Point3d & p) const;

  Point3d & operator-=(const Point3d & p);
  Point3d operator-(const Point3d & p) const;

  Point3d & operator*=(const float f);
  Point3d operator*(const float f) const;

  Point3d & operator/=(const float f);
  Point3d operator/(const float f) const;

  Point3d cross(const Point3d & p) const;
  Point3d & normalize();

private:
  float m_x;
  float m_y;
  float m_z;
};

inline float Point3d::x() const
{
  return m_x;
}

inline float Point3d::y() const
{
  return m_y;
}

inline float Point3d::z() const
{
  return m_z;
}
inline void Point3d::setX(const float x)
{
  m_x = x;
}

inline void Point3d::setY(const float y)
{
  m_y = y;
}

inline void Point3d::setZ(const float z)
{
  m_z = z;
}

#endif
