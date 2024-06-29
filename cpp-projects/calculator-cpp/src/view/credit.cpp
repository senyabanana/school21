#include "credit.h"

#include "ui_credit.h"

credit::credit(QWidget *parent) : QDialog(parent), ui(new Ui::credit) {
  ui->setupUi(this);
  QPixmap pix(":/img/pictures/kot1.jpg");
  int w = 260;
  int h = 190;
  ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

credit::~credit() { delete ui; }

void credit::on_radioButton_annuity_clicked() {
  calc->setType(CreditType::ANNUNITY);
}

void credit::on_radioButton_differentiated_clicked() {
  calc->setType(CreditType::DIFFERENTIATED);
}

void credit::on_pushButton_equal_clicked() {
  calc->setCreditAmount(ui->line_amount->text().toDouble());
  calc->setPercent(ui->line_percent->text().toDouble());
  calc->setCreditTerm(ui->line_term->text().toDouble());
  calc->creditCalculation();
  if (calc->getType() == CreditType::DIFFERENTIATED) {
    ui->line_monthly_payment->setText(
        QString::number(calc->getMonthlyPayment(0), 'f', 2) + " ₽" + " ... " +
        QString::number(calc->getMonthlyPayment((int)calc->getCreditTerm() - 1),
                        'f', 2) +
        " ₽");
  } else {
    ui->line_monthly_payment->setText(
        QString::number(calc->getMonthlyPayment(0), 'f', 2) + " ₽");
  }
  ui->line_overpayment->setText(
      QString::number(calc->getOverpayment(), 'f', 2) + " ₽");
  ui->line_total_payout->setText(
      QString::number(calc->getTotalPayout(), 'f', 2) + " ₽");
}
