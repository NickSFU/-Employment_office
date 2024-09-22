#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(DatabaseHandler* dbHandler,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    database=dbHandler;
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on_RegistrationButton_clicked()
{
    regwindow = new RegistrationWindow(database,this);
    regwindow->exec();
}


void LoginWindow::on_LogINButton_clicked()
{
    QString login = ui->LoginEdit->text();
    QString password = ui->PasswordEdit->text();
    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите логин и пароль");
        return;
    }

    QRegularExpression regex("[А-Яа-яЁё'\"\(): ; / ]");
    if (regex.match(login).hasMatch() || regex.match(password).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль не должны содержать русские буквы и пробелы, и спец символы: \" / ( ) ; : ' ");
        return;
    }
    user=new User();
    database->authenticateUser(user,login,password);

    QString role = user->getUserRole();
    if(role=="Администратор")
        {

            if (!adminwindow) {
                adminwindow = new AdminWindow(user,database,this);
                adminwindow->setAttribute(Qt::WA_DeleteOnClose);
            }
            this->hide();
            adminwindow->show();
        }
    else if (role == "Соискатель")
        {
            if(!appwindow)
            {
                appwindow = new ApplicantWindow();
                appwindow ->setAttribute(Qt::WA_DeleteOnClose);
            }
            this->hide();
            appwindow->show();
        }
    else if (role == "Работодатель")
        {
            if(!empwindow)
            {
                empwindow = new EmployerWindow(user,database,this);
                empwindow ->setAttribute(Qt::WA_DeleteOnClose);
            }
            this->hide();
            empwindow->show();
        }
        else
        {
            QMessageBox::warning(this,"Ошибка","Пользователя с таким логином и паролем не существует.");
        }



}

