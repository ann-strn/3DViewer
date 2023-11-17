#include "simpleobject3d.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <iostream>

SimpleObject3D::SimpleObject3D() : m_indexBuffer(QOpenGLBuffer::IndexBuffer) {}

SimpleObject3D::SimpleObject3D(std::vector<QVector3D> &vertData,
                               const std::vector<GLuint> &indexes)
    : m_indexBuffer(QOpenGLBuffer::IndexBuffer) {
  init_no_t(vertData, indexes);
}

SimpleObject3D::~SimpleObject3D() {
  if (m_vertexBuffer.isCreated()) m_vertexBuffer.destroy();
  if (m_indexBuffer.isCreated()) m_indexBuffer.destroy();
}

void SimpleObject3D::init_no_t(std::vector<QVector3D> &vertData,
                               const std::vector<GLuint> &indexes) {
  if (m_vertexBuffer.isCreated()) m_vertexBuffer.destroy();
  if (m_indexBuffer.isCreated()) m_indexBuffer.destroy();

  m_vertexBuffer.create();
  m_vertexBuffer.bind();
  m_vertexBuffer.allocate(vertData.data(), vertData.size() * sizeof(QVector3D));
  m_vertexBuffer.release();

  m_indexBuffer.create();
  m_indexBuffer.bind();
  m_indexBuffer.allocate(indexes.data(), indexes.size() * sizeof(GLuint));
  m_indexBuffer.release();

  m_modelMatrix.setToIdentity();
}

void SimpleObject3D::draw_no_t(QOpenGLShaderProgram *program,
                               QOpenGLFunctions *functions) {
  if (!m_vertexBuffer.isCreated() || !m_indexBuffer.isCreated()) return;

  program->setUniformValue("u_modelMatrix", m_modelMatrix);

  m_vertexBuffer.bind();

  int vertLoc = program->attributeLocation("a_position");
  program->enableAttributeArray(vertLoc);
  program->setAttributeBuffer(vertLoc, GL_FLOAT, 0, 3, sizeof(QVector3D));

  m_indexBuffer.bind();

  program->setUniformValue("color", line_color);
  functions->glDrawElements(GL_LINES, m_indexBuffer.size() / 4.0,
                            GL_UNSIGNED_INT, 0);

  if (draw_points == true) {
    program->setUniformValue("color", point_color);
    functions->glDrawElements(GL_POINTS, m_indexBuffer.size() / 4.0,
                              GL_UNSIGNED_INT, 0);
  }

  m_vertexBuffer.release();
  m_indexBuffer.release();
}
