#include "qopenglpanel.h"

QOpenGLPanel::QOpenGLPanel(QWidget *parent) : QOpenGLWidget(parent)
{
}

QOpenGLPanel::~QOpenGLPanel()
{
}

QOpenGLFunctions* QOpenGLPanel::getGLFunctions()
{
    return QOpenGLContext::currentContext()->functions();
}

QOpenGLExtraFunctions* QOpenGLPanel::getGLExtraFunctions()
{
    return QOpenGLContext::currentContext()->extraFunctions();
}

bool QOpenGLPanel::initializeShaderProgram(QString vertex, QString fragment, QOpenGLFunctions *f)
{
    progID = f->glCreateProgram();

    vertID = f->glCreateShader(GL_VERTEX_SHADER);
    const char* vertSource = readShaderSource(vertex);
    f->glShaderSource(vertID, 1, &vertSource, nullptr);
    f->glCompileShader(vertID);
    f->glAttachShader(progID, vertID);

    fragID = f->glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragSource = readShaderSource(fragment);
    f->glShaderSource(fragID, 1, &fragSource, nullptr);
    f->glCompileShader(fragID);
    f->glAttachShader(progID, fragID);

    f->glLinkProgram(progID);

    return checkGLError(f, "Linking Shader Program");
}

bool QOpenGLPanel::checkGLError(QOpenGLFunctions *f, QString functionCall)
{
    GLenum error = f->glGetError();
    if (error == GL_NO_ERROR) {
        qDebug() << "No OpenGL Error while " << functionCall;
        return true;
    } else {
        qDebug() << "Error " << error << " while " << functionCall;
        return false;
    }
}

const char* QOpenGLPanel::readShaderSource(QString filename)
{
    const char* source = nullptr;
    QFile shaderFile(filename);
    if (!shaderFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Error while reading shader source file";
        return source;
    }

    QTextStream in(&shaderFile);
    QString text = in.readAll();
    shaderFile.close();
    QByteArray ba = text.toLocal8Bit();
    source = ba.data();

    return source;
}

void QOpenGLPanel::initializeGL()
{
    QOpenGLFunctions *f = getGLFunctions();
    f->initializeOpenGLFunctions();
    QOpenGLExtraFunctions *ef = getGLExtraFunctions();
    ef->initializeOpenGLFunctions();

    f->glClearColor(0.0, 1.0, 1.0, 1.0);

    initializeShaderProgram(":simple.vert", ":simple.frag", f);

    // Setup orthographic projection matrix
    setupOrthographicProjection();

    translateMatrixID = f->glGetUniformLocation(progID, "translateMatrix");
    rotateMatrixID = f->glGetUniformLocation(progID, "rotateMatrix");
    scaleMatrixID = f->glGetUniformLocation(progID, "scaleMatrix");
    reflectMatrixID = f->glGetUniformLocation(progID, "reflectMatrix");

    ef->glGenVertexArrays(2, &arrays);
    f->glGenBuffers(1, &triangleData);
    ef->glBindVertexArray(arrays);
    f->glBindBuffer(GL_ARRAY_BUFFER, triangleData);

    checkGLError(f, "Generating and Binding Vertex Arrays");

    float vertAndColors[1024] = {
        //solBİZDENTARAF
        -1.0f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f,


        //sağBİZDENTARAF
        -1.0f, 0.3f, 0.0f,1.0f, 0.0f, 0.0f,
        1.0f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,

        //solBİZDENTARAF2
        -0.5f, 0.6f, 0.0f,0.0f, 0.0f, 0.0f,
        -0.5f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f,

        //solBİZDENTARAF2_2
        -0.5f, 0.6f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,

        //solBİZDENTARAF2_25
        -0.5f, 0.6f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.3f, -0.7f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.6f, -0.7f, 0.0f, 0.0f, 0.0f,


        //sağBİZDENTARAF2
        -0.5f, 0.6f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.6f, 0.0f, 0.0f, 0.0f, 0.0f,

        //sağBİZDENTARAF2_2
        0.5f, 0.6f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f,

        //sağBİZDENTARAF2_25
        -1.0f, 0.3f, -0.7f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.6f, 0.0f, 0.0f, 0.0f, 0.0f,

        //sağyansağARKA
        1.0f, 0.3f, -0.7f, 0.0f, 0.0f, 1.0f,
        1.0f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,

        //sağyansolARKA
        1.0f, -0.3f, -0.7f, 0.0f, 0.0f, 1.0f,
        1.0f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.3f, -0.7f, 0.0f, 0.0f, 1.0f,


        //solyansağÖN
        -1.0f, -0.3f, -0.7f, 0.0f, 0.0f, 1.0f,
        -1.0f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f,

        //solyansolÖN
        -1.0f, 0.3f, -0.7f, 0.0f, 0.0f, 1.0f,
        -1.0f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -0.3f, -0.7f, 0.0f, 0.0f, 1.0f,

        //zekssol
        -1.0f, 0.3f, -0.7f, 1.0f, 0.0f, 0.0f,
        -1.0f, -0.3f, -0.7f, 1.0f, 0.0f, 0.0f,
        1.0f, -0.3f, -0.7f, 1.0f, 0.0f, 0.0f,

        //zekssağ
        -1.0f, 0.3f, -0.7f, 1.0f, 0.0f, 0.0f,
        1.0f, -0.3f, -0.7f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.3f, -0.7f, 1.0f, 0.0f, 0.0f,

        //zekssağ2
        -0.5f, 0.6f, -0.7f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.3f, -0.7f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.6f, -0.7f, 0.0f, 0.0f, 0.0f,

        //zekssağ2_2
        0.5f, 0.6f, -0.7f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.3f, -0.7f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.3f, -0.7f, 1.0f, 0.0f, 0.0f,

        //zekssağ2_25
        1.0f, 0.3f, -0.7f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.6f, 0.0f, 0.0f, 0.0f, 0.0f,

        //zekssol2
        -0.5f, 0.6f, -0.7f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.3f, -0.7f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.3f, -0.7f, 0.0f, 0.0f, 0.0f,

        //zekssol2_2
        -0.5f, 0.6f, -0.7f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.3f, -0.7f, 1.0f, 0.0f, 0.0f,
        -1.0f, 0.3f, -0.7f, 1.0f, 0.0f, 0.0f,

        //zekssol2_25
        0.5f, 0.6f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.6f, -0.7f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.3f, -0.7f, 0.0f, 0.0f, 0.0f,

        //ustkare
        -1.0f, 0.3f, -0.7f, 0.0f, 0.0f, 1.0f,
        -1.0f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,

        -1.0f, 0.3f, -0.7f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.3f, -0.7f, 0.0f, 0.0f, 1.0f,

        //ustkare2
        -0.5f, 0.6f, -0.7f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.6f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.6f, 0.0f, 0.0f, 0.0f, 0.0f,

        -0.5f, 0.6f, -0.7f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.6f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.6f, -0.7f, 0.0f, 0.0f, 0.0f,

        //altkare
        -1.0f, -0.3f, -0.7f, 0.0f, 0.0f, 1.0f,
        -1.0f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f,

        -1.0f, -0.3f, -0.7f, 0.0f, 0.0f, 1.0f,
        1.0f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -0.3f, -0.7f, 0.0f, 0.0f, 1.0f














    };

    f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertAndColors), vertAndColors, GL_STATIC_DRAW);

    position = f->glGetAttribLocation(progID, "position");
    f->glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
    f->glEnableVertexAttribArray(position);

    color = f->glGetAttribLocation(progID, "color");
    f->glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
    f->glEnableVertexAttribArray(color);

    tX = 0.0f, tY = 0.0f, tZ = 0.0f;
    rX = 0.0f, rY = 0.3f, rZ = 0.0f;
    sX = 0.5f, sY = 0.5f, sZ = 0.5f;
    rDegree = 0.0f;
}

void QOpenGLPanel::setupOrthographicProjection()
{
    QOpenGLFunctions *f = getGLFunctions();

    // Set up orthographic projection matrix
    QMatrix4x4 orthoMatrix;
    orthoMatrix.setToIdentity();
    orthoMatrix.ortho(-2.0f, 2.0f, -2.0f, 2.0f, -1.0f, 1.0f);

    // Get the location of the projection matrix in the shader program
    GLint projMatrixID = f->glGetUniformLocation(progID, "projMatrix");

    // Pass the orthographic projection matrix to the shader
    f->glUseProgram(progID);
    f->glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, orthoMatrix.constData());
}

void QOpenGLPanel::paintGL()
{
    QOpenGLFunctions *f = getGLFunctions();
    QOpenGLExtraFunctions *ef = getGLExtraFunctions();
    f->glClear(GL_COLOR_BUFFER_BIT);

    translateMatrix.setToIdentity();
    tX = 0.0f * qCos(qDegreesToRadians(rDegree));
    tZ = 0.0f * qSin(qDegreesToRadians(rDegree));
    translateMatrix.translate(tX, tY, tZ);

    rotateMatrix.setToIdentity();
    rDegree += 0.3f;
    rotateMatrix.rotate(rDegree, rX, rY, rZ);

    scaleMatrix.setToIdentity();
    scaleMatrix.scale(sX, sY, sZ);

    reflectMatrix.setToIdentity();

    f->glUseProgram(progID);

    f->glUniformMatrix4fv(translateMatrixID, 1, GL_FALSE, translateMatrix.constData());
    f->glUniformMatrix4fv(rotateMatrixID, 1, GL_FALSE, rotateMatrix.constData());
    f->glUniformMatrix4fv(scaleMatrixID, 1, GL_FALSE, scaleMatrix.constData());
    f->glUniformMatrix4fv(reflectMatrixID, 1, GL_FALSE, reflectMatrix.constData());

    ef->glBindVertexArray(arrays);
    f->glDrawArrays(GL_TRIANGLES, 0, 128);

    update();
}

void QOpenGLPanel::resizeGL(int width, int height)
{
    // Handle window resizing if needed
}
