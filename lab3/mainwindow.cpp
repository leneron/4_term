#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    network = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog dialog;
    //just a single image to recognize
    dialog.setFileMode(QFileDialog::ExistingFile);

    QString fileName = dialog.getOpenFileName();
    if (!fileName.isEmpty())
    {
        if (ui->actionOpen_training_examples->isEnabled())
            ui->recognizeButton->setEnabled(true);

        ui->originalWidget->setImage(fileName);
        ui->originalWidget->repaint();
    }
}

void MainWindow::on_actionOpen_training_examples_triggered()
{
    QFileDialog dialog;
    //can train on many examples
    dialog.setFileMode(QFileDialog::ExistingFiles);

    QStringList fileNames = dialog.getOpenFileNames();
    if (!fileNames.empty())
    {
        network = new HopfieldNetwork(fileNames);
        ui->menuFile->setEnabled(true);
    }
}

void MainWindow::on_recognizeButton_clicked()
{
    QImage* input = ui->originalWidget->getImage();
    QImage* output = network->recognize(input);
    ui->recognizedWidget->setImage(output);
    ui->recognizedWidget->repaint();
}
