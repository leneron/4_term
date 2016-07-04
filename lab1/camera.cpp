#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::initCamera(const Type& typeValue)
{
    type = typeValue;
    cameraMatrix.setToIdentity();
    switch(type)
    {
        case PERSPECTIVE:
        {
            cameraPosition = QVector3D(10, 10, 10);
            cameraMatrix.perspective(70, 1, 0.05, 100);
            cameraMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), QVector3D(0, 1, 0));
            break;
        }
        case ORTHO_XY:
        {
            cameraMatrix.ortho(-15, 15, -15, 15, 0.001, 100);
            cameraMatrix.translate(QVector3D(0, 0, -20));
            break;
        }
        case ORTHO_XZ:
        {
            cameraMatrix.ortho(-15, 15, -15, 15, 0.001, 100);
            cameraMatrix.rotate(90, QVector3D(1, 0, 0));
            cameraMatrix.rotate(90, QVector3D(0, 1, 0));
            cameraMatrix.translate(QVector3D(0, -20, 0));
            break;
        }
        case ORTHO_YZ:
        {
            cameraMatrix.ortho(-15, 15, -15, 15, 0.001, 100);
            cameraMatrix.rotate(90, QVector3D(0, 1, 0));
            cameraMatrix.translate(QVector3D(20, 0, 0));
            break;
        }
    }
}

QMatrix4x4 Camera::getCameraMatrix() const
{
    return cameraMatrix;
}


