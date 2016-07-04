#include "openglwidget.h"

std::vector<Object *> OpenGLWidget::getObjects() const
{
    return objects;
}

bool OpenGLWidget::getOnlySelectedVisible() const
{
    return onlySelectedVisible;
}

void OpenGLWidget::setOnlySelectedVisible(bool value)
{
    onlySelectedVisible = value;
}

void OpenGLWidget::setCurrentCamera(int value)
{
    currentCamera = value;
}

void OpenGLWidget::generateRandomScene()
{
    // Creating random scene
    srand(time(0));
    int figuresN = rand() % 7 + 3;

    for (int i = 0; i < figuresN; i++)
    {
        Object* object = new Object();
        int h = rand() % 2;
        if (h)
            object->initObject("truncatedCone");
        else
            object->initObject("prisma");
        object->setPosition(QVector3D(pow(-1, rand() % 2) * (rand() % 100) / 100 * 8 , pow(-1, rand() % 2) * (rand() % 100) / 100 * 8, pow(-1, rand() % 2) * (rand() % 100) / 100 * 8));
        object->setRotation(QVector3D(rand() % 360, 0, 0));
        objects.push_back(object);
    }
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    vao.create(); //vertex array object
    vao.bind();

    //setting the axes
    Axis* axisX = new Axis();
    Axis* axisY = new Axis();
    Axis* axisZ = new Axis();

    axisX->initAxis(QVector3D(1, 0, 0), QVector3D(1, 0, 0));
    axisY->initAxis(QVector3D(0, 1, 0), QVector3D(0, 1, 0));
    axisZ->initAxis(QVector3D(0, 0, 1), QVector3D(0, 0, 1));

    axes.push_back(axisX);
    axes.push_back(axisY);
    axes.push_back(axisZ);

    //we need to initialize at least one object
    //for correct shader linking (after creating vao & vbo)
    Object* empty = new Object();
    empty->initObject("prisma");
    delete empty;

    //framebuffer object
    surface = new QOffscreenSurface();
    surface->create();
    context()->makeCurrent(surface);
    selectionFrameBufferObject = new QOpenGLFramebufferObject(this->width(), this->height());
    selectionFrameBufferObject->setAttachment(QOpenGLFramebufferObject::Depth);
}

void OpenGLWidget::paintGL()
{
    makeCurrent();

    glClearColor(0.4, 0.4, 0.4, 0);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    for (size_t i = 0; i < objects.size(); i++)
    {
        if ((objects[i]->getSelected()) || (!onlySelectedVisible))
        {
           objects[i]->paintObject(cameras[currentCamera]);
        }
    }

    for (size_t i = 0; i < axes.size(); i++)
    {
        axes[i]->paintAxis(cameras[currentCamera]);
    }

}

int OpenGLWidget::paintNumbers(int x, int y)
{

    context()->makeCurrent(surface);
    selectionFrameBufferObject->bind();

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    int number;

    for (size_t i = 0; i < objects.size(); i++)
    {
        if ((objects[i]->getSelected()) || (!onlySelectedVisible))
        {
            objects[i]->paintNumber(cameras[currentCamera], i);
        }
    }

    QImage coloredFiguresImage = selectionFrameBufferObject->toImage();

    //color in shader in red (simplified version)  = (figure's number + 1) / range-255
    //color on the image -- number from range [1, 255], 0 is an emply space
    number = qRed(coloredFiguresImage.pixel(x, y)) - 1;

    selectionFrameBufferObject->release();
    return number;
}

void OpenGLWidget::deselectAll()
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        objects[i]->setSelected(false);
    }
}

void OpenGLWidget::keyPressEvent(QKeyEvent* event)
{

    if (event->key() == Qt::Key_R)
    {
        //set rotation
        dialogProperties->setWindowTitle("Rotation");
        dialogProperties->init(0.0);
        if (dialogProperties->exec() == QDialog::Accepted)
        {
            QVector3D result = dialogProperties->getResult();
            setRotation(result);
        }
    }
    else if (event->key() == Qt::Key_T)
    {
        //set translation
        dialogProperties->setWindowTitle("Translation");
        dialogProperties->init(0.0);
        if (dialogProperties->exec() == QDialog::Accepted)
        {
            QVector3D result = dialogProperties->getResult();
            setTranslation(result);
        }
    }
    else if (event->key() == Qt::Key_S)
    {
        //set scale
        dialogProperties->setWindowTitle("Scale");
        dialogProperties->init(1.0);
        if (dialogProperties->exec() == QDialog::Accepted)
        {
            QVector3D result = dialogProperties->getResult();
            setScale(result);
        }
    }
    repaint();
}

void OpenGLWidget::mousePressEvent(QMouseEvent* event)
{
    //define the number of the selection
    int number = paintNumbers(event->x(), event->y());
    qDebug() << number;

    //if we clicked on the empty space, clear the selection vector and deselect all objects
    if (number == EMPTY_SPACE)
    {
        deselectAll();
    }
    else if (event->button() == Qt::LeftButton)
    {
        //if shift is not pressed
        if (!(event->modifiers() & Qt::ShiftModifier))
        {
            deselectAll();
        }
        bool value = objects[number]->getSelected();
        objects[number]->setSelected(!value);
    }
}

void OpenGLWidget::setTranslation(const QVector3D &vector)
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (objects[i]->getSelected())
            objects[i]->setPosition(objects[i]->getPosition() + vector);
    }
    repaint();
}

void OpenGLWidget::setRotation(const QVector3D &vector)
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (objects[i]->getSelected())
            objects[i]->setRotation(objects[i]->getRotation() + vector);
    }
    repaint();
}

void OpenGLWidget::setScale(const QVector3D &vector)
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (objects[i]->getSelected())
        {
            QVector3D currentVector = objects[i]->getScale();
            objects[i]->setScale(QVector3D(currentVector.x() * vector.x(), currentVector.y() * vector.y(), currentVector.z() * vector.z()));
        }
    }
    repaint();
}

void OpenGLWidget::clearObjects()
{
    while (!objects.empty())
    {
        delete objects[0];
        objects.erase(objects.begin());
    }
}

void OpenGLWidget::changeColor()
{
    if (colorDialog->exec() == QDialog::Accepted)
    {
        for (size_t i = 0; i < objects.size(); i++)
        {
            if (objects[i]->getSelected())
            {
                QColor color = colorDialog->currentColor();
                QVector3D normalizedColor = QVector3D(color.redF(), color.greenF(), color.blueF());
                objects[i]->setColor(normalizedColor);
            }
        }
    }
    repaint();
}

void OpenGLWidget::addNewObject(const std::string& fileName)
{
    Object* newObject = new Object();
    newObject->initObject(fileName);
    objects.push_back(newObject);
    repaint();
}

void OpenGLWidget::addNewObject(Object *newObject)
{
    objects.push_back(newObject);
    repaint();
}

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    onlySelectedVisible = false;
    dialogProperties = new DialogProperties;
    colorDialog = new QColorDialog;
    currentCamera = 0;

    const int numberOfCameras = 4;
    for (int i = 0; i < numberOfCameras; i++)
    {
        Camera* camera = new Camera();
        camera->initCamera(Camera::Type(i));
        cameras.push_back(camera);
    }
}

OpenGLWidget::~OpenGLWidget()
{
    clearObjects();

    for (size_t i = cameras.size() - 1; i >= 0; i--)
    {
        delete cameras[i];
        cameras.pop_back();
    }

    for (size_t i = axes.size() - 1; i >= 0; i--)
    {
        delete axes[i];
        axes.pop_back();
    }
}
