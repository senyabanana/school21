#include "mainwindow.h"
#include "myopenglwidget.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), frameCount(0)
{
    ui->setupUi(this);
    setWindowTitle("3D Viewer");

    ui->opengl->read_settings();
    return_settings_from_widget();

    frameCaptureTimer = new QTimer(this);
    connect(frameCaptureTimer, &QTimer::timeout, this, &MainWindow::captureFrame);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_button_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open .obj file:"), "../../", tr("Obj Files (*.obj)"));
    if (filename.isEmpty()) {
        qDebug() << "Дядя, выбери файл, чи шо";
        return;
    }
    default_settings();
    QByteArray file = filename.toLocal8Bit();
    char *file_name = file.data();
    process_input_data(ui->opengl->data, (char *)file_name);
    vertices_to_array(ui->opengl->data);
    facets_to_array(ui->opengl->data);
    ui->filename_label_2->setText(filename);
    ui->vertices_label_2->setText(QString::number(ui->opengl->data->count_of_vertices));
    ui->edges_label_2->setText((QString::number(ui->opengl->data->count_of_facets)));
    ui->opengl->update();
}

void MainWindow::default_settings() {
    ui->scale_x_lineEdit->setText("1");
    ui->scale_y_lineEdit->setText("1");
    ui->scale_z_lineEdit->setText("1");
    ui->rotate_x_lineEdit->setText("0");
    ui->rotate_y_lineEdit->setText("0");
    ui->rotate_z_lineEdit->setText("0");
    ui->translate_x_lineEdit->setText("0");
    ui->translate_y_lineEdit->setText("0");
    ui->translate_z_lineEdit->setText("0");
}

void MainWindow::on_parallel_radio_clicked() {
    ui->opengl->projection_type = 0;
}

void MainWindow::on_central_radio_clicked() {
    ui->opengl->projection_type = 1;
}

void MainWindow::on_scale_pushButton_clicked() {
    ui->opengl->scale_x = ui->scale_x_lineEdit->text().toDouble();
    ui->opengl->scale_y = ui->scale_y_lineEdit->text().toDouble();
    ui->opengl->scale_z = ui->scale_z_lineEdit->text().toDouble();
    ui->opengl->update();
}

void MainWindow::on_rotate_pushButton_clicked() {
    ui->opengl->rotate_x = ui->rotate_x_lineEdit->text().toDouble();
    ui->opengl->rotate_y = ui->rotate_y_lineEdit->text().toDouble();
    ui->opengl->rotate_z = ui->rotate_z_lineEdit->text().toDouble();
    ui->opengl->update();
}

void MainWindow::on_translate_pushButton_clicked() {
    ui->opengl->translate_x = ui->translate_x_lineEdit->text().toDouble();
    ui->opengl->translate_y = ui->translate_y_lineEdit->text().toDouble();
    ui->opengl->translate_z = ui->translate_z_lineEdit->text().toDouble();
    ui->opengl->update();
}

void MainWindow::on_edge_pushButton_clicked() {
    if (ui->solid_radio->isChecked()) {
        ui->opengl->edge_type = 0;
    } else if (ui->dashed_radio->isChecked()){
        ui->opengl->edge_type = 1;
    }
    ui->opengl->thickness_size = ui->thickness_lineEdit->text().toDouble();
    ui->opengl->update();
}

void MainWindow::on_vertex_pushButton_clicked() {
    if (ui->default_radio->isChecked()) {
        ui->opengl->vertex_type = 0;
    } else if (ui->circle_radio->isChecked()) {
        ui->opengl->vertex_type = 1;
    } else if (ui->square_radio->isChecked()) {
        ui->opengl->vertex_type = 2;
    }
    ui->opengl->size_point = ui->size_lineEdit->text().toDouble();
    ui->opengl->update();
}

void MainWindow::on_background_color_pushButton_clicked() {
    ui->opengl->background_color = QColorDialog::getColor(Qt::white, this, tr("Background color"), QColorDialog::DontUseNativeDialog);
}

void MainWindow::on_edge_color_pushButton_clicked() {
    ui->opengl->facet_color = QColorDialog::getColor(Qt::white, this, tr("Edge color"), QColorDialog::DontUseNativeDialog);
}

void MainWindow::on_vertex_color_pushButton_clicked() {
    ui->opengl->vertex_color = QColorDialog::getColor(Qt::white, this, tr("Vertex color"), QColorDialog::DontUseNativeDialog);
}

void MainWindow::return_settings_from_widget() {
    ui->scale_x_lineEdit->setText(QString::number(ui->opengl->scale_x));
    ui->scale_y_lineEdit->setText(QString::number(ui->opengl->scale_y));
    ui->scale_z_lineEdit->setText(QString::number(ui->opengl->scale_z));
    ui->translate_x_lineEdit->setText(QString::number(ui->opengl->translate_x));
    ui->translate_y_lineEdit->setText(QString::number(ui->opengl->translate_y));
    ui->translate_z_lineEdit->setText(QString::number(ui->opengl->translate_z));
    ui->rotate_x_lineEdit->setText(QString::number(ui->opengl->rotate_x));
    ui->rotate_y_lineEdit->setText(QString::number(ui->opengl->rotate_y));
    ui->rotate_z_lineEdit->setText(QString::number(ui->opengl->rotate_z));

    if (ui->opengl->projection_type == 1) {
        ui->central_radio->setChecked(true);
    } else if (ui->opengl->projection_type == 0) {
        ui->parallel_radio->setChecked(true);
    }
    ui->thickness_lineEdit->setText(QString::number(ui->opengl->thickness_size));
    if (ui->opengl->edge_type == 0) {
        ui->solid_radio->setChecked(true);
    } else if (ui->opengl->edge_type == 1) {
        ui->dashed_radio->setChecked(true);
    }
    if (ui->opengl->vertex_type == 0) {
        ui->default_radio->setChecked(true);
    } else if (ui->opengl->vertex_type == 1) {
        ui->circle_radio->setChecked(true);
    } else if (ui->opengl->vertex_type == 2) {
        ui->square_radio->setChecked(true);
    }
    ui->size_lineEdit->setText(QString::number(ui->opengl->size_point));
}

void MainWindow::on_save_pushButton_clicked() {
    QString image_format;
    if (ui->bmp_radio->isChecked()) {      
        image_format = "*.bmp";
    } else if (ui->jpeg_radio->isChecked()) {
        image_format = "*.jpeg";
    }
    QString save_image = QFileDialog::getSaveFileName(this, tr("Save file as: "), "", image_format);
    if (!save_image.endsWith(".bmp", Qt::CaseInsensitive) && ui->bmp_radio->isChecked()) {
                save_image += ".bmp";
    } else if (!save_image.endsWith(".jpeg", Qt::CaseInsensitive) && ui->jpeg_radio->isChecked()) {
                save_image += ".jpeg";
    }
    ui->opengl->grabFramebuffer().save(save_image);
}

void MainWindow::on_gif_pushButton_clicked() {
    frames.clear(); // Clear any existing frames
    frameCount = 0; // Reset frame count
    frameCaptureTimer->start(100); // Start capturing frames every 100ms
}

void MainWindow::captureFrame() {
    if(frameCount < 50) { // Capture 50 frames for 5 seconds
        QImage frame = ui->opengl->grabFramebuffer();
        frames.append(frame);
        frameCount++;
    } else {
        frameCaptureTimer->stop(); // Stop the timer after capturing 50 frames
        // Compile frames into a GIF here
        QGifImage gif(QSize(791, 791));
        gif.setDefaultDelay(100);
        for(auto &frame : frames) {
            gif.addFrame(frame);
        }
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save GIF"), "", tr("GIF Files (*.gif)"));
        if (!fileName.isEmpty()) {
            if (!fileName.endsWith(".gif", Qt::CaseInsensitive)) {
                fileName += ".gif";
            }
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly)) {
                gif.save(&file);
            }
        }
        // Reset for next capture
        frames.clear();
        frameCount = 0;
    }
}