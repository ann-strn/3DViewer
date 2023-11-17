#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(this, &MainWindow::signal_type_of_vert, ui->WidgetUI,
          &OGLWidget::type_of_vert_changed);
  connect(this, &MainWindow::signal_type_is_paralel, ui->WidgetUI,
          &OGLWidget::type_is_paralel_changed);
  connect(this, &MainWindow::signal_type_of_polygon, ui->WidgetUI,
          &OGLWidget::type_of_polygon_changed);
  dir = QDir::homePath();
  loadSettings();
}

MainWindow::~MainWindow() { delete ui; }

//
void MainWindow::on_pushButton_open_file_clicked() {
  ui->WidgetUI->update();
  filePath = QFileDialog::getOpenFileName(
      this, "Выбрать файл",
      static_cast<QDir>(QDir::homePath()).absolutePath() +
          "/Desktop/viewer/models/",
      "Файлы OBJ (*.obj)");
  if (!filePath.isEmpty()) {
    Data *obj_data = openObjFile(filePath.toStdString().c_str());

    if (!obj_data->polygonCount && !obj_data->vertexCount) {
      ui->label_file_name->setText("Ошибка файла");
    } else {
      ui->label_file_name->setText(QFileInfo(filePath).fileName());
      ui->label_file_path->setText(filePath);
    }
    size_t edge_cntr = 0;
    for (int i = 0; i < obj_data->polygonCount; i++) {
      for (int j = 0; j < obj_data->polygon[i].numberOfVerticesInPolygon; j++) {
        edge_cntr++;
      }
    }
    ui->label_count_of_polygons->setText(QString::number(edge_cntr / 4));
    ui->label_count_of_vertices->setText(
        QString::number(obj_data->vertexCount));

    ui->WidgetUI->initObj(obj_data);
  }
}

void MainWindow::on_comboBox_type_is_parallel_currentIndexChanged(int index) {
  projection_view = index;
  ui->comboBox_type_is_parallel->setCurrentIndex(index);
  ui->WidgetUI->type_is_paralel = index;
  ui->WidgetUI->update();
}

void MainWindow::on_horizontalScrollBar_width_of_vert_valueChanged(int value) {
  width_of_vert = value;
  ui->horizontalScrollBar_width_of_vert->setValue(value);
  ui->WidgetUI->width_of_vert = width_of_vert;
  ui->WidgetUI->update();
}

void MainWindow::on_comboBox_type_of_vert_currentIndexChanged(int index) {
  type_of_vert = index;
  ui->comboBox_type_of_vert->setCurrentIndex(index);
  ui->WidgetUI->type_of_vert = index;
  ui->WidgetUI->update();
}

void MainWindow::on_comboBox_type_of_poly_currentIndexChanged(int index) {
  type_of_poly = index;
  ui->comboBox_type_of_poly->setCurrentIndex(index);
  ui->WidgetUI->type_of_polygon = index;
  ui->WidgetUI->update();
}

void MainWindow::on_horizontalScrollBar_width_of_poly_valueChanged(int value) {
  width_of_poly = value;
  ui->horizontalScrollBar_width_of_poly->setValue(value);
  ui->WidgetUI->width_of_polygon = width_of_poly / 10;
  ui->WidgetUI->update();
}

void MainWindow::on_btn_screen_bmp_clicked() {
  QDir *pathDir = new QDir();
  pathDir->mkdir(pathProject);
  pathDir->mkdir(pathProject + "/screenshots");
  QDateTime dateTime = dateTime.currentDateTime();
  QString currentDateTime = dateTime.toString("yyyy_MM_dd_HHmmss_zzz");
  ui->btn_screen_bmp->setEnabled(false);
  ui->WidgetUI->grab().save(pathProject + "screenshots/" + currentDateTime +
                            ".bmp");
  ui->btn_screen_bmp->setEnabled(true);
}

void MainWindow::on_btn_screen_jpeg_clicked() {
  QDir *pathDir = new QDir();
  pathDir->mkdir(pathProject);
  pathDir->mkdir(pathProject + "/screenshots");
  QDateTime dateTime = dateTime.currentDateTime();
  QString currentDateTime = dateTime.toString("yyyy_MM_dd_HHmmss_zzz");
  ui->btn_screen_jpeg->setEnabled(false);
  ui->WidgetUI->grab().save(pathProject + "screenshots/" + currentDateTime +
                            ".jpg");
  ui->btn_screen_jpeg->setEnabled(true);
}

void MainWindow::on_btn_screen_gif_clicked() {
  QDir *pathDir = new QDir();
  pathDir->mkdir(pathProject);
  pathDir->mkdir(pathProject + "/screenshots");
  QDateTime dateTime = dateTime.currentDateTime();
  ui->btn_screen_gif->setEnabled(false);
  pathDir->mkdir(pathProject + "/screenshots/gif_obj/");
  startTime = 0, tmpTime = 1000 / GifFps;
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(oneGif()));
  timer->start(1000 / GifFps);
}

void MainWindow::oneGif() {
  if (startTime == tmpTime) {
    ui->WidgetUI->grab()
        .scaled(640, 480, Qt::IgnoreAspectRatio)
        .save(pathProject + "/screenshots/gif_obj/" + QString::number(counter) +
              ".bmp");
    counter++;
    tmpTime += 1000 / GifFps;
  }
  if (startTime == 1000 * GifLength) {
    timer->stop();
    delete timer;
    counter = 0;
    createGif();
  }
  startTime += 1000 / GifFps;
}

void MainWindow::saveSettings() {
  QJsonObject settings;
  settings["polygonColor_r"] = polygonColor.red();
  settings["polygonColor_g"] = polygonColor.green();
  settings["polygonColor_b"] = polygonColor.blue();
  settings["polygonColor_a"] = polygonColor.alpha();
  settings["vertexColor_r"] = vertexColor.red();
  settings["vertexColor_g"] = vertexColor.green();
  settings["vertexColor_b"] = vertexColor.blue();
  settings["vertexColor_a"] = vertexColor.alpha();
  settings["backColor_r"] = backColor.red();
  settings["backColor_g"] = backColor.green();
  settings["backColor_b"] = backColor.blue();
  settings["backColor_a"] = backColor.alpha();
  settings["width_of_poly"] = width_of_poly;
  settings["projection_view"] = projection_view;
  settings["width_of_vert"] = width_of_vert;
  settings["type_of_vert"] = type_of_vert;
  settings["type_of_poly"] = type_of_poly;

  QJsonDocument doc(settings);
  QFile file(dir.absolutePath() + "/Desktop/viewer/settings.json");
  if (file.open(QIODevice::WriteOnly)) {
    file.write(doc.toJson());
    file.close();
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {
  saveSettings();
  event->accept();
}

void MainWindow::loadSettings() {
  QFile life(dir.absolutePath() + "/Desktop/viewer/settings.json");

  if (life.open(QIODevice::ReadOnly)) {
    QJsonDocument jsonchik = QJsonDocument::fromJson(life.readAll());
    QJsonObject settings = jsonchik.object();

    polygonColor.setRed(settings.value("polygonColor_r").toInt());
    polygonColor.setGreen(settings.value("polygonColor_g").toInt());
    polygonColor.setBlue(settings.value("polygonColor_b").toInt());
    polygonColor.setAlpha(settings.value("polygonColor_a").toInt());

    vertexColor.setRed(settings.value("vertexColor_r").toInt());
    vertexColor.setGreen(settings.value("vertexColor_g").toInt());
    vertexColor.setBlue(settings.value("vertexColor_b").toInt());
    vertexColor.setAlpha(settings.value("vertexColor_a").toInt());

    backColor.setRed(settings.value("backColor_r").toInt());
    backColor.setGreen(settings.value("backColor_g").toInt());
    backColor.setBlue(settings.value("backColor_b").toInt());
    backColor.setAlpha(settings.value("backColor_a").toInt());

    type_of_vert = settings.value("type_of_vert").toInt();
    type_of_poly = settings.value("type_of_poly").toInt();
    width_of_vert = settings.value("width_of_vert").toInt();
    width_of_poly = settings.value("width_of_poly").toInt();
    projection_view = settings.value("projection_view").toInt();

    life.close();
    sendColorSettings();
    on_horizontalScrollBar_width_of_poly_valueChanged(width_of_poly);
    on_horizontalScrollBar_width_of_vert_valueChanged(width_of_vert);
    on_comboBox_type_of_poly_currentIndexChanged(type_of_poly);
    on_comboBox_type_of_vert_currentIndexChanged(type_of_vert);
    on_comboBox_type_is_parallel_currentIndexChanged(projection_view);
  }
}

void MainWindow::createGif() {
  QDir pathFile;
  QDateTime dateTime = dateTime.currentDateTime();
  QString currentDateTime = dateTime.toString("yyyy_MM_dd_HHmmss_zzz");
  QString gif_name = pathProject + "/screenshots/" + currentDateTime + ".gif";
  QByteArray ga = gif_name.toLocal8Bit();
  GifWriter writer;
  GifAnim anime;
  int err = 0;
  if (anime.GifBegin(&writer, ga.data(), 640, 480, 10, 8, false)) {
    for (int i = 0; i < 50; i++) {
      if (err == 1) {
        break;
      }
      QImage img(pathProject + "/screenshots/gif_obj/" + QString::number(i) +
                 ".bmp");
      anime.GifWriteFrame(&writer,
                          img.convertToFormat(QImage::Format_Indexed8)
                              .convertToFormat(QImage::Format_RGBA8888)
                              .constBits(),
                          640, 480, 10, 8, false);
    }
    anime.GifEnd(&writer);
  }

  pathFile.setPath(pathProject + "/screenshots/gif_obj/");
  pathFile.removeRecursively();
  ui->btn_screen_gif->setEnabled(true);
}

void MainWindow::on_horizontalScrollBar_move_x_valueChanged(int value) {
  ui->WidgetUI->t_x = (float)value / 100;
  ui->WidgetUI->update();
}

void MainWindow::on_horizontalScrollBar_move_y_valueChanged(int value) {
  ui->WidgetUI->t_y = (float)value / 100;
  ui->WidgetUI->update();
}

void MainWindow::on_horizontalScrollBar_move_z_valueChanged(int value) {
  ui->WidgetUI->t_z = (float)value / 10;
  ui->WidgetUI->update();
}

void MainWindow::on_scale_valueChanged(int value) {
  ui->WidgetUI->m_x = ((float)value / 100);
  ui->WidgetUI->update();
}

void MainWindow::on_horizontalScrollBar_rotate_x_valueChanged(int value) {
  ui->WidgetUI->rotate_x(value);
  ui->WidgetUI->update();
}

void MainWindow::on_horizontalScrollBar_rotate_y_valueChanged(int value) {
  ui->WidgetUI->rotate_y(value);
  ui->WidgetUI->update();
}

void MainWindow::on_horizontalScrollBar_rotate_z_valueChanged(int value) {
  ui->WidgetUI->rotate_z(value);
  ui->WidgetUI->update();
}

void MainWindow::on_pushButton_back_color_clicked() {
  backColor = QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");
  backColor.toRgb();
  sendColorSettings();
}

void MainWindow::sendColorSettings() {
  ui->WidgetUI->rback_color = backColor.red();
  ui->WidgetUI->gback_color = backColor.green();
  ui->WidgetUI->bback_color = backColor.blue();
  ui->WidgetUI->rback_color /= 255;
  ui->WidgetUI->gback_color /= 255;
  ui->WidgetUI->bback_color /= 255;

  ui->WidgetUI->m_line_color.setRgbF(polygonColor.redF(), polygonColor.greenF(),
                                     polygonColor.blueF(),
                                     polygonColor.alphaF());

  ui->WidgetUI->m_point_color.setRgbF(vertexColor.redF(), vertexColor.greenF(),
                                      vertexColor.blueF(),
                                      vertexColor.alphaF());
  ui->WidgetUI->update();
}

void MainWindow::on_pushButton_color_polygo_clicked() {
  polygonColor =
      QColorDialog::getColor(Qt::white, this, "Выберите цвет полигонов");
  polygonColor.toRgb();
  sendColorSettings();
}

void MainWindow::on_pushButton_vertices_color_clicked() {
  vertexColor = QColorDialog::getColor(Qt::white, this, "Выберите цвет вершин");
  vertexColor.toRgb();
  sendColorSettings();
}
