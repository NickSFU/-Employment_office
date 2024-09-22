#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QtSql>
#include <QString>
#include <QVector>
#include "user.h"
struct Vacansies // Структура для хранения вакансий
{
    int ID;
    int ID_employer;
    QString activityType;
    QString title;
    QString salary;
    QString period;
    QString requirements;
    QString additionalData;
};
class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);
    bool connectToDatabase(const QString &dbPath, const QString &dbName);
    bool createUsersTable();
    bool createEmployersTable();
    bool createApplicantsTable();
    bool createVacanciesTable();
    bool createResponsesTable();
    bool createContractsTable();
    bool createAdminData();
    bool createApplicantsData();
    bool createEmployersData();
    bool authenticateUser(User *curUser,const QString &login, const QString &password);
    bool isLoginTaken(const QString &login);
    bool addApplicantToDatabase(const QString &login,const QString &password,const QString &surname,const QString &name,const QString &patronymic,const QString &occupation,const QString &qualification,const QString &additionalData);
    bool addEmployerToDatabase(const QString &login, const QString &password, const QString &name, const QString &activityType, const QString &adress, const QString &phone);
    bool addVacanciesToDatabase(const int &userId, const QString &title, const QString &string, const QString &period, const QString &requirements, const QString &additionalData);
    QVector<Vacansies> getVacanciesByEmployerID(int employerID);
private:
    QSqlDatabase db;

};


#endif // DATABASEHANDLER_H
