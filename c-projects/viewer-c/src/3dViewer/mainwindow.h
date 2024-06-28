#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QTimer>
#include "QtGifImage/src/gifimage/qgifimage.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../viewer.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_button_clicked();
    void on_parallel_radio_clicked();
    void on_central_radio_clicked();
    void on_scale_pushButton_clicked();
    void on_rotate_pushButton_clicked();
    void on_translate_pushButton_clicked();
    void on_edge_pushButton_clicked();
    void on_vertex_pushButton_clicked();
    void on_background_color_pushButton_clicked();
    void on_edge_color_pushButton_clicked();
    void on_vertex_color_pushButton_clicked();
    void return_settings_from_widget();
    void on_save_pushButton_clicked();
    void on_gif_pushButton_clicked();
    void captureFrame();

private:
    void default_settings();
    QTimer *frameCaptureTimer;
    QList<QImage> frames;
    Ui::MainWindow *ui;
    int frameCount;
};
#endif // MAINWINDOW_H
