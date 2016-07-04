#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QVector3D>
#include <string>
#include "openglwidget.h"

class Database
{
public:
    Database();
    ~Database();

    void save(OpenGLWidget* openGLWidget);
    void load(OpenGLWidget* openGLWidget);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
