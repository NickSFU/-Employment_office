#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "user.h"
#include "databasehandler.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminWindow(User *curUser, DatabaseHandler *dbHandler, QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_CreateButton_clicked();

private:
    Ui::AdminWindow *ui;
    DatabaseHandler *database;
    User *currentUser;
};

#endif // ADMINWINDOW_H
