#ifndef CHANGEEVALPASS_H
#define CHANGEEVALPASS_H

#include <QDialog>
#include "DBConnect.h"
namespace Ui {
class ChangeEvalPass;
}

class ChangeEvalPass : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeEvalPass(QWidget *parent = nullptr);
    ~ChangeEvalPass();

signals:
    void fake_click_profile();

private slots:
    void on_show_button_pressed();

    void on_show_button_released();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ChangeEvalPass *ui;
};

#endif // CHANGEEVALPASS_H
