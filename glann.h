#ifndef GLANN_H
#define GLANN_H

#include <QGLShaderProgram>
#include <QGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QGLPixelBuffer>

#include <QBasicTimer>
#include <QTime>
#include <QImage>
#include <QVector>

#include "playground.h"


enum MODE{start,fwPropagation,fwFinished,backPropagation,backFinished};

class GLANN : public QGLWidget,protected QGLFunctions
{
    Q_OBJECT

public:
    GLANN(unsigned int neuronsCount, Playground *weightmap = 0);

    bool setInput(QVector<unsigned int> input);
    bool setError(QVector<unsigned int> error);
    QVector<unsigned int> getOutput();
    MODE getMode();

    unsigned int getNeuronsCount();

protected:

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void timerEvent(QTimerEvent *);

private:
    bool propagateInput();
    bool propagateBckWrds();
    void justDrawMaps();

    void initShader();
    void initTextures();

    unsigned int convertToPixels(float activationFl);
    float convertFromPixels(unsigned int activationUI);

    QBasicTimer timer;

    QImage *mWeightmap;
    QImage *mPropagation;

    QGLShaderProgram program;

    GLuint pixelsActivation;
    GLuint pixelsWeightmap;
    unsigned char *renderedPropagation;
    unsigned char *renderedWeights;

    unsigned int mNeurons;
    unsigned int propCycle;

    MODE mode = start;

    //Input Variables
    float x;
    float y;
};

#endif // GLANN_H
