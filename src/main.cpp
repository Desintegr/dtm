#include "opengl_scene.h"

#include <QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
  if(argc < 2) {
    std::cout << "Error: no input file given" << std::endl;
    return EXIT_FAILURE;
  }

  if(argc > 2) {
    std::cout << "Error: too many arguments" << std::endl;
    return EXIT_FAILURE;
  }

  QApplication app(argc, argv);

  OpenGLScene scene(argv[1]);
  scene.show();

  return app.exec();
}
