#include "deleteapplications.h"
#include "ui_deleteapplications.h"

DeleteApplications::DeleteApplications(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteApplications)
{
    ui->setupUi(this);
}
DeleteApplications::DeleteApplications(QString username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteApplications)
{
    ui->setupUi(this);
    this->username=username;
    connect(this, SIGNAL( fake_click_applications() ), this->parent()->parent()->parent()->parent()
            , SLOT( on_but_applications_clicked()) );
    QSqlQuery q;

       /************************************* Determine how many rows will be returned *************************************************/
       q.prepare("CALL applicationsToDelete(?)");
       q.bindValue(0,username);
       if(!q.exec()){
           QMessageBox::critical(this, "Critical Error", "Could not fetch the results!");
       }


    int rows = 0;
        while(q.next()){
            rows++;
        }
        ui->tableWidget->setRowCount(rows);
        q.clear();
        /********************************* END - Determine how many rows will be returned *************************************************/

        q.prepare("CALL applicationsToDelete(?)");
        q.bindValue(0,username);
        if(!q.exec()){
            QMessageBox::critical(this, "Critical Error", "Could not fetch the results!");
        }

        int row_count = 0;
        while(q.next()){
            for(int j = 0; j < 5; j++){
                auto *cell = new QTableWidgetItem;
                if(j == 3 && q.value(j).toString() == "0"){
                    cell->setText("NULL");
                }
                else if(j == 4 &&  q.value(j).toString() == ""){
                    cell->setText("No comments!");
                }
                else{
                cell->setText(q.value(j).toString());
                }
                cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
                ui->tableWidget->setItem(row_count,j,cell);
                ui->tableWidget->item(row_count,j)->setBackground(QColorConstants::Gray);
                ui->tableWidget->item(row_count,j)->setTextAlignment(Qt::AlignCenter);

            }
            row_count++;
        }
        q.clear();
}

DeleteApplications::~DeleteApplications()
{
    delete ui;
}

void DeleteApplications::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString job_id = ui->tableWidget->item(row,0)->text();
    QSqlQuery q;
    q.prepare("CALL deleteApplication(?,?)");
    q.bindValue(0,this->username);
    q.bindValue(1,job_id);
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", q.lastError().text());
        return;
    }
    ui->tableWidget->removeRow(row);
    QMessageBox::information(this, "Success", "Application was successfully removed!");

}

void DeleteApplications::on_buttonBox_accepted()
{
    fake_click_applications();
}
