#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include "databasehandler.h"

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationWindow(DatabaseHandler* dbHandler, QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:


    void on_RegistrationButton_clicked();

private:
    Ui::RegistrationWindow *ui;
    DatabaseHandler* database;
};

#endif // REGISTRATIONWINDOW_H
