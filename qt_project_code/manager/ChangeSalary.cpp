#include "ChangeSalary.h"
#include "ui_ChangeSalary.h"

ChangeSalary::ChangeSalary(QString afm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeSalary)
{
    ui->setupUi(this);
    this->afm = afm;
    QSqlQuery q;

    /************************************* Determine how many rows will be returned *************************************************/
    q.prepare("CALL changeSalary(?)");
    q.bindValue(0,afm);
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch employee's credentials");
    }

    int rows = 0;
    while(q.next()){
        rows++;
    }
    ui->tableWidget_jobs->setRowCount(rows);
    q.clear();
    /********************************* END - Determine how many rows will be returned *************************************************/

    q.prepare("CALL changeSalary(?)");
    q.bindValue(0,afm);
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch company's job data");
    }

    int row_count = 0;
    while(q.next()){
        for(int j = 0; j < 3; j++){
            auto *cell = new QTableWidgetItem;
            if(j==0 || j==1){
                cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
            }
            cell->setText(q.value(j).toString());
            ui->tableWidget_jobs->setItem(row_count,j,cell);
            ui->tableWidget_jobs->item(row_count,j)->setBackground(QColorConstants::Gray);
        }
        row_count++;
    }
    q.clear();

    /********************************* Setup company's logo on ui *************************************************************/
    QString logo = ":/images/logo_" + afm + ".png";
    QPixmap l(logo);
    ui->comp_logo->setPixmap(l);
    //get labels dimentions
    int w = ui->comp_logo->width();
    int h = ui->comp_logo->height();
    //set scaled pixmap and maintain aspect ratio
    ui->comp_logo->setPixmap(l.scaled(w,h,Qt::KeepAspectRatio));
}

ChangeSalary::~ChangeSalary()
{
    QSqlQuery q;
    int rows = ui->tableWidget_jobs->rowCount();
    for(int i = 0; i < rows; i++){
        auto *jobid = new QTableWidgetItem;
        jobid = ui->tableWidget_jobs->takeItem(i,0); //if job_id was not available on the table ->
        auto *salary = new QTableWidgetItem;          //must have a list with the job_id for each row as a private attribute
        salary = ui->tableWidget_jobs->takeItem(i,2); //and also watch out for any changes on table's sorting on run time

        q.prepare("UPDATE job SET salary = ? WHERE job_id = ?");
        q.bindValue(0,salary->text());
        q.bindValue(1,jobid->text());
        if(!q.exec()){
            QMessageBox::critical(this,"Critical Error", "Failed to update salary");
        }
        q.clear();
        ui->tableWidget_jobs->setItem(i,0,jobid);
        ui->tableWidget_jobs->setItem(i,2,salary);
    }
    delete ui;
}
