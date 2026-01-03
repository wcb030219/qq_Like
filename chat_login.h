#ifndef CHAT_LOGIN_H
#define CHAT_LOGIN_H

#include <QDialog>
#include<QVector>
#include <QWidget>
#include<QMessageBox>

namespace Ui {
class chat_login;
}

class chat_login : public QDialog
{
    Q_OBJECT

public:
    explicit chat_login(QWidget *parent = nullptr, const QString &loggedInUser = "");
    ~chat_login();

    void closeEvent(QCloseEvent *event) override;

signals:
    void windowClosed();

private:
    Ui::chat_login *ui;
    //初始状态为未打开登录后的界面
    QVector<bool> isShow;
    QString currentUser;
    QVector<QToolButton*> buttons;
};

#endif // CHAT_LOGIN_H
