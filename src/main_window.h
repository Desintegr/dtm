#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class OpenGLScene;

class MainWindow: public QMainWindow {
  Q_OBJECT

  private:
    QMenu* fileMenu;

    QAction* loadSceneAction;
    QAction* closeSceneAction;
    QAction* quitAction;

    OpenGLScene* scene; 

  public:
    MainWindow(QWidget* parent=0);

  private:
    void createMenus();
    void createActions();

  private slots:
    void loadScene();
    void closeScene();

};

#endif
