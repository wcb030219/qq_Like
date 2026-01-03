#include "registeruser.h"
#include "ui_registeruser.h"
#include "widget.h"

#include <QCloseEvent>
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



    repeat_user->setPlaceholderText("请输入用户名 (3-20个字符)");
    repeat_paw->setPlaceholderText("请输入密码 (至少6位)");
    repeat_enpaw->setPlaceholderText("请再次输入密码");
    btn_submit->setText("提交");


    repeat_paw->setEchoMode(QLineEdit::Password);
    repeat_enpaw->setEchoMode(QLineEdit::Password);
    int windowWidth = 400;
    int buttonWidth = 60;
    int buttonX = (windowWidth - buttonWidth) / 2;

    btn_submit->setGeometry(buttonX, 230, buttonWidth, 50);


    applyStyle();

    connect(btn_submit, &QPushButton::clicked, this, &registeruser::on_btn_submit_clicked);

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
    QString confirmPassword = repeat_enpaw->text();

    stusql& db = stusql::instance();

    if (!validateInput()) {
        return;
    }



    if (db.checkUserExists(username)) {
        QMessageBox::warning(this, "注册失败", "该用户名已被注册");
        repeat_user->setFocus();
        return;
    }

    // 注册用户
    bool success = db.addUser(username, password, confirmPassword);

    if (success) {
        QMessageBox::information(this, "注册成功",
                                 QString("账号 '%1' 注册成功！").arg(username));

        emit registerComplete(username);

        // 清空输入框
        repeat_user->clear();
        repeat_paw->clear();
        repeat_enpaw->clear();

        this->accept();
    } else {
        QMessageBox::warning(this, "注册失败", "注册失败，请稍后重试");
    }
}




bool registeruser::validateInput()
{
    QString username = repeat_user->text().trimmed();
    QString password = repeat_paw->text();
    QString confirmPassword = repeat_enpaw->text();

    // 检查用户名
    if (username.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "用户名不能为空");
        repeat_user->setFocus();
        return false;
    }

    if (username.length() < 3 || username.length() > 20) {
        QMessageBox::warning(this, "输入错误", "用户名长度需在3-20个字符之间");
        repeat_user->setFocus();
        return false;
    }


    // 检查密码
    if (password.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "密码不能为空");
        repeat_paw->setFocus();
        return false;
    }

    if (password.length() < 6) {
        QMessageBox::warning(this, "输入错误", "密码长度至少为6位");
        repeat_paw->setFocus();
        return false;
    }


    // 检查确认密码
    if (confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请确认密码");
        repeat_enpaw->setFocus();
        return false;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "输入错误", "两次输入的密码不一致");
        repeat_enpaw->clear();
        repeat_enpaw->setFocus();
        return false;
    }

    // 检查用户名是否已存在
    if (stusql::instance().checkUserExists(username)) {
        QMessageBox::warning(this, "注册失败", "该用户名已被注册");
        repeat_user->setFocus();
        return false;
    }

    return true;
}

void registeruser::closeEvent(QCloseEvent *event)
{
    emit backToLogin();
    event->accept();
}


