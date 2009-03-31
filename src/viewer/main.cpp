#include "opengl_scene.h"

#include <QtGui>

#include <iostream>

int main(int argc, char *argv[])
{
  if(argc < 2) {
    std::cerr << "Error: no input file given" << std::endl;
    return EXIT_FAILURE;
  }

  if(argc > 2) {
    std::cerr << "Error: too many arguments" << std::endl;
    return EXIT_FAILURE;
  }

  QApplication app(argc, argv);
  QDir::setCurrent(QFileInfo(argv[0]).absolutePath());
  OpenGLScene scene(argv[1]);
  scene.show();

  return app.exec();
}
