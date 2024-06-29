#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  data_t some_data;
  MainWindow w(nullptr, some_data);
  w.show();
  return a.exec();
}
