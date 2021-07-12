#include "employeeapplications.h"
#include "ui_employeeapplications.h"

EmployeeApplications::EmployeeApplications(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeeApplications)
{
    ui->setupUi(this);
}

EmployeeApplications::EmployeeApplications(QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeeApplications)
{
    ui->setupUi(this);
    this->username=username;
    QSqlQuery q;

       /************************************* Determine how many rows will be returned *************************************************/
       q.prepare("CALL get_applications(?)");
       q.bindValue(0,username);
       if(!q.exec()){
           QMessageBox::critical(this, "Critical Error", "Could not fetch the results!");
       }


    int rows = 0;
        while(q.next()){
            rows++;
        }
        ui->tableWidgetAppl->setRowCount(rows);
        q.clear();
        /********************************* END - Determine how many rows will be returned *************************************************/

        q.prepare("CALL get_applications(?)");
        q.bindValue(0,username);
        if(!q.exec()){
            QMessageBox::critical(this, "Critical Error", "Could not fetch the results!");
        }

        int row_count = 0;
        while(q.next()){
            for(int j = 0; j < 4; j++){
                auto *cell = new QTableWidgetItem;
                if(j == 2 && q.value(j).toString() == "-1"){
                    cell->setText("NULL");
                }
                else if(j == 3 &&  q.value(j).toString() == ""){
                    cell->setText("No Comments yet");
                }
                else{
                cell->setText(q.value(j).toString());
                }
                cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
                ui->tableWidgetAppl->setItem(row_count,j,cell);
                ui->tableWidgetAppl->item(row_count,j)->setBackground(QColorConstants::Gray);
                ui->tableWidgetAppl->item(row_count,j)->setTextAlignment(Qt::AlignCenter);

            }
            row_count++;
        }
        q.clear();

}

EmployeeApplications::~EmployeeApplications()
{
    delete ui;
}



void EmployeeApplications::on_but_del_appl_clicked()
{
    auto *d = new DeleteApplications(this->username,this);
       d->show();
}



void EmployeeApplications::on_but_update_appl_clicked()
{
    auto *d = new UpdateApplications(this->username,this);
       d->show();
}
