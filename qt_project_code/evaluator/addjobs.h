#ifndef ADDJOBS_H
#define ADDJOBS_H

#include <QDialog>
#include "DBConnect.h"
namespace Ui {
class AddJobs;
}

class AddJobs : public QDialog
{
    Q_OBJECT

public:
     explicit AddJobs(QWidget *parent = nullptr);
     explicit AddJobs( QString username, QWidget *parent = nullptr);
    ~AddJobs();

signals:
    void fake_click_myJobs();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddJobs *ui;
    QString username;
    QVariant ar;
};

#endif // ADDJOBS_H
