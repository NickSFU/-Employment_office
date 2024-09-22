#include "employerwindow.h"
#include "ui_employerwindow.h"

EmployerWindow::EmployerWindow(User *curUser, DatabaseHandler *dbHandler,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployerWindow)
{
    ui->setupUi(this);
    database=dbHandler;
    user=curUser;
    loadVacancies();
}

EmployerWindow::~EmployerWindow()
{
    delete ui;
}

void EmployerWindow::loadVacancies()
{
    QVector<Vacansies> vacancies = database->getVacanciesByEmployerID(user->getUserTableID());

    if (vacancies.isEmpty()) {
        QMessageBox::information(this, "Информация", "Вакансии не найдены.");
        return;
    }

    populateVacancyTable(vacancies);
}

void EmployerWindow::populateVacancyTable(const QVector<Vacansies> &vacancies)
{
    // Очищаем таблицу перед заполнением
    ui->vacancyTableWidget->clearContents();
    ui->vacancyTableWidget->setRowCount(vacancies.size());

    // Устанавливаем заголовки таблицы
    ui->vacancyTableWidget->setColumnCount(7);
    QStringList headers;
    headers<<"ID"<<"Вид деятельности" << "Должность" << "Зарплата" << "Период" << "Требования"<<"Дополнительная информация";
    ui->vacancyTableWidget->setHorizontalHeaderLabels(headers);

    // Заполняем таблицу данными
    for (int i = 0; i < vacancies.size(); i++) {
        ui->vacancyTableWidget->setItem(i, 0, new QTableWidgetItem(vacancies[i].ID));
        ui->vacancyTableWidget->setItem(i, 1, new QTableWidgetItem(vacancies[i].activityType));
        ui->vacancyTableWidget->setItem(i, 2, new QTableWidgetItem(vacancies[i].title));
        ui->vacancyTableWidget->setItem(i, 3, new QTableWidgetItem(vacancies[i].salary));
        ui->vacancyTableWidget->setItem(i, 4, new QTableWidgetItem(vacancies[i].period));
        ui->vacancyTableWidget->setItem(i, 5, new QTableWidgetItem(vacancies[i].requirements));
        ui->vacancyTableWidget->setItem(i, 6, new QTableWidgetItem(vacancies[i].additionalData));
    }
}

void EmployerWindow::on_CreateVacancyButton_clicked()
{
    QString title = ui->TitleEdit->text();
    QString salary = ui->SalaryEdit->text();
    QString period = ui->PeriodEdit->text();
    QString requirements = ui->RequirementsEdit->text();
    QString additionalData = ui->AdditionalDataEdit->toPlainText();

    if (title.isEmpty() || salary.isEmpty() || period.isEmpty() || requirements.isEmpty() || additionalData.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }
    int employerID=user->getUserID();
    if(database->addVacanciesToDatabase(employerID,title,salary,period,requirements,additionalData))
    {
        QMessageBox::information(this, "Успех", "Вакансия успешно добавлена!");
        ui->TitleEdit->clear();
        ui->SalaryEdit->clear();
        ui->PeriodEdit->clear();
        ui->RequirementsEdit->clear();
        ui->AdditionalDataEdit->clear();
    }
    else {
        qDebug() << "Ошибка при добавлении вакансии. Пожалуйста, проверьте данные.";
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить вакансию. Пожалуйста, проверьте данные.");
    }
    loadVacancies();
    return;

}


void EmployerWindow::on_DeleteVacancyButton_clicked()
{
    loadVacancies();
}


void EmployerWindow::on_vacancyTableWidget_clicked(const QModelIndex &index)
{
    row = index.row();
}

