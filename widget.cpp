#include "widget.h"
#include "ui_widget.h"
#include "chat_login.h"

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


    connect(btn_login, &QPushButton::clicked, this, &Widget::onLoginClicked);

    connect(ui->btn_register, &QPushButton::clicked, this, &Widget::on_btn_register_clicked);


    stusql::instance().init();
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
    close();
}


void Widget::onLoginClicked()
{

    QString username = le_username->text().trimmed();
    QString password = le_password->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "登录失败", "用户名或密码不能为空");
        return;
    }

    stusql& m_db = stusql::instance();
    if (m_db.verifyUser(username, password)) {
        QMessageBox::information(this, "登录成功", "登录成功！");
        // 跳转到主界面
        chat_login *loginWindow = new chat_login(this);
        loginWindow->setAttribute(Qt::WA_DeleteOnClose);

        // 用户列表窗口关闭时，直接关闭整个程序
        connect(loginWindow, &chat_login::windowClosed, this, &Widget::close);
        this->hide();
        loginWindow->show();


    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误");
    }
}


void Widget::on_btn_register_clicked()
{
    registeruser *reg = findChild<registeruser*>();
    if (!reg) {
        reg = new registeruser(this);
        reg->setAttribute(Qt::WA_DeleteOnClose);  // 关闭时自动删除

        connect(reg, &registeruser::registerComplete, this, [=](const QString &username) {
            // 自动填充登录用户名
            le_username->setText(username);
            le_password->clear();
            le_password->setFocus();
            reg->close();  // 关闭注册窗口
            this->show();  // 显示主窗口
        });

        connect(reg, &registeruser::backToLogin, this, [=]() {
            reg->close();  // 关闭注册窗口
            this->show();  // 显示主窗口
        });
    }

    this->hide();
    reg->show();
    reg->raise();  // 置顶显示
    reg->activateWindow();  // 激活窗口
}






