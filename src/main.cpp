#include <QApplication>

#include "dtm_widget.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  DTMWidget dtm;
  dtm.show();

  return app.exec();
}
