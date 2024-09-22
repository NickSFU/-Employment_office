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
struct Responses
{
    int ID;
    int ID_Vacancy;
    int ID_Applicant;
};

struct Contracts
{
    int ID;
    int ID_Response;
    QString Commision;
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
    bool addResponsesToDatabase(const int &ID_Vacancy, const int &ID_Applicant);
    bool addContractsToDatabase(const int &ID_Response);
    bool deleteUser(const int &ID);
    bool deleteVacancy(const int &ID);
    bool deleteResponse(const int &ID);
    QVector<Vacansies> getVacanciesByEmployerID(int employerID);
    QVector<Responses> getResponsesByVacancyID(int vacancyID);
    QVector<Responses> getResponsesByApplicantID(int applicantID);
    QVector<Contracts> getContractsByResponseID(int responseID);
private:
    QSqlDatabase db;

};


#endif // DATABASEHANDLER_H
