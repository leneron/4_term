#ifndef OBJ_H
#define OBJ_H

#include <string>
#include <fstream>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "camera.h"

class Object
{
public:
    Object();
    virtual ~Object();

    void paintObject(Camera* camera);
    void initObject(std::string objectFileName);
    void paintNumber(Camera* camera, int number);

    void setSelected(bool value);
    bool getSelected() const;

    QVector3D getPosition() const;
    void setPosition(const QVector3D &value);

    QVector3D getRotation() const;
    void setRotation(const QVector3D &value);

    QVector3D getScale() const;
    void setScale(const QVector3D &value);

    QVector3D getColor() const;
    void setColor(const QVector3D &value);

    void changeColor();
    std::string getFileName() const;

protected:
    bool selected;
    QVector3D color;
    std::string fileName;

    QOpenGLBuffer verticesBuffer;
    QOpenGLBuffer indicesBuffer;
    QOpenGLBuffer uvBuffer;
    QOpenGLBuffer normalsBuffer;

    uint indicesSize;
    uint verticesSize;
    uint uvSize;
    uint normalsSize;

    QOpenGLTexture *texture;

    QOpenGLShaderProgram program;
    QOpenGLShaderProgram programNumbers;

    QVector3D position;
    QVector3D rotation;
    QVector3D scale;

    void loadModel(const std::string& filename, float* &vertices, float* &uv, float* &normals, uint* &indices, uint &verticesSize, uint &uvSize, uint &normalsSize, uint &indicesSize);
    QMatrix4x4 modelMatrix() const;
};

#endif // OBJ_H
