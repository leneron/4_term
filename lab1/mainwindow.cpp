#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    database(new Database)
{
    ui->setupUi(this);
    startTimer(50);
}

void MainWindow::timerEvent(QTimerEvent*)
{
    ui->openGLWidget->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addTruncatedConeButton_clicked()
{
    ui->openGLWidget->addNewObject("truncatedCone");
}

void MainWindow::on_addPrismaButton_clicked()
{
    ui->openGLWidget->addNewObject("prisma");
}

void MainWindow::on_pushButton_clicked()
{
    ui->openGLWidget->changeColor();
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionSave_triggered()
{
    database->save(ui->openGLWidget);
}

void MainWindow::on_actionLoad_triggered()
{
    database->load(ui->openGLWidget);
    ui->openGLWidget->repaint();
}

void MainWindow::on_checkBox_clicked()
{
    bool value = ui->openGLWidget->getOnlySelectedVisible();
    ui->openGLWidget->setOnlySelectedVisible(!value);
}

void MainWindow::on_comboBox_activated(int index)
{
    ui->openGLWidget->setCurrentCamera(index);
    ui->openGLWidget->repaint();
}

void MainWindow::on_actionClear_all_triggered()
{
    ui->openGLWidget->clearObjects();
    ui->openGLWidget->repaint();
}

void MainWindow::on_actionGenerate_random_triggered()
{
    ui->openGLWidget->clearObjects();
    ui->openGLWidget->generateRandomScene();
    ui->openGLWidget->repaint();
}

void MainWindow::on_openGLWidget_destroyed()
{

}
