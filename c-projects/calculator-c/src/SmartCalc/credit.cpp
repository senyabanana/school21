#include "credit.h"
#include "ui_credit.h"

credit::credit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::credit)
{
    ui->setupUi(this);
    QPixmap pix(":/img/pictures/kot1.jpg");
    int w = 260;
    int h = 190;
    ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

credit::~credit()
{
    delete ui;
}

void credit::on_radioButton_annuity_clicked() {
    calc->type_of_credit = 0;
}

void credit::on_radioButton_differentiated_clicked() {
    calc->type_of_credit = 1;
}

void credit::on_pushButton_equal_clicked() {
    calc->credit_amount = ui->line_amount->text().toDouble();
    calc->percent = ui->line_percent->text().toDouble();
    calc->credit_term = ui->line_term->text().toDouble();
    credit_calculator(calc);
    if (calc->type_of_credit) {
        ui->line_monthly_payment->setText(QString::number(calc->monthly_payment[0], 'f', 2) + " ₽" + " ... " + QString::number(calc->monthly_payment[(int)calc->credit_term-1], 'f', 2) + " ₽");
    } else {
        ui->line_monthly_payment->setText(QString::number(calc->monthly_payment[0], 'f', 2) + " ₽");
    }
    ui->line_overpayment->setText(QString::number(calc->overpayment, 'f', 2) + " ₽");
    ui->line_total_payout->setText(QString::number(calc->total_payout, 'f', 2) + " ₽");
}
