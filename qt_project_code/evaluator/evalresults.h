#ifndef EVALRESULTS_H
#define EVALRESULTS_H

#include <QWidget>
#include "DBConnect.h"
namespace Ui {
class EvalResults;
}

class EvalResults : public QWidget
{
    Q_OBJECT

public:
    explicit EvalResults(QString username,QWidget *parent = nullptr);
    ~EvalResults();

private:
    Ui::EvalResults *ui;
    QString username;
};

#endif // EVALRESULTS_H
