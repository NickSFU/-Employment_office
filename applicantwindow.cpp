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
