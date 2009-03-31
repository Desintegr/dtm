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
  /**
   * Constructeur de scène OpenGL
   *
   * @param filename fichier de terrain
   * @param parent widget parent
   */
  OpenGLScene(QString filename, QWidget *parent=0);

  /**
   * Desctructeur de scène OpenGL
   */
  virtual ~OpenGLScene();

protected:
  /**
   * Initialisation la scène OpenGL
   */
  void initializeGL();

  /**
   * Redimensionnement de la scène OpenGL
   */
  void resizeGL(int w, int h);

  /**
   * Dessin de la scène OpenGL
   */
  void paintGL();

  /**
   * Événement de déplacement de souris
   */
  void mouseMoveEvent(QMouseEvent *e);

  /**
   * Événement de bouton de souris pressé
   */
  void mousePressEvent(QMouseEvent *e);

  /**
   * Événement de bouton de souris relaché
   */
  void mouseReleaseEvent(QMouseEvent *e);

  /**
   * Événement de déplacement de molette
   */
  void wheelEvent(QWheelEvent *e);

  /**
   * Événement de touche de clavier pressée
   */
  void keyPressEvent(QKeyEvent *e);

  /**
   * Événement de touche de clavier relachée
   */
  void keyReleaseEvent(QKeyEvent *e);

  /**
   * Événement de curseur entrant dans la fenêtre
   */
  void enterEvent(QEvent *e);

  /**
   * Événement de curseur sortant de la fenêtre
   */
  void leaveEvent(QEvent *e);

private slots:
  /**
   * Demande la mise à jour de la scène
   */
  void update();

private:
  static const uint FPS = 50;

  const QString m_filename;

  Camera *m_camera;
  DTM *m_dtm;
  Light *m_light;
  Water *m_water;

  FlowVRThread *m_flowVRThread;

  QTimer m_refresh;
  QTime m_ticks;
  uint m_current;
  uint m_last;
};

#endif
