#include "deposit.h"

#include "ui_deposit.h"

deposit::deposit(QWidget *parent) : QDialog(parent), ui(new Ui::deposit) {
  ui->setupUi(this);
  QPixmap pix(":/img/pictures/kot2.jpg");
  int w = 290;
  int h = 190;
  ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

deposit::~deposit() { delete ui; }

void deposit::on_radioButton_pay_clicked() {
  ui->label_pay_or_cap->setText("Периодичность выплат");
  calc->setCapitalization(false);
}

void deposit::on_radioButton_cap_clicked() {
  ui->label_pay_or_cap->setText("Капитализация процентов");
  calc->setCapitalization(true);
  // calc->setFrequency(ui->comboBox_frequency->currentIndex());
  calc->setFrequency(
      static_cast<Frequency>(ui->comboBox_frequency->currentIndex()));
}

void deposit::on_pushButton_equal_clicked() {
  calc->setDepositAmount(ui->line_amount->text().toDouble());
  calc->setPercent(ui->line_percent->text().toDouble());
  calc->setDepositTerm(ui->line_term->text().toDouble());
  calc->setTax(ui->line_tax->text().toDouble());
  calc->setAddListValue(0, ui->line_add_1->text().toDouble());
  calc->setAddListValue(1, ui->line_add_1->text().toDouble());
  calc->setAddListValue(2, ui->line_add_1->text().toDouble());
  calc->setWithdrawalsList(0, ui->line_withdrawals_1->text().toDouble());
  calc->setWithdrawalsList(1, ui->line_withdrawals_1->text().toDouble());
  calc->setWithdrawalsList(2, ui->line_withdrawals_1->text().toDouble());
  calc->depositCalculation();
  ui->line_interest->setText(QString::number(calc->getInterest(), 'f', 0));
  ui->line_tax_amount->setText(QString::number(calc->getTaxAmount(), 'f', 0));
  ui->line_output_amount->setText(
      QString::number(calc->getOutputAmount(), 'f', 0));
}
