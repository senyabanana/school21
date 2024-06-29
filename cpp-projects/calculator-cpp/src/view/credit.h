#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

#include "../controller/controller.h"

namespace Ui {
class credit;
}

class credit : public QDialog {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private:
  Ui::credit *ui;

  Credit a;
  Credit *calc = &a;

 private slots:
  void on_pushButton_equal_clicked();
  void on_radioButton_annuity_clicked();
  void on_radioButton_differentiated_clicked();
};

#endif
