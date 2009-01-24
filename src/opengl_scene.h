#ifndef DTM_WIDGET_H
#define DTM_WIDGET_H

#include <QGLWidget>
#include <QTime>
#include <QTimer>
#include <QString>

class QPixmap;

class Camera;
class DTM;
class Light;

class OpenGLScene: public QGLWidget {
  Q_OBJECT

  public:
    OpenGLScene(QString fileName, QWidget* parent=0);
    ~OpenGLScene();

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
    static const uint FPS = 50;

    QString m_fileName;

    Camera* m_camera;
    DTM* m_dtm;
    Light* m_light;

    QTimer m_refresh;
    QTime m_ticks;
    uint m_current;
    uint m_last;

  private slots:
    void update();
};

#endif
