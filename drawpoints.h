#ifndef DRAWPOINTS_H
#define DRAWPOINTS_H

#include <QOpenGLWidget>
#include <QVector2D>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QPainter>

const double NEARFIELD = 2;
const double MONTHS = 42;

class drawPoints: public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit drawPoints(QWidget *parent = nullptr);
    ~drawPoints();
    void setPoints(QVector<QVector2D> points);

    void setAxis(bool axis);

    void setBig(bool big);

private:

    void initializeGL();

    void paintGL();

    void drawAxis();

    void renderText(double x, double y, const QString &str);

    QVector<QVector2D> m_points;

    QVector<QVector2D> m_axisPoints;

    QOpenGLShaderProgram *m_program = nullptr;
    QOpenGLVertexArrayObject m_VArray;
    QOpenGLBuffer m_buffer;
    int m_matrix;

    QOpenGLShaderProgram *m_programA = nullptr;
    QOpenGLVertexArrayObject m_VArrayA;
    QOpenGLBuffer m_bufferA;
    int m_matrixA;
    bool m_dataLoaded = false;

    float m_yTop = 1.01f;
    float m_yBottom = -0.1f;
    float m_xRight = 1.01f;
    float m_xLeft = -0.01f;

    bool m_axis = false;
    bool m_big = false;
};
#endif // DRAWPOINTS_H
