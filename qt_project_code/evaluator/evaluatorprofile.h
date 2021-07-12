#ifndef EVALUATORPROFILE_H
#define EVALUATORPROFILE_H

#include <QWidget>
#include "DBConnect.h"
namespace Ui {
class EvaluatorProfile;
}

class EvaluatorProfile : public QWidget
{
    Q_OBJECT

public:
    explicit EvaluatorProfile(QWidget *parent = nullptr);
    explicit EvaluatorProfile(QString username ,QWidget *parent = nullptr);
    ~EvaluatorProfile();

private slots:
    void on_show_button_pressed();

    void on_show_button_released();

    void on_but_chpass_clicked();

    void on_but_chmail_clicked();

private:
    Ui::EvaluatorProfile *ui;
    QString username;
};

#endif // EVALUATORPROFILE_H
