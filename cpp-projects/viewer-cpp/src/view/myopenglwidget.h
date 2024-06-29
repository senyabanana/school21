#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QSettings>
#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QtWidgets/QWidget>

#include "../controller/controller.h"
#include "../model/struct/struct.h"
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MyOpenGLWidget;
}
QT_END_NAMESPACE

class MyOpenGLWidget : public QOpenGLWidget {
  Q_OBJECT
 private:
  QPoint mPos;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *) override;
  void drawObject();

 public:
  void setData(data_t &data_);
  data_t &getData() { return data; }
  MyOpenGLWidget(QWidget *parent = nullptr);
  MyOpenGLWidget(data_t &data, QWidget *parent = nullptr);
  ~MyOpenGLWidget();

  double scale_x;
  double scale_y;
  double scale_z;
  double translate_x;
  double translate_y;
  double translate_z;
  double rotate_x;
  double rotate_y;
  double rotate_z;

  int projection_type = 1;
  int thickness_size = 1;
  int edge_type = 0;
  int vertex_type = 0;
  int size_point = 0;

  QColor background_color = QColor(255, 255, 255);
  QColor facet_color = QColor(10, 186, 181);
  QColor vertex_color;

  QSettings *settings;
  void set_settings();
  void read_settings();

 private:
  data_t &data;
  data_t default_data;
  Ui::MyOpenGLWidget *ui;
};

#endif  // MYOPENGLWIDGET_H
