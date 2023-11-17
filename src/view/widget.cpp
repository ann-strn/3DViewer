#include "widget.h"

#include <simpleobject3d.h>

#include <QMouseEvent>
#include <QOpenGLContext>
#include <iostream>

OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  m_x = 1.0f;
  t_x = 0.0f;
  t_y = 0.0f;
  t_z = -2.0f;
  obj = new SimpleObject3D;
}

OGLWidget::~OGLWidget() { delete obj; }

void OGLWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  initShaders();
}

void OGLWidget::paintGL() {
  glClearColor(rback_color, gback_color, bback_color, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  QMatrix4x4 viewMatrix;
  viewMatrix.setToIdentity();
  viewMatrix.translate(t_x, t_y, t_z);
  viewMatrix.scale(m_x);
  viewMatrix.rotate(m_rotation);

  m_projectionMatrix.setToIdentity();
  if (type_is_paralel)
    m_projectionMatrix.ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
  else
    m_projectionMatrix.perspective(45.0f, 1.31, 0.1f, 100.0f);
  m_program.bind();
  m_program.setUniformValue("u_projectionMatrix", m_projectionMatrix);
  m_program.setUniformValue("u_viewMatrix", viewMatrix);

  if (type_of_vert == 2) {
    glDisable(GL_POINT_SMOOTH);
    obj->draw_points = true;
  } else if (type_of_vert == 1) {
    obj->draw_points = true;
    glEnable(GL_POINT_SMOOTH);
  } else if (type_of_vert == 0) {
    obj->draw_points = false;
  }
  obj->line_color.setRgb(m_line_color.red(), m_line_color.green(),
                         m_line_color.blue(), m_line_color.alpha());
  obj->point_color.setRgb(m_point_color.red(), m_point_color.green(),
                          m_point_color.blue(), m_point_color.alpha());
  glPointSize(width_of_vert);
  glLineWidth(width_of_polygon);
  if (type_of_polygon == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 5);
  } else
    glDisable(GL_LINE_STIPPLE);

  obj->draw_no_t(&m_program, context()->functions());
  m_program.release();
}

void OGLWidget::initShaders() {
  if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         ":/shaders/vshader_no_t.vsh"))
    close();
  if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         ":/shaders/fshader_no_t.fsh"))
    close();
  if (!m_program.link()) close();
}

void OGLWidget::initObj(Data *obj_data) {
  std::vector<QVector3D> vertexes;
  for (int i = 0; i < obj_data->vertexCount; i++) {
    vertexes.emplace_back(obj_data->m.mtrx[i * 3], obj_data->m.mtrx[i * 3 + 1],
                          obj_data->m.mtrx[i * 3 + 2]);
  }
  std::vector<GLuint> indexes;
  for (int i = 0; i < obj_data->polygonCount; i++) {
    for (int j = 0; j < obj_data->polygon[i].numberOfVerticesInPolygon; j++) {
      indexes.emplace_back(obj_data->polygon[i].vertices[j]);
    }
  }
  destructData(obj_data);
  obj->init_no_t(vertexes, indexes);
}

void OGLWidget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton)
    m_mousePosition = QVector2D(event->position());
  else if (event->button() == Qt::RightButton)
    m_mousePosition = QVector2D(event->position());
  event->accept();
}

void OGLWidget::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() != Qt::LeftButton && event->buttons() != Qt::RightButton)
    return;

  QVector2D diff = QVector2D(event->position()) - m_mousePosition;
  m_mousePosition = QVector2D(event->position());

  if (event->buttons() == Qt::LeftButton) {
    float angle = diff.length() / 2.0;
    QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);
    m_rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation;
  } else if (event->buttons() == Qt::RightButton) {
    t_x += diff.x() / 400;
    t_y -= diff.y() / 300;
  }
  update();
}

void OGLWidget::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    m_x *= 1.25;
  } else if (event->angleDelta().y() < 0) {
    m_x /= 1.25;
  }
  update();
}

void OGLWidget::width_of_polygon_changed(int width) {
  width_of_polygon = width;
  update();
}

void OGLWidget::type_is_paralel_changed(int type) {
  type_is_paralel = type;
  update();
}

void OGLWidget::type_of_polygon_changed(int type) {
  type_of_polygon = type;
  update();
}

void OGLWidget::type_of_vert_changed(int type) {
  type_of_vert = type;
  update();
}

void OGLWidget::width_of_vert_changed(int width) {
  width_of_vert = width / 10;
  update();
}

void OGLWidget::rotate_x(int x) {
  float angle = x - last_x;
  last_x = x;
  QVector3D axis = QVector3D(1.0f, 0.0f, 0.0f);
  m_rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation;
  update();
}

void OGLWidget::rotate_y(int y) {
  float angle = y - last_y;
  last_y = y;
  QVector3D axis = QVector3D(0.0f, 1.0f, 0.0f);
  m_rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation;
  update();
}

void OGLWidget::rotate_z(int z) {
  float angle = z - last_z;
  last_z = z;
  QVector3D axis = QVector3D(0.0f, 0.0f, 1.0f);
  m_rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation;
  update();
}