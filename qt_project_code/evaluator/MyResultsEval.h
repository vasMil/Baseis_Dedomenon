#ifndef MYRESULTSEVAL_H
#define MYRESULTSEVAL_H

#include <QWidget>
#include "DBConnect.h"

namespace Ui {
class MyResultsEval;
}

class MyResultsEval : public QWidget
{
    Q_OBJECT

public:
    explicit MyResultsEval(QString username, QWidget *parent = nullptr);
    ~MyResultsEval();

signals:
    void fake_click_MyResultsEval();

private slots:
    void on_pushButton_5_clicked();

    void on_comboBox_myResults_currentTextChanged(const QString &arg1);

private:
    Ui::MyResultsEval *ui;
    QString username , job_id, empl;
};

#endif // MYRESULTSEVAL_H
