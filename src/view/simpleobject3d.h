#ifndef SIMPLEOBJECT3D_H
#define SIMPLEOBJECT3D_H

#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QColor>


class QOpenGLFunctions;
class QOpenGLShaderProgram;

class SimpleObject3D
{
public:
  SimpleObject3D();
  SimpleObject3D(std::vector<QVector3D> &vertData, const std::vector<GLuint> &indexes);
  ~SimpleObject3D();
  void init_no_t(std::vector<QVector3D> &vertData, const std::vector<GLuint> &indexes);
  void draw_no_t(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);
  QColor line_color;
  QColor point_color;
  bool draw_points = true;



private:
  QOpenGLBuffer m_vertexBuffer;
  QOpenGLBuffer m_indexBuffer;
  QMatrix4x4 m_modelMatrix;

public slots:


};

#endif // SIMPLEOBJECT3D_H
