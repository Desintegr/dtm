#ifndef CAMERA_H
#define CAMERA_H

#include "point3d.h"

class Camera {

  public:
    static const double pi = 3.14159265358979323846264338327950288419717;
    static const double mousesens = 0.2;
    static const double keysens = 0.1;

    // TODO
    Point3d position;
    Point3d target;
    Point3d forward;
    Point3d left;

    double phi;
    double theta;

  public:
    Camera();

    void mouseMove(int x, int y);
    void keyPress(int key);
    void wheelUp();
    void wheelDown();
    void update();

};

#endif
