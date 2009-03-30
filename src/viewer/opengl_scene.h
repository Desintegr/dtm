#ifndef DTM_WIDGET_H
#define DTM_WIDGET_H

#include <QtOpenGL>

class Camera;
class DTM;
class FlowVRThread;
class Light;
class Water;

class OpenGLScene: public QGLWidget
{
  Q_OBJECT

public:
  OpenGLScene(QString fileName, QWidget *parent=0);
  virtual ~OpenGLScene();

protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

  void mouseMoveEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);
  void wheelEvent(QWheelEvent *e);
  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
  void enterEvent(QEvent *e);
  void leaveEvent(QEvent *e);

private:
  static const uint FPS = 50;

  QString m_fileName;

  Camera *m_camera;
  DTM *m_dtm;
  Light *m_light;
  Water *m_water;

  FlowVRThread *m_flowVRThread;

  QTimer m_refresh;
  QTime m_ticks;
  uint m_current;
  uint m_last;

private slots:
  void update();
};

#endif
