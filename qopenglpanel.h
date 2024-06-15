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
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLVertexArrayObject>
#include <QtOpenGL/QOpenGLBuffer>
#include <vector>

class QOpenGLPanel : public QOpenGLWidget
{
    Q_OBJECT

public:
    QOpenGLPanel(QWidget *parent = nullptr);
    ~QOpenGLPanel();
    void setCameraMatrix();
    void setProjectionMatrix();
    void translate(GLfloat x, GLfloat y, GLfloat z);
    void rotate(GLfloat degree, GLfloat x, GLfloat y, GLfloat z);
    void scale(GLfloat x, GLfloat y, GLfloat z);
    void lookAt(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat cx, GLfloat cy, GLfloat cz, GLfloat ux, GLfloat uy, GLfloat uz);
    void perspective(GLfloat angle, GLfloat ratio, GLfloat near, GLfloat far);
    void resetScene();
    void mousePressEvent(QMouseEvent* event) override;
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
    //void setupOrthographicProjection();




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

    GLuint projectionMatrixID, cameraMatrixID;
    QMatrix4x4 projectionMatrix, cameraMatrix;
    GLfloat camEyeX, camEyeY, camEyeZ;
    QVector3D cameraEye;
    GLfloat camCenterX, camCenterY, camCenterZ;
    QVector3D cameraCenter;
    GLfloat camUpX, camUpY, camUpZ;
    QVector3D cameraUp;
    GLfloat verticalAngle, aspectRatio, nearPlane, farPlane;

};

#endif // QOPENGLPANEL_H
