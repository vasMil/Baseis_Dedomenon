#ifndef EVALUATORJOBS_H
#define EVALUATORJOBS_H

#include <QWidget>
#include "DBConnect.h"
namespace Ui {
class EvaluatorJobs;
}

class EvaluatorJobs : public QWidget
{
    Q_OBJECT

public:
    explicit EvaluatorJobs(QWidget *parent = nullptr);
    explicit EvaluatorJobs(QString username,QWidget *parent = nullptr);
    ~EvaluatorJobs();

private:
    Ui::EvaluatorJobs *ui;
    QString username;
};

#endif // EVALUATORJOBS_H
