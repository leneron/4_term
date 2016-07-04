#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

class DisplayWidget: public QWidget
{
    Q_OBJECT
public:
    explicit DisplayWidget(QWidget *parent = 0);

    void setImage(QImage* value);
    void setImage(const QString &fileName);

    QImage* getImage() const;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QImage* image;
};

#endif // DISPLAYWIDGET_H
