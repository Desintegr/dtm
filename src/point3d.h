#ifndef POINT3D_H
#define POINT3D_H

class Point3d {
  public:
    float x;
    float y;
    float z;

    Point3d(float _x=0, float _y=0, float _z=0);

    Point3d& operator+=(const Point3d& p);
    Point3d operator+(const Point3d& p) const;

    Point3d& operator-=(const Point3d& p);
    Point3d operator-(const Point3d& p) const;

    Point3d& operator*=(const float f);
    Point3d operator*(const float f) const;

    Point3d& operator/=(const float f);
    Point3d operator/(const float f) const;

    Point3d cross(const Point3d& p) const;
    Point3d normalize();
};

#endif
