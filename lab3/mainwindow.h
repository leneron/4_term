#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hopfieldnetwork.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionOpen_training_examples_triggered();

    void on_recognizeButton_clicked();

private:
    Ui::MainWindow *ui;
    HopfieldNetwork* network;
};

#endif // MAINWINDOW_H
