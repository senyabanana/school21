#include "myopenglwidget.h"

#include "ui_mainwindow.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), data(default_data) {
  settings = new QSettings(
      QCoreApplication::applicationDirPath() + "/my_settings.conf",
      QSettings::IniFormat);
}

MyOpenGLWidget::MyOpenGLWidget(data_t &data, QWidget *parent)
    : QOpenGLWidget(parent), data(data) {
  data.polygons.clear();
  data.array_for_vertices.clear();
  data.array_for_facets.clear();
  data.count_of_vertices = 0;
  data.count_of_facets = 0;
  data.count_v = 0;
  data.max = 0;
  data.min = 0;

  settings = new QSettings(
      QCoreApplication::applicationDirPath() + "/my_settings.conf",
      QSettings::IniFormat);
}

MyOpenGLWidget::~MyOpenGLWidget() {}

void MyOpenGLWidget::setData(data_t &data_) {
  data = data_;
  update();
}

void MyOpenGLWidget::set_settings() {
  settings->beginGroup("OpenGL widget settings");

  settings->setValue("Scalling X", scale_x);
  settings->setValue("Scalling Y", scale_y);
  settings->setValue("Scalling Z", scale_z);
  settings->setValue("Translation X", translate_x);
  settings->setValue("Translation Y", translate_y);
  settings->setValue("Translation Z", translate_z);
  settings->setValue("Rotating X", rotate_x);
  settings->setValue("Rotating Y", rotate_y);
  settings->setValue("Rotating Z", rotate_z);

  settings->setValue("Projection type", projection_type);
  settings->setValue("Thickness size", thickness_size);
  settings->setValue("Edge type", edge_type);
  settings->setValue("Vertex type", vertex_type);
  settings->setValue("Size point", size_point);

  settings->setValue("Background color", background_color);
  settings->setValue("Edge color", facet_color);
  settings->setValue("Vertex color", vertex_color);

  settings->endGroup();
}

void MyOpenGLWidget::read_settings() {
  settings->beginGroup("OpenGL widget settings");

  scale_x = settings->value("Scalling X", 1.0).toDouble();
  scale_y = settings->value("Scalling y", 1.0).toDouble();
  scale_z = settings->value("Scalling z", 1.0).toDouble();
  translate_x = settings->value("Translation X", 0.0).toDouble();
  translate_y = settings->value("Translation Y", 0.0).toDouble();
  translate_z = settings->value("Translation Z", 0.0).toDouble();
  rotate_x = settings->value("Rotating X", 0.0).toDouble();
  rotate_y = settings->value("Rotating Y", 0.0).toDouble();
  rotate_z = settings->value("Rotating Z", 0.0).toDouble();

  projection_type = settings->value("Projection type", 1).toInt();
  thickness_size = settings->value("Thickness size", 1).toInt();
  edge_type = settings->value("Edge size", 0).toInt();
  vertex_type = settings->value("Vertex type", 0).toInt();
  size_point = settings->value("Size point", 0).toInt();

  background_color =
      settings->value("Background color", background_color).value<QColor>();
  facet_color = settings->value("Edge color", facet_color).value<QColor>();
  vertex_color = settings->value("Vertex color", vertex_color).value<QColor>();

  settings->endGroup();
}

void MyOpenGLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void MyOpenGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void MyOpenGLWidget::paintGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection_type == 0) {
    glOrtho(data.min, data.max, data.min, data.max, data.min, data.max);
  } else {
    glFrustum(data.min, data.max, data.min, data.max, data.max, data.max * 3);
  }
  glClearColor(background_color.red() / 255.0, background_color.green() / 255.0,
               background_color.blue() / 255.0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glScaled(scale_x, scale_y, scale_z);
  if (projection_type == 0) {
    glTranslated(translate_x, translate_y, translate_z);
  } else {
    glTranslated(translate_x, translate_y, translate_z - (data.max - data.min));
  }
  glRotated(rotate_x, 1, 0, 0);
  glRotated(rotate_y, 0, 1, 0);
  glRotated(rotate_z, 0, 0, 1);
  drawObject();
  update();
}

void MyOpenGLWidget::drawObject() {
  glColor3d(vertex_color.red() / 255.0, vertex_color.green() / 255.0,
            vertex_color.blue() / 255.0);
  if (vertex_type == 1) {
    glEnable(GL_POINT_SMOOTH);
    glPointSize(size_point);
  } else if (vertex_type == 2) {
    glDisable(GL_POINT_SMOOTH);
    glPointSize(size_point);
  }
  glVertexPointer(3, GL_DOUBLE, 0, data.array_for_vertices.data());
  glEnableClientState(GL_VERTEX_ARRAY);
  if (vertex_type != 0) {
    glDrawArrays(GL_POINTS, 1, data.count_of_vertices);
  }
  glColor3d(facet_color.red() / 255.0, facet_color.green() / 255.0,
            facet_color.blue() / 255.0);
  glLineWidth(thickness_size);
  glLineStipple(2, 0X00FF);
  if (edge_type == 1) {
    glEnable(GL_LINE_STIPPLE);
  }
  glDrawElements(GL_LINES, data.count_v * 2, GL_UNSIGNED_INT,
                 data.array_for_facets.data());
  glDisable(GL_LINE_STIPPLE);
  glDisableClientState(GL_VERTEX_ARRAY);

  set_settings();
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *mo) {
  rotate_x = 1 / M_PI * (mo->pos().y() - mPos.y());
  rotate_y = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    scale_x *= 0.9;
    scale_y *= 0.9;
    scale_z *= 0.9;
  } else {
    scale_x *= 1.1;
    scale_y *= 1.1;
    scale_z *= 1.1;
  }
  update();
}
