#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "../calculator.h"
#include <QMainWindow>
#include <QVector>
#include <QPixmap>

#ifdef __cplusplus
extern "C" {
#endif
#include "../calculator.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    double xBegin, xEnd, h, X, xy_1, xy_2, yx_1, yx_2;
    int N;
    QVector<double> x, y;

private slots:
    void numbers();
    void math_operations();
    void trigonometry();
    void on_pushButton_dot_clicked();
    void on_pushButton_left_bracket_clicked();
    void on_pushButton_right_bracket_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_minus_clicked();
    void on_pushButton_x_clicked();
    void on_pushButton_equal_clicked();
    void on_pushButton_credit_clicked();
    void on_pushButton_deposit_clicked();
    void on_pushButton_graf_clicked();
};
#endif // MAINWINDOW_H
