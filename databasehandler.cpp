#include "databasehandler.h"

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject{parent}
{

}

bool DatabaseHandler::connectToDatabase(const QString &dbPath, const QString &dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE"); // Устанавливаем драйвер для работы с базой данных SQLite
    db.setDatabaseName(dbPath + dbName); // Соединяем путь и имя файла базы данных
    if (!db.open()) { // Пытаемся открыть соединение с базой данных
        qDebug() << "Не удалось подключиться к базе данных";
        return false;
    }
    return true;
}

bool DatabaseHandler::createUsersTable()
{
    QSqlQuery queryUsers(db);
    if (!queryUsers.exec("CREATE TABLE IF NOT EXISTS Users ("
                         "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "Login TEXT NOT NULL,"
                         "Password TEXT NOT NULL,"
                         "Role TEXT NOT NULL,"
                         "DeletionFlag INTEGER NOT NULL"
                         ")")) {
        qDebug() << "Не удалось создать таблицу Users:" << queryUsers.lastError().text();
            return false;
    }
    return true;
}

bool DatabaseHandler::createEmployersTable()
{
    QSqlQuery queryUsers(db);
    if (!queryUsers.exec("CREATE TABLE IF NOT EXISTS Employers ("
                         "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "ID_user INTEGER NOT NULL,"
                         "Name TEXT NOT NULL,"
                         "ActivityType TEXT NOT NULL,"
                         "Adresss TEXT NOT NULL,"
                         "PhoneNumber TEXT NOT NULL"
                         ")")) {
            qDebug() << "Не удалось создать таблицу Employers:" << queryUsers.lastError().text();
                return false;
    }
    return true;
}

bool DatabaseHandler::createApplicantsTable()
{
    QSqlQuery queryUsers(db);
    if (!queryUsers.exec("CREATE TABLE IF NOT EXISTS Applicants ("
                         "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "ID_user INTEGER NOT NULL,"
                         "Surname TEXT NOT NULL,"
                         "Name TEXT NOT NULL,"
                         "Patronymic TEXT NOT NULL,"
                         "Qualification TEXT NOT NULL,"
                         "Occupation TEXT NOT NULL,"
                         "AdditionalData TEXT NOT NULL"
                         ")")) {
                qDebug() << "Не удалось создать таблицу Applicants:" << queryUsers.lastError().text();
                    return false;
    }

    return true;
}

bool DatabaseHandler::createVacanciesTable()
{
    QSqlQuery queryUsers(db);
    if (!queryUsers.exec("CREATE TABLE IF NOT EXISTS Vacancies ("
                         "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "ID_Employer INTEGER NOT NULL,"
                         "Title TEXT NOT NULL,"
                         "Salary TEXT NOT NULL,"
                         "Period TEXT NOT NULL,"
                         "Requirements TEXT NOT NULL,"
                         "AdditionalData TEXT NOT NULL,"
                         "DeletionFlag INTEGER NOT NULL"
                         ")")) {
                    qDebug() << "Не удалось создать таблицу Vacancies:" << queryUsers.lastError().text();
                        return false;
    }

    return true;
}

bool DatabaseHandler::createResponsesTable()
{
    QSqlQuery queryUsers(db);
    if (!queryUsers.exec("CREATE TABLE IF NOT EXISTS Responses ("
                         "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "ID_Vacancy INTEGER NOT NULL,"
                         "ID_Applicant INTEGER NOT NULL,"
                         "DeletionFlag INTEGER NOT NULL"
                         ")")) {
                        qDebug() << "Не удалось создать таблицу Responses:" << queryUsers.lastError().text();
                            return false;
    }

    return true;
}

bool DatabaseHandler::createContractsTable()
{
    QSqlQuery queryUsers(db);
    if (!queryUsers.exec("CREATE TABLE IF NOT EXISTS Contracts ("
                         "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "ID_Response INTEGER NOT NULL,"
                         "Commision TEXT NOT NULL"
                         ")")) {
                            qDebug() << "Не удалось создать таблицу Contracts:" << queryUsers.lastError().text();
                                return false;
    }

    return true;
}

bool DatabaseHandler::createAdminData()
{
    QSqlQuery queryCheckTable(db);
    queryCheckTable.prepare("SELECT COUNT(*) FROM Users");
    if (!queryCheckTable.exec() || !queryCheckTable.next()) {
                    qDebug() << "Ошибка при проверке наличия данных в таблице Users:" << queryCheckTable.lastError().text();
                        return false;
    }
    int userCount = queryCheckTable.value(0).toInt();
    if(userCount==0)
    {
    QSqlQuery queryUsers(db);
    if (!queryUsers.exec("INSERT INTO Users (Login, Password, Role, DeletionFlag)"
                         "VALUES('admin','admin','Администратор', '0')"))
    {
                    qDebug() << "Не удалось создать таблицу Users:" << queryUsers.lastError().text();
                        return false;
    }
    }
    return true;
}

bool DatabaseHandler::createApplicantsData()
{
    QSqlQuery queryChecker;
    QSqlQuery queryUsers(db);
    QSqlQuery queryID(db);
    queryChecker.prepare("SELECT ID FROM Users WHERE Login = 'qwerty'");
    queryChecker.exec();
    queryChecker.next();
    int Checker = queryChecker.value(0).toInt();
    if(!Checker)
    {
        queryUsers.exec();
        queryUsers.prepare("INSERT INTO Users (Login, Password, Role, DeletionFlag)"
                           "VALUES ('qwerty','qwerty','Соискатель', '0')");
        queryUsers.exec();
        queryID.prepare("SELECT ID FROM Users WHERE Login = 'qwerty'");
        queryID.exec();
        queryID.next();
        int userId=queryID.value(0).toInt();
        queryUsers.prepare("INSERT INTO Applicants (ID_user, Surname, Name, Patronymic, Qualification, Occupation, AdditionalData)"
                           "VALUES (? ,'Тестов','Тестовик','Тестович','Общее образование','Программист','Правша')");
        queryUsers.addBindValue(userId);
        queryUsers.exec();
    }
    return true;
}

bool DatabaseHandler::createEmployersData()
{   QSqlQuery queryChecker;
    QSqlQuery queryUsers;
    QSqlQuery queryID;
    queryChecker.prepare("SELECT ID FROM Users WHERE Login = 'asdfgh'");
    queryChecker.exec();
    queryChecker.next();
    int Checker = queryChecker.value(0).toInt();
    if(!Checker){
        queryUsers.prepare("INSERT INTO Users (Login, Password, Role, DeletionFlag)"
                           "VALUES ('asdfgh', 'asdfgh', 'Работодатель','0')");
        if (!queryUsers.exec()) {
            qDebug() << "Ошибка при добавлении пользователя в таблицу Users:" << queryUsers.lastError().text();
            return false;
        }
        queryID.prepare("SELECT ID FROM Users WHERE Login = 'asdfgh' AND DeletionFlag = 0");
        if (!queryID.exec() || !queryID.next()) {
            qDebug() << "Ошибка поиске ID:" << queryUsers.lastError().text();
                                                           return false;
        }
        int userID=queryID.value(0).toInt();
        queryUsers.prepare("INSERT INTO Employers (ID_User, Name, ActivityType, Adresss, PhoneNumber)"
                           "VALUES (?, 'ИВТ холдинг', 'IT', 'ул.Технологическая 6', '88005553535')");
        queryUsers.addBindValue(userID);
        if (!queryUsers.exec()) {
            qDebug() << "Ошибка при добавлении пользователя в таблицу Employers:" << queryUsers.lastError().text();
            return false;
        }
    }
    return true;
}

bool DatabaseHandler::authenticateUser(User *curUser,const QString &login, const QString &password)
{


    QSqlQuery queryUsers(db);
    QSqlQuery queryUserRole(db);
    QString userRole;
    int userID;
    int userTablesID;
    queryUsers.prepare("SELECT ID FROM Users WHERE Login =? AND Password =? AND DeletionFlag = 0");
    queryUserRole.prepare("SELECT Role FROM Users WHERE Login =? AND Password =? AND DeletionFlag = 0");
    queryUserRole.addBindValue(login);
    queryUserRole.addBindValue(password);
    queryUsers.addBindValue(login);
    queryUsers.addBindValue(password);
    if (!queryUsers.exec()) {
    qDebug() << "Ошибка при аутентификации пользователя:" << queryUsers.lastError().text();
    return false;
    }
    if (!queryUserRole.exec()) {
    qDebug() << "Ошибка при аутентификации пользователя роль:" << queryUsers.lastError().text();
    return false;
    }
    if (queryUsers.next()) {
    userID=queryUsers.value(0).toInt();
    curUser->setUserID(userID); // Сохраняем текущий идентификатор пользователя
    }
    if (queryUserRole.next()) {
    userRole=queryUserRole.value(0).toString();
    curUser->setUserRole(userRole); // Сохраняем текущую роль пользователя
    }
    if(userRole=="Работодатель")
    {
    QSqlQuery queryEmployers;
    queryEmployers.prepare("SELECT ID FROM Employers WHERE ID_user = ?");
    queryEmployers.addBindValue(userID);
    if (!queryEmployers.exec()) {
            qDebug() << "Ошибка при аутентификации пользователя:" << queryUsers.lastError().text();
            return false;
    }
    if (queryEmployers.next())
    {
            userTablesID=queryEmployers.value(0).toInt();
            curUser->setUserTableID(userTablesID);
    }
    }
    else if (userRole=="Соискатель")
    {
                   QSqlQuery queryApplicants;
                   queryApplicants.prepare("SELECT ID FROM Applicants WHERE ID_user = ?");
                   queryApplicants.addBindValue(userID);
                   if (!queryApplicants.exec()) {
                       qDebug() << "Ошибка при аутентификации пользователя:" << queryUsers.lastError().text();
                       return false;
                   }
                   if (queryApplicants.next())
                   {
                       userTablesID=queryApplicants.value(0).toInt();
                       curUser->setUserTableID(userTablesID);
                   }
               }
    return true;
}
bool DatabaseHandler::isLoginTaken(const QString &login)
{
    /*if(!db.isValid())
    {
        qDebug() << "Ошибка при проверке подключения бд:";
    }
    if(!db.isOpen())
    {
        qDebug() << "Ошибка при проверке подключения бд:";
    }*/
    QSqlQuery queryLogin;
    queryLogin.prepare("SELECT ID FROM Users WHERE Login = ? AND DeletionFlag = 0");
    queryLogin.addBindValue(login);
    if (!queryLogin.exec()) {
    qDebug() << "Ошибка при проверке логина:" << queryLogin.lastError().text();
        return true; // Возвращаем true, чтобы предотвратить регистрацию в случае ошибки
    }

    if (queryLogin.next() && queryLogin.value(0).toInt() > 0) {
    return true; // Логин существует
    }

    return false;
}

bool DatabaseHandler::addApplicantToDatabase(const QString &login,const QString &password,const QString &surname,const QString &name,const QString &patronymic,const QString &occupation,const QString &qualification,const QString &additionalData)
{
    QSqlQuery queryUsers;
    QSqlQuery queryID;
    queryUsers.prepare("INSERT INTO Users (Login, Password, Role, DeletionFlag)"
                       "VALUES (?, ?, 'Соискатель','0')");
    queryUsers.addBindValue(login);
    queryUsers.addBindValue(password);
    if (!queryUsers.exec()) {
    qDebug() << "Ошибка при добавлении пользователя в таблицу Users:" << queryUsers.lastError().text();
    return false;
    }
    queryID.prepare("SELECT ID FROM Users WHERE Login = ? AND DeletionFlag = 0");
    queryID.addBindValue(login);
    if (!queryID.exec() || !queryID.next()) {
        qDebug() << "Ошибка поиске ID:" << queryUsers.lastError().text();
        return false;
    }
    int userID=queryID.value(0).toInt();
    queryUsers.prepare("INSERT INTO Applicants (ID_User, Surname, Name, Patronymic, Qualification, Occupation, AdditionalData)"
                       "VALUES (?, ?, ?, ?, ?, ?, ?)");
    queryUsers.addBindValue(userID);
    queryUsers.addBindValue(surname);
    queryUsers.addBindValue(name);
    queryUsers.addBindValue(patronymic);
    queryUsers.addBindValue(qualification);
    queryUsers.addBindValue(occupation);
    queryUsers.addBindValue(additionalData);
    if (!queryUsers.exec()) {
        qDebug() << "Ошибка при добавлении пользователя в таблицу Applicants:" << queryUsers.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseHandler::addEmployerToDatabase(const QString &login, const QString &password, const QString &name, const QString &activityType, const QString &adress, const QString &phone)
{
    QSqlQuery queryUsers;
    QSqlQuery queryID;
    queryUsers.prepare("INSERT INTO Users (Login, Password, Role, DeletionFlag)"
                       "VALUES (?, ?, 'Работодатель','0')");
    queryUsers.addBindValue(login);
    queryUsers.addBindValue(password);
    if (!queryUsers.exec()) {
        qDebug() << "Ошибка при добавлении пользователя в таблицу Users:" << queryUsers.lastError().text();
        return false;
    }
    queryID.prepare("SELECT ID FROM Users WHERE Login = ? AND DeletionFlag = 0");
    queryID.addBindValue(login);
    if (!queryID.exec() || !queryID.next()) {
        qDebug() << "Ошибка при поиске ID:" << queryUsers.lastError().text();
                                           return false;
    }
    int userID=queryID.value(0).toInt();
    queryUsers.prepare("INSERT INTO Employers (ID_User, Name, ActivityType, Adresss, PhoneNumber)"
                       "VALUES (?, ?, ?, ?, ?)");
    queryUsers.addBindValue(userID);
    queryUsers.addBindValue(name);
    queryUsers.addBindValue(activityType);
    queryUsers.addBindValue(adress);
    queryUsers.addBindValue(phone);
    if (!queryUsers.exec()) {
        qDebug() << "Ошибка при добавлении пользователя в таблицу Applicants:" << queryUsers.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseHandler::addVacanciesToDatabase(const int &userID, const QString &title, const QString &salary, const QString &period, const QString &requirements, const QString &additionalData)
{
    QSqlQuery queryUsers;
    QSqlQuery queryID;
    queryID.prepare("SELECT ID From Employers WHERE ID_user = ?");
    queryID.addBindValue(userID);
    if (!queryID.exec()) {
        qDebug() << "Ошибка при добавлении пользователя в таблицу Vacancies:" << queryUsers.lastError().text();
        return false;
    }
    if (!queryID.exec() || !queryID.next()) {
        qDebug() << "Ошибка при поиске ID:" << queryUsers.lastError().text();
        return false;
    }
    int employerID=queryID.value(0).toInt();
    queryUsers.prepare("INSERT INTO Vacancies (ID_Employer, Title, Salary, Period, Requirements, AdditionalData, DeletionFlag)"
                       "VALUES (?, ?, ?, ?, ?, ?, '0')");
    queryUsers.addBindValue(employerID);
    queryUsers.addBindValue(title);
    queryUsers.addBindValue(salary);
    queryUsers.addBindValue(period);
    queryUsers.addBindValue(requirements);
    queryUsers.addBindValue(additionalData);
    if (!queryUsers.exec()) {
        qDebug() << "Ошибка при добавлении пользователя в таблицу Applicants:" << queryUsers.lastError().text();
        return false;
    }

    return true;

}

QVector<Vacansies> DatabaseHandler::getVacanciesByEmployerID(int employerID){
    QVector<Vacansies> vacancies;
    Vacansies vacancy;
    QSqlQuery query(db);
    query.prepare("SELECT ActivityType, Vacancies.ID, Title, Salary, Period, Requirements, AdditionalData FROM Employers JOIN Vacancies ON Employers.ID = ID_Employer WHERE ID_Employer = ? AND DeletionFlag = 0");
    query.addBindValue(employerID);
    if (!query.exec()) {
        qDebug() << "Ошибка при получении вакансий:" << query.lastError().text();
            return vacancies;
    }

    while (query.next()) {

        vacancy.ID_employer = employerID;
        vacancy.activityType = query.value(0).toString();
        vacancy.ID = query.value(1).toInt();
        vacancy.title = query.value(2).toString();
        vacancy.salary = query.value(3).toString();
        vacancy.period = query.value(4).toString();
        vacancy.requirements = query.value(5).toString();
        vacancy.additionalData = query.value(6).toString();
        vacancies.append(vacancy);

    }

        return vacancies;
}
