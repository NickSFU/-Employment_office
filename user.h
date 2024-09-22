#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    void setUserID(const int ID);
    void setUserTableID(const int ID);
    void setUserRole(const QString role);
    int getUserID();
    int getUserTableID();
    QString getUserRole();

private:
    int CurrentUserID;
    int CurrentUserTableID;
    QString CurrentUserRole;



};

#endif // USER_H
