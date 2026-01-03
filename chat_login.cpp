#include "chat_login.h"
#include "ui_chat_login.h"
#include<QToolButton>
#include<QPixmap>
#include "chat_client.h"
chat_login::chat_login(QWidget *parent, const QString &loggedInUser)
    : QDialog(parent)
    , ui(new Ui::chat_login)
    , currentUser(loggedInUser)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/resource/qq.png"));
    this->setWindowTitle("QQ - " + currentUser);
    this->setWindowTitle("QQ");
    //用户名列表
    QStringList list;
    list<<"性感小飞侠"<<"闷骚男"<<"韩国欧巴"<<"神经病一枚"<<"笨笨猪"<<"狗头"<<"蛇精病"<<"赵四"<<"本山兄弟";
    //图片资源列表
    QStringList listIcon;
    listIcon<<"spqy"<<"ymrl"<<"qq"<<"Cherry"<<"dr"<<"jj"<<"lswh"<<"qmnn"<<"spqy";

    for(int i=0;i<9;i++){
        QToolButton *btn=new QToolButton(this);
        btn->setIcon(QPixmap(QString("://%1.png").arg(listIcon[i])));
        btn->setIcon(QPixmap(QString(":/resource/%1.png").arg(listIcon[i])));
        //透明
        btn->setAutoRaise(true);
        //设置网名
        btn->setText(QString("%1").arg(list[i]));
        //设置显示格式
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        ui->vlayout->addWidget(btn);
        buttons.push_back(btn);
        isShow.push_back(false);
    }

    for(int i=0;i<9;i++){
        connect(buttons[i],&QToolButton::clicked,[=](){
            if(true==isShow[i]){
                QMessageBox::warning(this,"警告","改聊天框已被打开");
                return;
            }
            isShow[i]=true;
            chat_client *widget=new chat_client(0,buttons[i]->text());
            widget->setWindowIcon(buttons[i]->icon());
            widget->setWindowTitle(buttons[i]->text());
            widget->show();
            //关闭聊天框时将对于的isShow跟改为false
            connect(widget,&chat_client::closeWidget,[=](){
                isShow[i]=false;
            });
        });
    }
}



chat_login::~chat_login()
{
    delete ui;
}

void chat_login::closeEvent(QCloseEvent *event)
{
    QApplication::quit();
}

