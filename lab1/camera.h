#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

class Camera
{
public:
    Camera();
    ~Camera();

    enum Type {PERSPECTIVE, ORTHO_XY, ORTHO_XZ, ORTHO_YZ};

    void initCamera(const Type& typeValue = PERSPECTIVE);
    QMatrix4x4 getCameraMatrix() const;

private:
    QMatrix4x4 cameraMatrix;
    QVector3D cameraPosition;

    Type type;
};

#endif // CAMERA_H
