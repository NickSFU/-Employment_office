#include "user.h"

User::User(QObject *parent)
    : QObject{parent}
{

}

void User::setUserID(const int ID)
{
    CurrentUserID = ID;
}

void User::setUserTableID(const int ID)
{
    CurrentUserTableID = ID;
}
void User::setUserRole(const QString role)
{
    CurrentUserRole = role;
}
int User::getUserID()
{
    return CurrentUserID;
}

int User::getUserTableID()
{
    return CurrentUserTableID;
}

QString User::getUserRole()
{
    return CurrentUserRole;
}
