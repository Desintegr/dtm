#ifndef DTM_WIDGET_H
#define DTM_WIDGET_H

#include <QGLWidget>
#include <QTime>
#include <QTimer>

#include <QPixmap> // TODO

#include "camera.h"
#include "dtm.h"

class OpenGLScene: public QGLWidget {
  Q_OBJECT

  private:
    static const uint FPS = 50;

  public:
    OpenGLScene(QString fileName, QWidget* parent=0);

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
    void enterEvent(QEvent* e);
    void leaveEvent(QEvent* e);

  private:
    Camera camera;
    DTM dtm;

    QTimer refresh;
    QTime ticks;
    uint current;
    uint last;

    QPixmap texture;

  private slots:
    void update();
};

#endif
