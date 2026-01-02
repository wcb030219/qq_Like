#include "stusql.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>

stusql::stusql(QObject *parent)
    : QObject{parent}
{

}

stusql &stusql::instance()
{
    static stusql instance;
    return instance;
}


void stusql::init()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\QT\\QtSqlite\\chat_system.db");

    if (!db.open()) {
        qDebug() << "Error: Failed to open database:" << db.lastError().text();
        return;
    }
}

bool stusql::addUser(const QString &username, const QString &password, const QString &confirmPassword)
{
    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        qDebug() << "Error: All fields are required";
        return false;
    }

    if (password != confirmPassword) {
        qDebug() << "Error: Passwords do not match";
        return false;
    }

    // 检查用户是否已存在
    if (checkUserExists(username)) {
        qDebug() << "Error: Username already exists";
        return false;
    }


    // 插入新用户
    QSqlQuery query;
    query.prepare(
        "INSERT INTO users (username, password, enter_password) "
        "VALUES (:username, :password, :enter_password)"
        );
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":enter_password", password); // 确认密码字段也存储加密后的密码

    if (!query.exec()) {
        qDebug() << "Error adding user:" << query.lastError().text();
        return false;
    }

    qDebug() << "User added successfully. User ID:" << query.lastInsertId().toInt();
    return true;
}


bool stusql::checkUserExists(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Error checking user existence:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}

bool stusql::verifyUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Error verifying user:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        QString storedPassword = query.value(0).toString();

        return storedPassword == password;
    }

    return false;
}


