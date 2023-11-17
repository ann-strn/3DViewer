
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include "widget.h"
#include "simpleobject3d.h"
#include <QTimer>
#include <QMessageBox>
#include "gif/gifanim.h"
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {
class MainWindow;
}

class SimpleObject3D;
class OGLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QString filePath;
    ~MainWindow();
    void width_of_polygon_changed(int width);

    void type_is_paralel_changed(int type);
    void type_of_polygon_changed(int type);
    void type_of_vert_changed(int type);

private slots:
    void on_pushButton_open_file_clicked();
    void on_comboBox_type_is_parallel_currentIndexChanged(int index);
    void on_comboBox_type_of_vert_currentIndexChanged(int index);
    void on_comboBox_type_of_poly_currentIndexChanged(int index);
    void on_horizontalScrollBar_width_of_vert_valueChanged(int value);
    void on_horizontalScrollBar_width_of_poly_valueChanged(int value);
    void on_btn_screen_bmp_clicked();
    void closeEvent(QCloseEvent *event);
    void on_btn_screen_jpeg_clicked();
    void on_btn_screen_gif_clicked();
    void oneGif();
    void on_horizontalScrollBar_move_x_valueChanged(int value);
    void on_horizontalScrollBar_move_y_valueChanged(int value);
    void on_horizontalScrollBar_move_z_valueChanged(int value);
    void on_scale_valueChanged(int value);
    void on_horizontalScrollBar_rotate_x_valueChanged(int value);
    void on_horizontalScrollBar_rotate_y_valueChanged(int value);
    void on_horizontalScrollBar_rotate_z_valueChanged(int value);
    void on_pushButton_back_color_clicked();
    void on_pushButton_color_polygo_clicked();
    void on_pushButton_vertices_color_clicked();

signals:
    void signal_back_color(QColor color);
    void signal_vert_color(QColor color);
    void signal_polygon_color(QColor color);
    void signal_width_of_polygon(int width);
    void signal_type_is_paralel(int type);
    void signal_type_of_polygon(int type);
    void signal_type_of_vert(int type);

private:
    Ui::MainWindow *ui;
    constexpr static const size_t GifFps = 10;
    constexpr static const size_t GifLength = 5;
    size_t counter = 0;
    QDir dir;
    QString pathProject = QDir::homePath() + "/Desktop/viewer/";
    double startTime, tmpTime;
    int width_of_poly, projection_view, width_of_vert, type_of_vert, type_of_poly;
     QTimer *timer;
     QColor polygonColor, vertexColor, backColor;

     void createGif();
     void sendColorSettings();
     void saveSettings();
     void loadSettings();


};

#endif // MAINWINDOW_H
