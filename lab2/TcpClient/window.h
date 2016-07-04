#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "client.h"

namespace Ui {
class Window;
}

class Window: public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

    void setUserName(const QString &value);

private slots:
    void on_textEdit_textChanged();
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();

    //void keyPressEvent(QKeyEvent*) override;

    void getTextFromServer();
    void clearText();

private:
    Ui::Window *ui;
    Client* client;
    QString currentText;
};

#endif // WINDOW_H
