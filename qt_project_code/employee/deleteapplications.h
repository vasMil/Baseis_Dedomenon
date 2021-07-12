#ifndef DELETEAPPLICATIONS_H
#define DELETEAPPLICATIONS_H

#include <QDialog>
#include "DBConnect.h"
namespace Ui {
class DeleteApplications;
}

class DeleteApplications : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteApplications(QWidget *parent = nullptr);
    explicit DeleteApplications(QString username, QWidget *parent = nullptr);
    ~DeleteApplications();

signals:
    void fake_click_applications();

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_buttonBox_accepted();

private:
    Ui::DeleteApplications *ui;
    QString username,job_id;
};

#endif // DELETEAPPLICATIONS_H
