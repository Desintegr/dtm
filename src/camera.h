#ifndef CAMERA_H
#define CAMERA_H

#include "point3d.h"

class Camera {

  private:
    static const double PI = 3.14159265358979323846264338327950288419717;
    static const double MOUSESENS = 0.2;
    static const double KEYSENS = 0.1;

  private:
    Point3d m_position;
    Point3d m_target;
    Point3d m_forward;
    Point3d m_left;

    double m_phi;
    double m_theta;

  public:
    Camera();

    inline const Point3d& position() const {
      return m_position;
    }
    inline const Point3d& target() const {
      return m_target;
    }

    void mouseMove(const int x, const int y);
    void keyPress(const int key);
    void wheelUp();
    void wheelDown();

  private:
    void update();

};

#endif
