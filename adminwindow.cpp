#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(User *curUser, DatabaseHandler *dbHandler,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    database=dbHandler;
    currentUser=curUser;

}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_CreateButton_clicked()
{
    QString login = ui->LoginEdit->text();
    QString password = ui->PasswordEdit->text();
    QString name = ui->NameEdit->text();
    QString activityType = ui->ActivityTypeEdit->text();
    QString adress = ui->AdressEdit->text();
    QString phone = ui->PhoneEdit->text();
    if (login.isEmpty() || password.isEmpty() || name.isEmpty() || activityType.isEmpty() || adress.isEmpty()|| phone.isEmpty() ) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }
    QRegularExpression loginPasswordRegex("^[A-Za-z0-9_!@#$%^&*]+$");
    if (!loginPasswordRegex.match(login).hasMatch() || !loginPasswordRegex.match(password).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль не должны содержать русские буквы и пробелы.");
        return;
    }

    QRegularExpression phoneRegex("^[0123456789+]+$");
    if (!phoneRegex.match(phone).hasMatch() ) {
        QMessageBox::warning(this, "Ошибка", "Телефон должен содержать только цифры или +.");
        return;
    }
    if (login.length() < 5 || password.length() < 5) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль должны быть не менее 5 символов.");
        return;
    }
    if(database->isLoginTaken(login))
    {
        QMessageBox::warning(this, "Ошибка", "Данный логин уже занят.");
        return;
    }
    if(database->addEmployerToDatabase(login, password,name, activityType, adress, phone))
    {
        QMessageBox::information(this, "Успех", "Пользователь успешно зарегистрирован!");
        ui->LoginEdit->clear();
        ui->PasswordEdit->clear();
        ui->NameEdit->clear();
        ui->ActivityTypeEdit->clear();
        ui->AdressEdit->clear();
        ui->PhoneEdit->clear();
    }
    else {
        qDebug() << "Ошибка при регистрации пользователя. Пожалуйста, проверьте данные.";
        QMessageBox::critical(this, "Ошибка", "Не удалось зарегистрировать пользователя. Пожалуйста, проверьте данные.");
    }
    return;
}


