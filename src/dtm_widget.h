#ifndef DTM_WIDGET_H
#define DTM_WIDGET_H

#include <QGLWidget>

#include "camera.h"

class DTMWidget: public QGLWidget {
  Q_OBJECT

  public:
    DTMWidget(QWidget *parent=0);

  protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void keyPressEvent(QKeyEvent *e);

  private:
    Camera c;
};

#endif
