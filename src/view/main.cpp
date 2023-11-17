#include <QApplication>

#include "mainwindow.h"
#include "widget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  MainWindow z;
  z.show();
  return a.exec();
}
