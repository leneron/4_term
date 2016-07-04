#include "axis.h"

Axis::Axis():
    verticesBuffer(QOpenGLBuffer::VertexBuffer)
{

}

void Axis::initAxis(const QVector3D &direction, const QVector3D &colorValue)
{
    color = colorValue;

    float vertices[verticesSize] = {
        direction.x() * LENGTH, direction.y() * LENGTH, direction.z() * LENGTH,
        -1 * direction.x() * LENGTH, -1 * direction.y() * LENGTH, -1 * direction.z() * LENGTH,
    };

    //buffers
    verticesBuffer.create();
    verticesBuffer.bind();
    verticesBuffer.allocate(vertices, verticesSize * sizeof(float));

    //ShadersProgram
    if (program.create())
    {
        program.addShaderFromSourceFile(QOpenGLShader::Vertex, "../lab1/axis.vert");
        program.addShaderFromSourceFile(QOpenGLShader::Fragment, "../lab1/axis.frag");
    }

    program.link();
    program.bind();
    program.enableAttributeArray("coord");
}

void Axis::paintAxis(Camera *camera)
{
    //line weight
    if (selected)
        glLineWidth(2.0);
    else
        glLineWidth(1.0);

    program.bind();

    verticesBuffer.bind();
    program.setAttributeBuffer("coord", GL_FLOAT, 0, 3);

    program.setUniformValue("cameraMatrix", camera->getCameraMatrix());
    program.setUniformValue("color", color);

    glDrawArrays(GL_LINES, 0, indicesSize);
}

