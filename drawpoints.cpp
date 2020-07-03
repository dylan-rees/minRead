#include "drawpoints.h"

drawPoints::drawPoints(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

drawPoints::~drawPoints()
{
    if (m_program !=nullptr) delete m_program;
    if (m_programA !=nullptr) delete m_programA;
}

void drawPoints::setPoints(QVector<QVector2D> points)
{
    m_points.clear();
    m_points = points;

    int size = (m_points.size()) * int(2*sizeof(float));
    m_VArray.bind();
    m_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_buffer.bind();
    m_buffer.allocate(m_points.constData(), size);
    m_buffer.release();

    m_dataLoaded = true;
    this->update();
}

void drawPoints::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    m_program = new QOpenGLShaderProgram();

    QOpenGLShader vShader( QOpenGLShader::Vertex);
    vShader.compileSourceFile(  ":/shaders/tex.vert" );
    QOpenGLShader fShader( QOpenGLShader::Fragment);
    fShader.compileSourceFile(  ":/shaders/tex.frag" );

    m_program->addShader( &vShader);
    m_program->addShader( &fShader);
    m_program->link();
    if ( !m_program->link())
    {
        qWarning( "ERROR: unable to link angle shader program.");
        return;
    }
    m_matrix = m_program->uniformLocation( "matrix" );

    m_VArray.create();
    m_buffer.create();
    m_program->release();

    m_programA = new QOpenGLShaderProgram();

    QOpenGLShader vShaderA( QOpenGLShader::Vertex);
    vShaderA.compileSourceFile(  ":/shaders/axis.vert" );
    QOpenGLShader fShaderA( QOpenGLShader::Fragment);
    fShaderA.compileSourceFile(  ":/shaders/axis.frag" );

    m_programA->addShader( &vShaderA);
    m_programA->addShader( &fShaderA);
    m_programA->link();
    if ( !m_program->link())
    {
        qWarning( "ERROR: unable to link angle shader program.");
        return;
    }
    m_matrixA = m_programA->uniformLocation( "matrix" );

    m_VArrayA.create();
    m_bufferA.create();
    m_programA->release();
    m_axisPoints.append(QVector2D(0.0f,1.0f));
    for (int i=0;i<=MONTHS;i++)
    {
        m_axisPoints.append(QVector2D(float(i)/float(MONTHS),0.0f));
        m_axisPoints.append(QVector2D(float(i)/float(MONTHS),-0.02f));
        m_axisPoints.append(QVector2D(float(i)/float(MONTHS),0.0f));
        if (i%6 == 0)
        {
            m_axisPoints.append(QVector2D(float(i)/float(MONTHS),-0.05f));
            m_axisPoints.append(QVector2D(float(i)/float(MONTHS),0.0f));
        }
    }
    int size = (m_axisPoints.size()) * int(2*sizeof(float));
    m_VArrayA.bind();
    m_bufferA.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_bufferA.bind();
    m_bufferA.allocate(m_axisPoints.constData(), size);
    m_bufferA.release();

}

void drawPoints::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable( GL_PROGRAM_POINT_SIZE );

    drawAxis();
    if (m_dataLoaded)
    {
        QMatrix4x4 matrix;
        matrix.ortho(  m_xLeft, m_xRight, m_yBottom, m_yTop, NEARFIELD, -NEARFIELD );
        matrix.translate( 0.0f, 0.0f, 1.0f );

        m_program->bind();
        m_program->setUniformValue( m_matrix, matrix );


        m_VArray.bind();
        m_buffer.bind();
        m_program->enableAttributeArray(0);
        m_program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 0);
        m_buffer.release();

        glDrawArrays(GL_POINTS, 0, m_points.size());
        m_program->release();
        m_VArray.release();

    }
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
      qDebug() << err << endl;
    }
}

void drawPoints::drawAxis()
{
    QMatrix4x4 matrix;
    matrix.ortho(  m_xLeft, m_xRight, m_yBottom, m_yTop, NEARFIELD, -NEARFIELD );
    matrix.translate( 0.0f, 0.0f, 1.0f );

    m_programA->bind();
    m_programA->setUniformValue( m_matrix, matrix );


    m_VArrayA.bind();
    m_bufferA.bind();
    m_programA->enableAttributeArray(0);
    m_programA->setAttributeBuffer(0, GL_FLOAT, 0, 2, 0);
    m_bufferA.release();

    glDrawArrays(GL_LINE_STRIP, 0, m_axisPoints.size());
    m_programA->release();
    m_VArrayA.release();

    float yPos = -0.1f;
    if (m_big)
        yPos = -0.2f;
    for (int i=0;i<=MONTHS;i++)
    {
        float numAdj = 0.003f;
        if (i%6 ==0)
        {
            if (i<10)
                numAdj /=2;
            renderText(float(i)/float(MONTHS)-numAdj,yPos,QString::number(i));
        }
    }
}

void drawPoints::renderText(double x, double y, const QString &str)
{
    // Transform coordinates
    float xpos = ((x-m_xLeft)/(m_xRight-m_xLeft))*this->width();
    float ypos = (1-(y-m_yBottom)/(m_yTop-m_yBottom))*this->height();
    //Color set if required
    QColor color = Qt::black;

    // Render text
    QPainter painter(this);
    painter.setPen(color);
//    painter.setPen(Qt::black);
    if (m_big)
        painter.setFont(QFont("Arial",12,QFont::Bold,false));
    else
        painter.setFont(QFont("Arial",8,QFont::Bold,false));
    painter.drawText(xpos, ypos, str);
    painter.end();
}

void drawPoints::setBig(bool big)
{
    m_big = big;
    m_yTop = 0.71f;
    m_yBottom = -0.2f;
    this->update();
}

void drawPoints::setAxis(bool axis)
{
    m_axis = axis;
    m_yTop = 0.05f;
    m_yBottom = -0.4f;
    this->update();
}
