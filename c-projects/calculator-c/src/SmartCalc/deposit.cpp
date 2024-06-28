#include "deposit.h"
#include "ui_deposit.h"

deposit::deposit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deposit)
{
    ui->setupUi(this);
    QPixmap pix(":/img/pictures/kot2.jpg");
    int w = 290;
    int h = 190;
    ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

deposit::~deposit()
{
    delete ui;
}

void deposit::on_radioButton_pay_clicked() {
    ui->label_pay_or_cap->setText("Периодичность выплат");
    calc->capitalization = 0;
}

void deposit::on_radioButton_cap_clicked() {
    ui->label_pay_or_cap->setText("Капитализация процентов");
    calc->capitalization = 1;
    calc->frequency = ui->comboBox_frequency->currentIndex();
}

void deposit::on_pushButton_equal_clicked() {
    calc->deposit_amount = ui->line_amount->text().toDouble();
    calc->percent = ui->line_percent->text().toDouble();
    calc->deposit_term = ui->line_term->text().toDouble();
    calc->tax = ui->line_tax->text().toDouble();
    calc->add_list[0] = ui->line_add_1->text().toDouble();
    calc->add_list[1] = ui->line_add_2->text().toDouble();
    calc->add_list[2] = ui->line_add_3->text().toDouble();
    calc->withdrawals_list[0] = ui->line_withdrawals_1->text().toDouble();
    calc->withdrawals_list[1] = ui->line_withdrawals_2->text().toDouble();
    calc->withdrawals_list[2] = ui->line_withdrawals_3->text().toDouble();
    deposit_calculator(calc);
    ui->line_interest->setText(QString::number(calc->interest, 'f', 0));
    ui->line_tax_amount->setText(QString::number(calc->tax_amount, 'f', 0));
    ui->line_output_amount->setText(QString::number(calc->output_amount, 'f', 0));
}
