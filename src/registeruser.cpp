#include "registeruser.h"
#include "ui_registeruser.h"
#include "widget.h"

#include <QMessageBox>

registeruser::registeruser(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registeruser)
{
    ui->setupUi(this);

    this->setFixedSize(400,350);
    setWindowTitle("注册");

    repeat_user = new QLineEdit(this);
    repeat_paw = new QLineEdit(this);
    repeat_enpaw = new QLineEdit(this);
    btn_submit = new QPushButton(this);

    repeat_user->setGeometry(40,50,320,50);
    repeat_paw->setGeometry(40,110,320,50);
    repeat_enpaw->setGeometry(40,170,320,50);


    repeat_user->setPlaceholderText("输入账号");
    repeat_paw->setPlaceholderText("输入密码");
    repeat_enpaw->setPlaceholderText("重复密码");
    btn_submit->setText("提交");

    repeat_paw->setEchoMode(QLineEdit::Password);
    repeat_enpaw->setEchoMode(QLineEdit::Password);
    int windowWidth = 400;
    int buttonWidth = 60;
    int buttonX = (windowWidth - buttonWidth) / 2;

    btn_submit->setGeometry(buttonX, 230, buttonWidth, 50);
    applyStyle();

    connect(btn_submit, &QPushButton::clicked, this, &registeruser::on_btn_submit_clicked);

    m_ss.init();
}

registeruser::~registeruser()
{
    delete ui;
}

void registeruser::applyStyle()
{
    // 圆角带内阴影
    QList<QLineEdit*> edits = {repeat_user, repeat_paw, repeat_enpaw};
    QString com  = R"(
    QLineEdit {
        border: none;
        border-radius: 12px;
        padding: 12px 15px;
        font-size: 14px;
        background-color: white;
        selection-background-color: #4d90fe;
        color: #333;
        box-shadow: inset 0 2px 4px rgba(0,0,0,0.08);
    }
    QLineEdit:focus {
        outline: none;
        box-shadow:
            inset 0 2px 4px rgba(0,0,0,0.08),
            0 0 0 3px rgba(66, 153, 225, 0.3);
    }
    QLineEdit::placeholder {
        color: #999;
    }
)";
    for (QLineEdit *lineEdit : edits) {
        lineEdit->setStyleSheet(com);
    }


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
    btn_submit->setStyleSheet(btnStyle);
}

void registeruser::on_btn_submit_clicked()
{
    QString username = repeat_user->text().trimmed();
    QString password = repeat_paw->text();

    // 禁用按钮防止重复提交
    btn_submit->setEnabled(false);

    // 尝试注册用户
    bool success = m_ss.addUser(username, password,password);

    if (success) {
        // 注册成功
        QMessageBox::information(this, "注册成功",
                                 QString("账号 '%1' 注册成功！").arg(username));

        // 发送信号，传递用户名
        emit registerComplete(username);

        // 清空输入框
        repeat_user->clear();
        repeat_paw->clear();
        repeat_enpaw->clear();

        this->accept();
    } else {
        // 注册失败

        // 重新启用按钮
        btn_submit->setEnabled(true);
    }
}

bool registeruser::validateInput()
{
    QString username = repeat_user->text().trimmed();
    QString password = repeat_paw->text();
    QString confirmPassword = repeat_enpaw->text();

    // 检查用户名
    if (username.isEmpty()) {
        return false;
    }

    if (username.length() < 3 || username.length() > 20) {
        return false;
    }

    // 检查密码
    if (password.isEmpty()) {
        return false;
    }

    if (password.length() < 6) {
        return false;
    }

    // 检查确认密码
    if (confirmPassword.isEmpty()) {
        return false;
    }

    if (password != confirmPassword) {
        return false;
    }
    return true;
}



