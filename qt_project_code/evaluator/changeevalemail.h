#ifndef CHANGEEVALEMAIL_H
#define CHANGEEVALEMAIL_H

#include <QDialog>
#include "DBConnect.h"

namespace Ui {
class ChangeEvalEmail;
}

class ChangeEvalEmail : public QDialog
{
    Q_OBJECT


public:
    explicit ChangeEvalEmail(QWidget *parent = nullptr);
    ~ChangeEvalEmail();
signals:
    void fake_click_profile();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ChangeEvalEmail *ui;
};

#endif // CHANGEEVALEMAIL_H
