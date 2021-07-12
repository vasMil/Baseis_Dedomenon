#ifndef CHANGEEMPLPASS_H
#define CHANGEEMPLPASS_H

#include <QDialog>
#include "DBConnect.h"

namespace Ui {
class ChangeEmplPass;
}

class ChangeEmplPass : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeEmplPass(QWidget *parent = nullptr);
    ~ChangeEmplPass();

signals:
    void fake_click_profile();

private slots:
    void on_show_button_pressed();

    void on_show_button_released();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ChangeEmplPass *ui;
};

#endif // CHANGEEMPLPASS_H
