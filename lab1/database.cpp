#include <QtSql>
#include <vector>
#include "database.h"
#include "object.h"

Database::Database()
{
    db = QSqlDatabase::addDatabase("QMYSQL", "db");
    db.setHostName("localhost");
    db.setDatabaseName("lab1_scene");
    db.setUserName("root");
    db.setPassword("123456");
    bool ok = db.open();
    if (!ok)
        qDebug() <<  db.lastError().text();
}

Database::~Database()
{

}


void Database::save(OpenGLWidget *openGLWidget)
{
    bool ok = db.open();
    if (!ok)
        qDebug() <<  db.lastError().text();
    else
    {
        QSqlQuery query(db);
        query.exec("DELETE FROM figures");

        std::vector<Object*> data = openGLWidget->getObjects();
        query.prepare("INSERT INTO figures (id, filename, "
                      "positionX, positionY, positionZ, "
                      "rotationX, rotationY, rotationZ, "
                      "scaleX, scaleY, scaleZ, "
                      "colorR, colorG, colorB) "
                      "VALUES (:id, :filename, "
                      ":positionX, :positionY, :positionZ, "
                      ":rotationX, :rotationY, :rotationZ, "
                      ":scaleX, :scaleY, :scaleZ, "
                      ":colorR, :colorG, :colorB)");
        for (size_t i = 0; i < data.size(); i++)
        {
            query.bindValue(":id", (uint)(i + 1));

            query.bindValue(":filename", data[i]->getFileName().c_str());

            query.bindValue(":positionX", data[i]->getPosition().x());
            query.bindValue(":positionY", data[i]->getPosition().y());
            query.bindValue(":positionZ", data[i]->getPosition().z());

            query.bindValue(":rotationX", data[i]->getRotation().x());
            query.bindValue(":rotationY", data[i]->getRotation().y());
            query.bindValue(":rotationZ", data[i]->getRotation().z());

            query.bindValue(":scaleX", data[i]->getScale().x());
            query.bindValue(":scaleY", data[i]->getScale().y());
            query.bindValue(":scaleZ", data[i]->getScale().z());

            query.bindValue(":colorR", data[i]->getColor().x());
            query.bindValue(":colorG", data[i]->getColor().y());
            query.bindValue(":colorB", data[i]->getColor().z());

            query.exec();
        }
    }
    qDebug() << db.lastError();
    db.close();
}

void Database::load(OpenGLWidget *openGLWidget)
{
    bool ok = db.open();
    if (!ok)
        qDebug() <<  db.lastError().text();
    else
    {
        openGLWidget->clearObjects();
        QSqlQuery query(db);
        query.exec("SELECT id, filename, "
                      "positionX, positionY, positionZ, "
                      "rotationX, rotationY, rotationZ, "
                      "scaleX, scaleY, scaleZ, "
                      "colorR, colorG, colorB "
                      "FROM figures");
        while(query.next())
        {
            std::string filename = query.value(1).toString().toStdString();
            Object* object = new Object();
            object->initObject(filename);

            float positionX = query.value(2).toFloat();
            float positionY = query.value(3).toFloat();
            float positionZ = query.value(4).toFloat();
            object->setPosition(QVector3D(positionX, positionY, positionZ));

            float rotationX = query.value(5).toFloat();
            float rotationY = query.value(6).toFloat();
            float rotationZ = query.value(7).toFloat();
            object->setRotation(QVector3D(rotationX, rotationY, rotationZ));

            float scaleX = query.value(8).toFloat();
            float scaleY = query.value(9).toFloat();
            float scaleZ = query.value(10).toFloat();
            object->setScale(QVector3D(scaleX, scaleY, scaleZ));

            float colorR = query.value(11).toFloat();
            float colorG = query.value(12).toFloat();
            float colorB = query.value(13).toFloat();
            object->setColor(QVector3D(colorR, colorG, colorB));

            openGLWidget->addNewObject(object);
        }
    }
}
