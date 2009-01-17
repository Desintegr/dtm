#ifndef POINT3D_H
#define POINT3D_H

class Point3d {

  private:
    float m_x;
    float m_y;
    float m_z;

  public:
    Point3d(const float x=0,
            const float y=0,
            const float z=0);

    inline float x() const {
      return m_x;
    }

    inline void setX(const float x) {
      m_x = x;
    }

    inline float y() const {
      return m_y;
    }

    inline void setY(const float y) {
      m_y = y;
    }

    inline float z() const {
      return m_z;
    }
    
    inline void setZ(const float z) {
      m_z = z;
    }

    Point3d& operator+=(const Point3d& p);
    Point3d operator+(const Point3d& p) const;

    Point3d& operator-=(const Point3d& p);
    Point3d operator-(const Point3d& p) const;

    Point3d& operator*=(const float f);
    Point3d operator*(const float f) const;

    Point3d& operator/=(const float f);
    Point3d operator/(const float f) const;

    Point3d cross(const Point3d& p) const;
    Point3d normalize() const;
};

#endif
