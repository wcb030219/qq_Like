#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#include <QCloseEvent>
#include <QDialog>
#include <QUdpSocket>
#include <QWidget>

namespace Ui {
class chat_client;
}

class chat_client : public QWidget
{
    Q_OBJECT

public:
    enum msgType{
        Msg,//普通信息
        UserEnter,//用户进入
        UserLeft//用户离开
    };
    explicit chat_client(QWidget *parent,QString name);



    void closeEvent(QCloseEvent *event);
    void sendMsg(msgType type);//广播信息
    QString getName();//获取名字
    QString getMsg();//获取聊天信息
    void userEnter(QString username);//处理用户进入
    void userLeft(QString username,QString time);//处理用户离开
    void receiveMessage();//接收udp消息(槽函数)


    ~chat_client();


signals:
    //发送关闭信号
    void closeWidget();


private:
    Ui::chat_client *ui;
    QString myname;
    quint16 port;//湍口
    QUdpSocket *udpSocket;//udp套接字


};

#endif // CHAT_CLIENT_H
