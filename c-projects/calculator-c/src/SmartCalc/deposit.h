#ifndef DEPOSIT_H
#define DEPOSIT_H

//#include "../calculator.h"
#include <QDialog>

#ifdef __cplusplus
extern "C" {
#endif
#include "../calculator.h"
#ifdef __cplusplus
}
#endif

namespace Ui {
class deposit;
}

class deposit : public QDialog
{
    Q_OBJECT

public:
    explicit deposit(QWidget *parent = nullptr);
    ~deposit();

private:
    Ui::deposit *ui;

    Deposit a;
    Deposit *calc = &a;

private slots:
    void on_pushButton_equal_clicked();
    void on_radioButton_pay_clicked();
    void on_radioButton_cap_clicked();
};

#endif // DEPOSIT_H
