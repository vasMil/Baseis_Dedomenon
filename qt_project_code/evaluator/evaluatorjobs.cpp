#include "evaluatorjobs.h"
#include "ui_evaluatorjobs.h"

EvaluatorJobs::EvaluatorJobs(QString username,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EvaluatorJobs)
{
    ui->setupUi(this);
    this->username=username;
        QSqlQuery q;

           /************************************* Determine how many rows will be returned *************************************************/
           q.prepare("CALL showCompanysJobs(?)");
           q.bindValue(0,username);
           if(!q.exec()){
               QMessageBox::critical(this, "Critical Error", "Could not fetch the results!");
           }


        int rows = 0;
            while(q.next()){
                rows++;
            }
            ui->tableWidgetJob ->setRowCount(rows);
            q.clear();
            /********************************* END - Determine how many rows will be returned *************************************************/

            q.prepare("CALL showCompanysJobs(?)");
            q.bindValue(0,username);
            if(!q.exec()){
                QMessageBox::critical(this, "Critical Error", "Could not fetch the results!");
            }

            int row_count = 0;
            while(q.next()){
                for(int j = 0; j < 7; j++){
                    auto *cell = new QTableWidgetItem;
                    cell->setText(q.value(j).toString());
                    cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
                    ui->tableWidgetJob->setItem(row_count,j,cell);
                    ui->tableWidgetJob->item(row_count,j)->setBackground(QColorConstants::Gray);
                    ui->tableWidgetJob->item(row_count,j)->setTextAlignment(Qt::AlignCenter);

                }




                row_count++;
            }
            q.clear();
}

EvaluatorJobs::~EvaluatorJobs()
{
    delete ui;
}
