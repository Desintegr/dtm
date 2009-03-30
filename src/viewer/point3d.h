#ifndef POINT3D_H
#define POINT3D_H

class Point3d
{
public:
  /**
   * Constructeur de point 3D
   *
   * @param x la coordonnée x
   * @param y la coordonnée y
   * @param z la coordonnée z
   */
  Point3d(const float x=0,
          const float y=0,
          const float z=0);

  /**
   * Retourne la coordonnée x
   */
  float x() const;

  /**
   * Retourne la coordonnée y
   */
  float y() const;

  /**
   * Retourne la coordonnée z
   */
  float z() const;

  /**
   * Modifie la coordonnée x
   *
   * @param x la nouvelle valeur de x
   */
  void setX(const float x);

  /**
   * Modifie la coordonnée y
   *
   * @param y la nouvelle valeur de y
   */
  void setY(const float y);

  /**
   * Modifie la coordonnée z
   *
   * @param z la nouvelle valeur de z
   */
  void setZ(const float z);

  /**
   * Opérateur +=
   */
  Point3d & operator+=(const Point3d & p);

  /**
   * Opérateur +
   */
  Point3d operator+(const Point3d & p) const;

  /**
   * Opérateur -=
   */
  Point3d & operator-=(const Point3d & p);

  /**
   * Opérateur -
   */
  Point3d operator-(const Point3d & p) const;

  /**
   * Opérateur *=
   */
  Point3d & operator*=(const float f);

  /**
   * Opérateur *
   */
  Point3d operator*(const float f) const;

  /**
   * Opérateur /=
   */
  Point3d & operator/=(const float f);

  /**
   * Opérateur /
   */
  Point3d operator/(const float f) const;

  /**
   * Produit vectoriel
   */
  Point3d cross(const Point3d &p) const;

  /**
   * Normalise le point 3D
   */
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
