#include "applicantwindow.h"
#include "ui_applicantwindow.h"

ApplicantWindow::ApplicantWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplicantWindow)
{
    ui->setupUi(this);
}

ApplicantWindow::~ApplicantWindow()
{
    delete ui;
}

void ApplicantWindow::on_ActivityTypeBox_textActivated(const QString &arg1)
{

}


void ApplicantWindow::on_RespondButton_clicked()
{

}


void ApplicantWindow::on_tableWidget_clicked(const QModelIndex &index)
{

}


void ApplicantWindow::on_tableWidget_2_clicked(const QModelIndex &index)
{

}


void ApplicantWindow::on_DeleteResponse_clicked()
{

}

