#include "loginwindow.h"
#include "databasehandler.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DatabaseHandler* dbHandler=new DatabaseHandler();
    // Подключаемся к базе данных в указанной папке, если её нет, то создаём её (Вместо "database" можете назвать иначе, как хотите, чтобы называлась база данных)
    if (!dbHandler->connectToDatabase("", "database.db")) {
        qDebug() << "Не удалось подключиться к базе данных";
        return 1;
    }

    if (!dbHandler->createUsersTable()) {
        qDebug() << "Не удалось создать таблицу Users";
        return 1;
    }

    if (!dbHandler->createEmployersTable()) {
        qDebug() << "Не удалось создать таблицу Employers";
        return 1;
    }

    if (!dbHandler->createApplicantsTable()) {
        qDebug() << "Не удалось создать таблицу Employers";
        return 1;
    }
    if (!dbHandler->createVacanciesTable()) {
        qDebug() << "Не удалось создать таблицу Vacancies";
        return 1;
    }

    if (!dbHandler->createResponsesTable()) {
        qDebug() << "Не удалось создать таблицу Responses";
        return 1;
    }

    if (!dbHandler->createContractsTable()) {
        qDebug() << "Не удалось создать таблицу Responses";
        return 1;
    }

    if (!dbHandler->createAdminData()) {
        qDebug() << "Не удалось добавить админа";
        return 1;
    }

    if (!dbHandler->createApplicantsData()) {
        qDebug() << "Не удалось добавить данные соискателя";
        return 1;
    }
    if (!dbHandler->createEmployersData()) {
        qDebug() << "Не удалось добавить данные работодателя";
        return 1;
    }
    LoginWindow w(dbHandler);
    w.show();
    return a.exec();
}
