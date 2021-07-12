#ifndef EVALUATORAVERAGE_H
#define EVALUATORAVERAGE_H

#include <QWidget>
#include "DBConnect.h"

namespace Ui {
class EvaluatorAverage;
}

class EvaluatorAverage : public QWidget
{
    Q_OBJECT

public:
    explicit EvaluatorAverage(QWidget *parent = nullptr);
    explicit EvaluatorAverage(QString afm, QWidget *parent = nullptr);
    ~EvaluatorAverage();

private:
    Ui::EvaluatorAverage *ui;
};

#endif // EVALUATORAVERAGE_H
