#include "evalresults.h"
#include "ui_evalresults.h"

EvalResults::EvalResults(QString username,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EvalResults)
{
    ui->setupUi(this);
    this->username=username;
        QSqlQuery q;

           /************************************* Determine how many rows will be returned *************************************************/
           q.prepare("CALL showAllCompanyResults(?)");
           q.bindValue(0,username);
           if(!q.exec()){
               QMessageBox::critical(this, "Critical Error", "Could not fetch the results!");
           }


        int rows = 0;
            while(q.next()){
                rows++;
            }
            ui->tableWidgetResults ->setRowCount(rows);
            q.clear();
            /********************************* END - Determine how many rows will be returned *************************************************/

            q.prepare("CALL showAllCompanyResults(?)");
            q.bindValue(0,username);
            if(!q.exec()){
                QMessageBox::critical(this, "Critical Error", "Could not fetch the results!");
            }
            QString cellText;
            int row_count = 0;
            while(q.next()){
                for(int j = 0; j < 6; j++){
                    auto *cell = new QTableWidgetItem;
                    if(q.value(j).toString() == "-1"){
                        cellText = "NULL";
                    }
                    else if(q.value(j).toString() == ""){
                        cellText = "No Comments Yet";
                    }
                    else{
                        cellText = q.value(j).toString();
                    }
                    cell->setText(cellText);
                    cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
                    ui->tableWidgetResults->setItem(row_count,j,cell);
                    ui->tableWidgetResults->item(row_count,j)->setBackground(QColorConstants::Gray);
                    ui->tableWidgetResults->item(row_count,j)->setTextAlignment(Qt::AlignCenter);

                }




                row_count++;
            }
            q.clear();
}

EvalResults::~EvalResults()
{
    delete ui;
}
