#include "EvaluatorAverage.h"
#include "ui_EvaluatorAverage.h"

EvaluatorAverage::EvaluatorAverage(QString afm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EvaluatorAverage)
{
    ui->setupUi(this);
    QSqlQuery q;

    /************************************* Determine how many rows will be returned *************************************************/
    q.prepare("CALL evaluatorAverage(?)");
    q.bindValue(0,afm);
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch evaluators' average grades!");
    }

    int rows = 0;
    while(q.next()){
        rows++;
    }
    ui->tableWidget_avg->setRowCount(rows);
    q.clear();
    /********************************* END - Determine how many rows will be returned *************************************************/

    q.prepare("CALL evaluatorAverage(?)");
    q.bindValue(0,afm);
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch evaluators' average grades!");
    }

    int row_count = 0;
    while(q.next()){
        for(int j = 0; j < 4; j++){
            auto *cell = new QTableWidgetItem;
            if(j == 3 && q.value(j).isNull()){
                cell->setText("Hasn't completed an evaluation");
            }
            else{
                cell->setText(q.value(j).toString());
            }
            ui->tableWidget_avg->setItem(row_count,j,cell);
            ui->tableWidget_avg->item(row_count,j)->setBackground(QColorConstants::Gray);
            ui->tableWidget_avg->item(row_count,j)->setTextAlignment(Qt::AlignCenter);
        }
        row_count++;
    }
    q.clear();
}

EvaluatorAverage::~EvaluatorAverage()
{
    delete ui;
}
