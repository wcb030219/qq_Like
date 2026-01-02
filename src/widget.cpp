#include "widget.h"
#include "ui_widget.h"

#include <QMouseEvent>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QLineEdit>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);

    QLabel *avatarLabel = new QLabel(this);
    QPixmap original(":/resource/qq.png");

    // 创建圆形图片
    QPixmap circular(100, 100);
    circular.fill(Qt::transparent);
    avatarLabel->setGeometry(150, 80, 100, 100);
    QPainter painter(&circular);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(original.scaled(100, 100,
                                            Qt::IgnoreAspectRatio,
                                            Qt::SmoothTransformation)));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(0, 0, 100, 100);
    painter.end();

    avatarLabel->setPixmap(circular);

    // 或者使用样式表实现圆角
    avatarLabel->setStyleSheet(
        "QLabel {"
        "    border-radius: 50px;"  // 50px半径 = 100px直径的圆形
        "    border: 2px solid #4CAFEA;"  // 蓝色边框
        "}"
        );


    le_username = new QLineEdit(this);
    le_password = new QLineEdit(this);

    le_username->setGeometry(40,210,320,50);
    le_password->setGeometry(40,280,320,50);

    le_username->setStyleSheet(
        "border: 1px solid #DDDDDD;"
        "border-radius: 5px;"
        "padding: 10px 15px;"
        "font-size: 15px;"
        "background-color: #FAFAFA;"
        );

    le_password->setStyleSheet(
        "border: 1px solid #DDDDDD;"
        "border-radius: 5px;"
        "padding: 10px 15px;"
        "font-size: 15px;"
        "background-color: #FAFAFA;"
        );


    le_username->setPlaceholderText("输入账号");
    le_password->setPlaceholderText("输入密码");
    le_password->setEchoMode(QLineEdit::Password);

    btn_login = new QPushButton(this);

    btn_login -> move(40,400);
    btn_login -> setText(tr("登录"));
    btn_login ->setFixedSize(320,50);
    QString btnStyle =
        "QPushButton {"
        "    background-color: #4CAFEA;"  // 默认蓝色
        "    color: white;"
        "    border-radius: 10px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    border: none;"
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #3A9BDA;"  // 悬停时深蓝色
        "}"
        "QPushButton:pressed {"
        "    background-color: #2A8BCA;"  // 按下时更深蓝色
        "    padding: 12px 8px 8px 12px;"  // 模拟按下效果
        "}";
     btn_login->setStyleSheet(btnStyle);


    connect(btn_login, &QPushButton::clicked, this, &Widget::on_btn_login_clicked);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
   if (event->button() == Qt::LeftButton) {
    m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
    event->accept();
}
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}



void Widget::on_btn_close_clicked()
{
    exit(0);
}


void Widget::on_btn_login_clicked()
{

}






void Widget::on_btn_register_clicked()
{
    registeruser *regDialog = new registeruser(this);

    // 连接信号
    connect(regDialog, &registeruser::registerComplete, this, [=]() {
        this->show();  // 显示登录窗口
        regDialog->deleteLater();  // 删除注册窗口
    });

    this->hide();  // 隐藏登录窗口
    regDialog->exec();  // 显示注册窗口

}






