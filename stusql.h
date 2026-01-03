#ifndef STUSQL_H
#define STUSQL_H
#include <QSqlDatabase>
#include <QObject>
#include <QMessageBox>

class stusql : public QObject
{
    Q_OBJECT
public:
    explicit stusql(QObject *parent = nullptr);

    static stusql& instance();

    void init();

    bool addUser(const QString& username, const QString& password, const QString& confirmPassword);
    bool checkUserExists(const QString& username);
    bool verifyUser(const QString& username, const QString& password);
    bool updateUserPassword(const QString& username, const QString& newPassword);
    bool deleteUser(const QString& username);

signals:
private:
    QSqlDatabase m_db;
};

#endif // STUSQL_H
