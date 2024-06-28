#ifndef CREDIT_H
#define CREDIT_H

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
class credit;
}

class credit : public QDialog
{
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

#endif // CREDIT_H
