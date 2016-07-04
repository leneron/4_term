#ifndef DIALOGPROPERTIES_H
#define DIALOGPROPERTIES_H

#include <QDialog>
#include <QVector3D>

namespace Ui {
class DialogProperties;
}

class DialogProperties : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProperties(QWidget *parent = 0);
    ~DialogProperties();

    QVector3D getResult() const;
    void init(const float& value);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogProperties *ui;

    QVector3D result;
};

#endif // DIALOGPROPERTIES_H
