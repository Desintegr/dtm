#ifndef CAMERA_H
#define CAMERA_H

#include <QHash>

#include "point3d.h"

class Camera {

  public:
    Camera();

    void mouseMove(const int x, const int y);
    void keyPress(const int key, const bool state);
    void wheel(const bool dir);

    void look() const;
    void animate(const uint step);

  private:
    static const float PI = 3.1415926535;
    static const float SENSITIVITY = 0.2;
    static const float SPEED = 0.05;
    static const uint BOOST = 10;
    static const uint WHEELTIME = 250;

    Point3d m_position;
    Point3d m_target;
    Point3d m_forward;
    Point3d m_left;

    float m_phi;
    float m_theta;

    QHash<const int, bool> m_keystates;

    bool m_wheelactive;
    uint m_wheeltime;
    int m_wheeldir;

  private:
    void vectorFromAngles();

};

#endif
