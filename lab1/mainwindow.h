#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual void timerEvent(QTimerEvent*) override;
    ~MainWindow();

private slots:
    void on_addTruncatedConeButton_clicked();

    void on_addPrismaButton_clicked();

    void on_pushButton_clicked();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_checkBox_clicked();

    void on_comboBox_activated(int index);

    void on_actionClear_all_triggered();

    void on_actionGenerate_random_triggered();

    void on_openGLWidget_destroyed();

private:
    Ui::MainWindow* ui;
    Database* database;
};

#endif // MAINWINDOW_H
