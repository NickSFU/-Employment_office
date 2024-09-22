#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "databasehandler.h"
#include "registrationwindow.h"
#include "adminwindow.h"
#include "applicantwindow.h"
#include "employerwindow.h"
#include <QMessageBox>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(DatabaseHandler* dbHandler,QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_RegistrationButton_clicked();
    void on_LogINButton_clicked();

private:
    Ui::LoginWindow *ui;
    DatabaseHandler* database;
    RegistrationWindow *regwindow = NULL;
    AdminWindow *adminwindow = NULL;
    ApplicantWindow *appwindow = NULL;
    EmployerWindow *empwindow = NULL;
    User *user=NULL;

};
#endif // LOGINWINDOW_H
