#ifndef AXE_H
#define AXE_H

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "camera.h"

class Axis
{
public:
    Axis();
    ~Axis();

    void initAxis(const QVector3D& direction, const QVector3D& colorValue);
    void paintAxis(Camera* camera);

private:
    const float LENGTH = 50.0;
    const uint indicesSize = 2;
    const uint verticesSize = 6;

    QOpenGLBuffer verticesBuffer;

    QOpenGLShaderProgram program;
    QVector3D color;
    bool selected;
};

#endif // AXE_H
