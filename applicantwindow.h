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

private slots:
    //void on_ActivityTypeBox_textActivated(const QString &arg1);

    //void loadVacancies();
    //void loadResponses();
   // void loadContracts();
    //void on_RespondButton_clicked();
    //void on_tableWidget_clicked(const QModelIndex &index);
   // void on_tableWidget_2_clicked(const QModelIndex &index);
    //void on_DeleteResponse_clicked();

private:
    Ui::ApplicantWindow *ui;
};

#endif // APPLICANTWINDOW_H
