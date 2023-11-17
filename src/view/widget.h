#ifndef WIDGET_H
#define WIDGET_H

#define GL_SILENCE_DEPRECATION

extern "C" {
#include "../back/parser.h"
#include "../back/affine_transformations.h"
}

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>


class SimpleObject3D;

class OGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();
    QColor m_background_color, m_line_color, m_point_color;
    float m_x, t_z, t_x, t_y;
    float rback_color, gback_color, bback_color;
    int type_is_paralel = 0, type_of_vert = 0, type_of_polygon = 0,  width_of_polygon = 1, width_of_vert = 5, last_x = 0,
    last_y = 0, last_z = 0;
    void initObj(Data *obj_data);


protected:
    void initializeGL() override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void closeObject();
    void initShaders();

private:
    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_program;
    QVector2D m_mousePosition;
    QQuaternion m_rotation;

    SimpleObject3D *obj ;

public slots:
    void width_of_polygon_changed(int width);
    void width_of_vert_changed(int width);
    void type_is_paralel_changed(int type);
    void type_of_polygon_changed(int type);
    void type_of_vert_changed(int type);
    void rotate_x(int x);
    void rotate_y(int y);
    void rotate_z(int z);
};
#endif // WIDGET_H
