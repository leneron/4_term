#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    client = new Client(this);

    connect(client, SIGNAL(getTextFromServer()), this, SLOT(getTextFromServer()));
    connect(client, SIGNAL(clearText()), this, SLOT(clearText()));
}

Window::~Window()
{
    delete ui;
}

void Window::setUserName(const QString &value)
{
    client->setUserName(value);
}

void Window::on_textEdit_textChanged()
{  
    QString text = ui->textEdit->toPlainText();
    if (currentText != text)
    {
        currentText = text;
        client->setText(currentText);
        client->sendTextToServer();
    }
}

void Window::on_actionConnect_triggered()
{
    client->connect();
}

void Window::on_actionDisconnect_triggered()
{
    client->disconnect();
}

//void Window::keyPressEvent(QKeyEvent *)
//{
//    //updating the text in client and sending it to the server
//    client->setText(ui->textEdit->toPlainText());
//    client->sendTextToServer();
//}

void Window::getTextFromServer()
{
    //handling the signal updateText() from the client
    QString text = client->getText();
    currentText = text;
    ui->textEdit->setText(text);
}

void Window::clearText()
{
    currentText = "";
    ui->textEdit->setText("");
}

