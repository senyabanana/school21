#include "mainwindow.h"

#include "credit.h"
#include "deposit.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(math_operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(math_operations()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(trigonometry()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(trigonometry()));

  QColor back_color("#434343");
  QColor label_color("#CECECE");
  ui->widget->setBackground(QBrush(back_color));
  ui->widget->xAxis->setTickLabelColor(label_color);
  ui->widget->yAxis->setTickLabelColor(label_color);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString str_numbers;
  if (ui->result->text() == '0') {
    ui->result->setText("");
  }
  if (flag_right_bracket == 1) {
    str_numbers = (ui->result->text() + button->text());
    ui->result->setText(str_numbers);
    flag_op = 0;
    flag_digit = 0;
    flag_right_bracket = 1;
    flag_sign = 1;
    flag_minus = 0;
    flag_x = 1;
  }
}

void MainWindow::math_operations() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->result->text() == '0') {
    flag_op = 1;
  }
  if (flag_op == 0) {
    ui->result->setText(ui->result->text() + button->text());
    flag_op = 1;
    flag_dot = 0;
    flag_digit = 1;
    flag_right_bracket = 1;
    flag_sign = 0;
    flag_x = 1;
  }
}

void MainWindow::trigonometry() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  if (ui->result->text() == '0') {
    ui->result->setText("");
  }
  ui->result->setText(ui->result->text() + button->text() + "(");
  flag_op = 1;
  flag_dot = 0;
  flag_trigo_count++;
  flag_digit = 1;
  flag_right_bracket = 1;
  flag_sign = 0;
  flag_x = 1;
}

void MainWindow::on_pushButton_minus_clicked() {
  if (flag_minus == 0) {
    if (ui->result->text() == '0') {
      ui->result->setText("");
    }
    ui->result->setText(ui->result->text() + "-");
    flag_op = 1;
    flag_dot = 0;
    flag_minus = 1;
    flag_digit = 0;
    flag_right_bracket = 1;
    flag_sign = 0;
    flag_x = 1;
  }
}

void MainWindow::on_pushButton_dot_clicked() {
  if (flag_dot == 0 && flag_op == 0 && flag_right_bracket == 1) {
    ui->result->setText(ui->result->text() + ".");
    flag_dot = 1;
    flag_op = 1;
    flag_digit = 1;
    flag_right_bracket = 1;
    flag_sign = 1;
    flag_x = 1;
  }
}

void MainWindow::on_pushButton_left_bracket_clicked() {
  QString str_numbers;
  if (ui->result->text() == '0') {
    ui->result->setText("");
    flag_sign = 0;
  }
  if (flag_sign == 0) {
    str_numbers = (ui->result->text() + "(");
    ui->result->setText(str_numbers);
    flag_trigo_count++;
  }
  flag_minus = 0;
  flag_x = 1;
}

void MainWindow::on_pushButton_right_bracket_clicked() {
  QString str_numbers;
  if (flag_trigo_count > 0 && flag_op == 0 && flag_right_bracket == 1) {
    str_numbers = (ui->result->text() + ")");
    ui->result->setText(str_numbers);
    flag_op = 0;
    flag_trigo_count--;
    flag_digit = 1;
    flag_right_bracket = 0;
    flag_sign = 1;
    flag_minus = 0;
    flag_x = 1;
  }
  flag_right_bracket = 1;
}

void MainWindow::on_pushButton_clear_clicked() {
  ui->pushButton_plus->setChecked(false);
  ui->pushButton_minus->setChecked(false);
  ui->pushButton_mul->setChecked(false);
  ui->pushButton_div->setChecked(false);
  ui->result->setText("0");
  flag_op = 0;
  flag_dot = 0;
  flag_trigo_count = 0;
  flag_digit = 1;
  flag_right_bracket = 1;
  flag_sign = 0;
  flag_minus = 0;
  flag_x = 1;
}

void MainWindow::on_pushButton_x_clicked() {
  if (ui->result->text() == '0') {
    ui->result->setText("");
  }
  ui->result->setText(ui->result->text() + "x");
  flag_op = 0;
  flag_minus = 0;
  flag_digit = 0;
  flag_right_bracket = 1;
  flag_sign = 1;
  flag_x = 0;
}

void MainWindow::on_pushButton_equal_clicked() {
  double x = 0.0;
  QPushButton *button = (QPushButton *)sender();
  button->setChecked(true);
  QString result_text = ui->result->text();
  QByteArray array_of_bytes = result_text.toLocal8Bit();
  std::string str = array_of_bytes.data();
  if (ui->x_value->text() != "") {
    x = (ui->x_value->text().toDouble());
  }
  QString result_to_str =
      QString::number(calcController.calculation(str, x), 'g', 15);
  ui->result->setText(result_to_str);
  flag_x = 1;
}

void MainWindow::on_pushButton_graf_clicked() {
  QString result_text = ui->result->text();
  QByteArray array_of_bytes = result_text.toLocal8Bit();
  std::string str = array_of_bytes.data();
  ui->widget->clearGraphs();
  x.clear();
  y.clear();
  yx_1 = 0;
  yx_2 = 0;
  xBegin = 0;
  xEnd = 0;
  h = 0.1;

  double Y = ui->x_value->text().toDouble();
  if (Y == 0) Y = 1;

  xy_1 = ui->lineEdit_max_x->text().toDouble();
  xy_2 = ui->lineEdit_min_x->text().toDouble();
  yx_1 = ui->lineEdit_max_y->text().toInt();
  yx_2 = ui->lineEdit_min_y->text().toInt();

  xBegin = yx_2;
  xEnd = yx_1 + h;

  ui->widget->xAxis->setRange(xy_2, xy_1);
  ui->widget->yAxis->setRange(yx_2, yx_1);
  N = (xEnd - xBegin) / h + 2;

  for (X = xBegin; X <= xEnd; X += h) {
    x.push_back(X);
    y.push_back(calcController.calculation(str, Y * X));
  }

  QColor graf_color("#F6872E");
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->graph(0)->setPen(QPen(graf_color));
  ui->widget->replot();
}

void MainWindow::on_pushButton_credit_clicked() {
  credit credit_window;
  credit_window.setModal(true);
  credit_window.exec();
}

void MainWindow::on_pushButton_deposit_clicked() {
  deposit deposit_window;
  deposit_window.setModal(true);
  deposit_window.exec();
}
