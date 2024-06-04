#ifndef QOPENGLPANEL_H
#define QOPENGLPANEL_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLVertexArrayObject>
#include <QtOpenGL/QOpenGLBuffer>
#include <QFile>
#include <QMatrix4x4>
#include <QtMath>

class QOpenGLPanel : public QOpenGLWidget
{
public:
    QOpenGLPanel(QWidget *parent = nullptr);
    ~QOpenGLPanel();

private:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    const char* readShaderSource(QString filename);
    QOpenGLFunctions* getGLFunctions();
    QOpenGLExtraFunctions* getGLExtraFunctions();
    bool initializeShaderProgram(QString vertex, QString fragment, QOpenGLFunctions *f);
    bool checkGLError(QOpenGLFunctions *f, QString functionCall);

    GLuint progID, vertID, fragID;
    GLuint arrays, triangleData;
    GLuint position, color;

    GLuint translateMatrixID, rotateMatrixID, scaleMatrixID, reflectMatrixID;
    QMatrix4x4 translateMatrix, rotateMatrix, scaleMatrix, reflectMatrix;

    GLfloat tX, tY, tZ;
    float rDegree;
    GLfloat rX, rY, rZ;
    GLfloat sX, sY, sZ;
    GLfloat reX, reY, reZ;

};

#endif // QOPENGLPANEL_H
