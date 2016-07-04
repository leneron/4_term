#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <vector>
#include <QDebug>
#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QMatrix>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QMessageBox>
#include <QOpenGLFramebufferObject>
#include <QOffscreenSurface>
#include <QColorDialog>
#include <random>
#include <ctime>
#include <string>
#include "dialogproperties.h"
#include "camera.h"
#include "object.h"
#include "axis.h"

class OpenGLWidget: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
protected:
    //constant for defining the empty space in selection
    const int EMPTY_SPACE = -1;

    DialogProperties* dialogProperties;
    QColorDialog* colorDialog;

    QOpenGLVertexArrayObject vao;

    std::vector<Object*> objects;
    std::vector<Camera*> cameras;
    int currentCamera;
    QOpenGLFramebufferObject* selectionFrameBufferObject;
    QOffscreenSurface* surface;
    std::vector<Axis*> axes;

    bool onlySelectedVisible;

    void initializeGL();
    void paintGL();

    int paintNumbers(int x, int y);
    void deselectAll();

    //Editing
    void keyPressEvent(QKeyEvent* event);
    //Selection
    void mousePressEvent(QMouseEvent* event);

    void setTranslation(const QVector3D& vector);
    void setRotation(const QVector3D& vector);
    void setScale(const QVector3D& vector);

public:
    OpenGLWidget(QWidget* parent = 0);
    ~OpenGLWidget();

    void addNewObject(const std::string &fileName);
    void addNewObject(Object* newObject);
    void changeColor();
    std::vector<Object *> getObjects() const;
    void clearObjects();
    bool getOnlySelectedVisible() const;
    void setOnlySelectedVisible(bool value);
    void setCurrentCamera(int value);
    void generateRandomScene();
};

#endif // OPENGLWIDGET_H
