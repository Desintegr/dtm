#ifndef CAMERA_H
#define CAMERA_H

#include <QHash>

#include "point3d.h"

class Camera {

  private:
    static const float PI = 3.1415926535;
    static const float SENSITIVITY = 0.2;
    static const float SPEED = 0.002;
    static const int WHEELTIME = 100;

  private:
    Point3d m_position;
    Point3d m_target;
    Point3d m_forward;
    Point3d m_left;

    float m_phi;
    float m_theta;

    QHash<const int, bool> m_keystates;

    bool m_wheelactive;
    int m_wheeltime;
    int m_wheeldir;

  public:
    Camera();

    void mouseMove(const int x, const int y);
    void keyPress(const int key, const bool state);
    void wheel(const bool dir);

    void look() const;
    void animate(int step);

};

#endif