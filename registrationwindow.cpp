#include "registrationwindow.h"
#include "ui_registrationwindow.h"

RegistrationWindow::RegistrationWindow(DatabaseHandler* dbHandler, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);
    database = dbHandler;
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}


void RegistrationWindow::on_RegistrationButton_clicked()
{
    QString login = ui -> LoginEdit -> text();
    QString password = ui -> PasswordEdit -> text();
    QString surname = ui -> SurnameEdit -> text();
    QString name = ui -> NameEdit -> text();
    QString patronymic = ui ->PatronymicEdit -> text();
    QString occupation = ui ->OccupationEdit -> text();
    QString qualification = ui ->QualificationEdit -> toPlainText();
    QString additionalData = ui ->AdditionalDataEdit->toPlainText();


    if (login.isEmpty() || name.isEmpty() || patronymic.isEmpty() || occupation.isEmpty() || qualification.isEmpty()|| additionalData.isEmpty() || login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    QRegularExpression nameRegex("^[а-яёА-ЯЁ]+$");
    if (!nameRegex.match(surname).hasMatch() || !nameRegex.match(name).hasMatch() || !nameRegex.match(patronymic).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "ФИО должны содержать только русские буквы.");
        return;
    }

    QRegularExpression loginPasswordRegex("^[A-Za-z0-9_!@#$%^&+*]+$");
    if (!loginPasswordRegex.match(login).hasMatch() || !loginPasswordRegex.match(password).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль не должны содержать русские буквы и пробелы.");
        return;
    }

    if (login.length() < 5 || password.length() < 5) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль должны быть не менее 5 символов.");
        return;
    }
    surname = surname.toLower();
    name = name.toLower();
    patronymic = patronymic.toLower();
    surname[0] = surname[0].toUpper();
    name[0] = name[0].toUpper();
    patronymic[0] = patronymic[0].toUpper();

    if(database->isLoginTaken(login))
    {
        QMessageBox::warning(this, "Ошибка", "Данный логин уже занят.");
        return;
    }
    if(database->addApplicantToDatabase(login, password, surname, name, patronymic, occupation, qualification, additionalData))
    {
        QMessageBox::information(this, "Успех", "Пользователь успешно зарегистрирован!");
        accept();
    }
    else {
        qDebug() << "Ошибка при регистрации пользователя. Пожалуйста, проверьте данные.";
        QMessageBox::critical(this, "Ошибка", "Не удалось зарегистрировать пользователя. Пожалуйста, проверьте данные.");
    }
    return;
}

