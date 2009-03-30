#include "flood.h"

#include <QApplication>

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
  Flood flood(argv[1]);

  return app.exec();
}
