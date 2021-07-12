#include "ManagerResult.h"
#include "ui_ManagerResult.h"

ManagerResult::ManagerResult(QString afm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerResult)
{
    ui->setupUi(this);
    QSqlQuery q;

    /************************************* Determine how many rows will be returned *************************************************/
    q.prepare("CALL evaluationEmplRes(?)");
    q.bindValue(0,afm);
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch the results!");
    }

    int rows = 0;
    while(q.next()){
        rows++;
    }
    ui->tableWidget_res->setRowCount(rows);
    q.clear();
    /********************************* END - Determine how many rows will be returned *************************************************/

    q.prepare("CALL evaluationEmplRes(?)");
    q.bindValue(0,afm);
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch the results!");
    }

    int row_count = 0;
    while(q.next()){
        for(int j = 0; j < 6; j++){
            auto *cell = new QTableWidgetItem;
            if(j == 3 && q.value(j) == NULL){
                cell->setText("Hasn't completed an evaluation");
            }
            else{
                cell->setText(q.value(j).toString());
            }
            ui->tableWidget_res->setItem(row_count,j,cell);
            ui->tableWidget_res->item(row_count,j)->setBackground(QColorConstants::Gray);
            ui->tableWidget_res->item(row_count,j)->setTextAlignment(Qt::AlignCenter);
        }
        row_count++;
    }
    q.clear();
}

ManagerResult::~ManagerResult()
{
    delete ui;
}
