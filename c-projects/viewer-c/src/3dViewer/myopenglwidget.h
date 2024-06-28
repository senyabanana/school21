#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QtWidgets/QWidget>
#include <QSettings>

#include "mainwindow.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../viewer.h"
#ifdef __cplusplus
}
#endif

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
    MyOpenGLWidget(QWidget *parent = nullptr);
    ~MyOpenGLWidget();
    object_t a;
    object_t *data = &a;

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

    //175, 175, 175 10, 186, 181
    QColor background_color = QColor(255, 255, 255);
    QColor facet_color = QColor(10, 186, 181);
    QColor vertex_color;

    QSettings *settings;
    void set_settings();
    void read_settings();
private:
    Ui::MyOpenGLWidget *ui;
};

#endif // MYOPENGLWIDGET_H
