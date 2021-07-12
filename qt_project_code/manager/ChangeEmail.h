#ifndef CHANGEEMAIL_H
#define CHANGEEMAIL_H

#include <QDialog>
#include "DBConnect.h"

namespace Ui {
class ChangeEmail;
}

class ChangeEmail : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeEmail(QWidget *parent = nullptr);
    ~ChangeEmail();

signals:
    void fake_click_myprof();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ChangeEmail *ui;
};

#endif // CHANGEEMAIL_H
