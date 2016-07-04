#include "dialogproperties.h"
#include "ui_dialogproperties.h"

DialogProperties::DialogProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProperties)
{
    ui->setupUi(this);
}

DialogProperties::~DialogProperties()
{
    delete ui;
}

void DialogProperties::on_buttonBox_accepted()
{
    float value_X = float(ui->doubleSpinBox_X->value());
    float value_Y = float(ui->doubleSpinBox_Y->value());
    float value_Z = float(ui->doubleSpinBox_Z->value());
    result = QVector3D(value_X, value_Y, value_Z);
}

QVector3D DialogProperties::getResult() const
{
    return result;
}

void DialogProperties::init(const float &value)
{
    ui->doubleSpinBox_X->setValue(value);
    ui->doubleSpinBox_Y->setValue(value);
    ui->doubleSpinBox_Z->setValue(value);
}
