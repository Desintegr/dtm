#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class OpenGLScene;

class MainWindow: public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent=0);

private:
  QMenu *fileMenu;

  QAction *loadSceneAction;
  QAction *closeSceneAction;
  QAction *quitAction;

  OpenGLScene *scene;

private:
  void createMenus();
  void createActions();

private slots:
  void loadScene();
  void closeScene();
};

#endif
