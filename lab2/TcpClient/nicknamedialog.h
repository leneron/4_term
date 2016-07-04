#ifndef NICKNAMEDIALOG_H
#define NICKNAMEDIALOG_H

#include <QDialog>

namespace Ui {
class NicknameDialog;
}

class NicknameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NicknameDialog(QWidget *parent = 0);
    ~NicknameDialog();

    QString getResult() const;

private slots:
    void on_buttonBox_accepted();


private:
    Ui::NicknameDialog *ui;

    QString result;
};

#endif // NICKNAMEDIALOG_H
