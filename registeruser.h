#ifndef REGISTERUSER_H
#define REGISTERUSER_H

#include "stusql.h"

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class registeruser;
}

class registeruser : public QDialog
{
    Q_OBJECT

public:
    explicit registeruser(QWidget *parent = nullptr);
    ~registeruser();


    void closeEvent(QCloseEvent *event);
    void applyStyle();
private slots:
    void on_btn_submit_clicked();
    bool validateInput();


signals:
    void registerComplete(const QString &username);
    void backToLogin();
private:
    Ui::registeruser *ui;

    QLineEdit *repeat_user;
    QLineEdit *repeat_paw;
    QLineEdit *repeat_enpaw;
    QPushButton *btn_submit;
};

#endif // REGISTERUSER_H
