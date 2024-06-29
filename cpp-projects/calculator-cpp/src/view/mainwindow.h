#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QVector>

#include "../controller/controller.h"

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

  CalculatorController calcController;
  int flag_op = 0;
  int flag_dot = 0;
  int flag_digit = 1;
  int flag_right_bracket = 1;
  int flag_sign = 0;
  int flag_trigo_count = 0;
  int flag_minus = 0;
  int flag_x = 0;

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

#endif
