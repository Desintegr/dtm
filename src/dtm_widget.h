#ifndef DTM_WIDGET_H
#define DTM_WIDGET_H

#include <QGLWidget>
#include <QTimer>

#include "camera.h"
#include "dtm.h"

class DTMWidget: public QGLWidget {
  Q_OBJECT

  private:
    static const int FPS = 60;

  public:
    DTMWidget(QWidget* parent=0);

  protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void wheelEvent(QWheelEvent* e);
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);

  private:
    Camera camera;
    DTM dtm;

    QTimer t;
    int current;
    int last;

  private slots:
    void update();
};

#endif
