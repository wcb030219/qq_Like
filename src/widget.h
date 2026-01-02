#ifndef WIDGET_H
#define WIDGET_H

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include "registeruser.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void on_btn_close_clicked();
    void on_btn_login_clicked();


    void on_btn_register_clicked();

private:
    Ui::Widget *ui;
    QPoint m_dragPosition;

    QLineEdit *le_username = nullptr;
    QLineEdit *le_password = nullptr;
    QPushButton *btn_login = nullptr;

    registeruser m_register;

};
#endif // WIDGET_H
