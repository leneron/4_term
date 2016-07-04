#include "displaywidget.h"
#include <QPainter>
#include <QImage>

DisplayWidget::DisplayWidget(QWidget *parent) : QWidget(parent)
{
    image = nullptr;
}

void DisplayWidget::setImage(const QString &fileName)
{
    if (image != nullptr)
        delete image;
    image = new QImage(fileName);
}

void DisplayWidget::paintEvent(QPaintEvent *event)
{
    if (image != nullptr)
    {

        int stepX = std::max(this->width(), image->width()) / image->width();
        int stepY = std::max(this->height(), image->height()) / image->height();

        QPainter painter(this);

        for (int i = 0; i < image->width(); i++)
            for(int j = 0; j < image->height(); j++)
            {
                QColor color = QColor(image->pixel(i, j));
                painter.fillRect(QRect(i * stepX, j * stepY, stepX, stepY),
                                 color);
            }

    }
}
void DisplayWidget::setImage(QImage* value)
{
    QImage* newImage = new QImage(*value);
    image = newImage;
}

QImage* DisplayWidget::getImage() const
{
    return image;
}


