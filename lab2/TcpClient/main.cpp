#include "window.h"
#include <QApplication>
#include "nicknamedialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString nickname = "";
    while (nickname == "")
    {
        NicknameDialog dialog;

        if (dialog.exec() == QDialog::Accepted)
        {
            nickname = dialog.getResult();
        }
        else return 0;
    }

    Window w;
    w.show();
    w.setUserName(nickname);

    return a.exec();
}
