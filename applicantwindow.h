#ifndef APPLICANTWINDOW_H
#define APPLICANTWINDOW_H

#include <QDialog>

namespace Ui {
class ApplicantWindow;
}

class ApplicantWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ApplicantWindow(QWidget *parent = nullptr);
    ~ApplicantWindow();

private:
    Ui::ApplicantWindow *ui;
};

#endif // APPLICANTWINDOW_H
