#include "main_window.h"

#include <QtGui>

#include "opengl_scene.h"

MainWindow::MainWindow(QWidget* parent):
  QMainWindow(parent) {
  scene = NULL;

  resize(800, 600);
  setWindowTitle("Digital Terrain Model");
  createActions();
  createMenus();
}

void MainWindow::createActions() {
  loadSceneAction = new QAction("&Load...", this);
  connect(loadSceneAction, SIGNAL(triggered()), this, SLOT(loadScene()));

  closeSceneAction = new QAction("&Close", this);
  connect(closeSceneAction, SIGNAL(triggered()), this, SLOT(closeScene()));
  closeSceneAction->setDisabled(true);

  quitAction = new QAction("&Quit", this);
  connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenus() {
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(loadSceneAction);
  fileMenu->addAction(closeSceneAction);
  fileMenu->addSeparator();
  fileMenu->addAction(quitAction);
}

void MainWindow::loadScene() {
  QString fileName = QFileDialog::getOpenFileName(this,
                                                  tr("Open File"),
                                                  QDir::currentPath(),
                                                  tr("DTM files (*.grd)"));

  if(!fileName.isEmpty()) {
    scene = new OpenGLScene(fileName, this);
    setCentralWidget(scene);

    closeSceneAction->setEnabled(true);
  }
}

void MainWindow::closeScene() {
  if(scene) {
    scene->close();
    delete scene;
    closeSceneAction->setDisabled(true);
  }
}
