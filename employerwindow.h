#ifndef EMPLOYERWINDOW_H
#define EMPLOYERWINDOW_H

#include <QDialog>
#include <QMessageBox>>
#include "databasehandler.h"
#include "user.h"
namespace Ui {
class EmployerWindow;
}

class EmployerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EmployerWindow(User *curUser, DatabaseHandler *dbHandler,QWidget *parent = nullptr);
    ~EmployerWindow();
    void populateVacancyTable(const QVector<Vacansies> &vacancies);

private slots:
    void on_CreateVacancyButton_clicked();
    void loadVacancies();
    void loadResponses();
    void loadContracts();
    void on_DeleteVacancyButton_clicked();

    void on_vacancyTableWidget_clicked(const QModelIndex &index);

    void on_ConcludeContractButton_clicked();

    void on_RefuseApplicantButton_clicked();

    void on_tableWidget_2_clicked(const QModelIndex &index);

private:
    Ui::EmployerWindow *ui;
    DatabaseHandler *database;
    User *user;
    int row;
};

#endif // EMPLOYERWINDOW_H
