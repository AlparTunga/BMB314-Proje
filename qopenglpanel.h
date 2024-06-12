#ifndef QOPENGLPANEL_H
#define QOPENGLPANEL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtMath>

class QOpenGLPanel : public QOpenGLWidget
{
    Q_OBJECT

public:
    QOpenGLPanel(QWidget *parent = nullptr);
    ~QOpenGLPanel();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:


    QOpenGLFunctions *getGLFunctions();
    QOpenGLExtraFunctions *getGLExtraFunctions();
    bool initializeShaderProgram(QString vertex, QString fragment, QOpenGLFunctions *f);
    bool checkGLError(QOpenGLFunctions *f, QString functionCall);
    const char* readShaderSource(QString filename);
    void setupOrthographicProjection(); // Bu satırı ekleyin

    GLuint progID;
    GLuint vertID;
    GLuint fragID;
    GLuint arrays;
    GLuint triangleData;
    GLuint position;
    GLuint color;
    GLuint translateMatrixID;
    GLuint rotateMatrixID;
    GLuint scaleMatrixID;
    GLuint reflectMatrixID;

    QMatrix4x4 translateMatrix;
    QMatrix4x4 rotateMatrix;
    QMatrix4x4 scaleMatrix;
    QMatrix4x4 reflectMatrix;

    float tX, tY, tZ;
    float rX, rY, rZ;
    float sX, sY, sZ;
    float rDegree;
    QVector3D ambientColor;

};

#endif // QOPENGLPANEL_H
