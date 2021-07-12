#ifndef UPDATEAPPLICATIONS_H
#define UPDATEAPPLICATIONS_H

#include <QDialog>
#include "DBConnect.h"
namespace Ui {
class UpdateApplications;
}

class UpdateApplications : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateApplications(QWidget *parent = nullptr);
    explicit UpdateApplications(QString username, QWidget *parent = nullptr);
    explicit UpdateApplications(QVariant ar[],QWidget *parent = nullptr);

    ~UpdateApplications();

signals:
    void fake_click_applications();

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_comboBox_applications_currentTextChanged(const QString &arg1);

private:
    Ui::UpdateApplications *ui;
    QString username, prev, cur;
};

#endif // UPDATEAPPLICATIONS_H
