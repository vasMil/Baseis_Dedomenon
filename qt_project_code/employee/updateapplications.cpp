#include "updateapplications.h"
#include "ui_updateapplications.h"

UpdateApplications::UpdateApplications(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateApplications){
    ui->setupUi(this);
}
UpdateApplications::UpdateApplications(QString username,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateApplications)
{
    ui->setupUi(this);
    this->username=username;
    connect(this, SIGNAL( fake_click_applications() ), this->parent()->parent()->parent()->parent()
            , SLOT( on_but_applications_clicked()) );

    QSqlQuery q;

        q.prepare("CALL updateApplications(?)");
        q.bindValue(0,username);
        if(!q.exec()){
            QMessageBox::critical(this, "Critical Error", "Could not fetch jobs");
        }
        while(q.next()){
            ui->comboBox_applications->addItem(q.value(0).toString() + ": " + q.value(1).toString());
            prev=cur;
        }
        q.clear();
}

UpdateApplications::~UpdateApplications()
{
    delete ui;
}





void UpdateApplications::on_buttonBox_accepted()
{
    QString jobID = ui->comboBox_applications->currentText().split(": ")[0];
    if(jobID == ""){
        QMessageBox::warning(this, "Warning!", "No job was selected, so none was added!");
        return;
    }
    QSqlQuery q;
    q.prepare("CALL finalizeJobUpdate(?,?)");
    q.bindValue(0,this->username);
    q.bindValue(1, jobID);
    if(!q.exec()){
        QMessageBox::critical(this, "Application did not register!", q.lastError().text());
    }
    fake_click_applications();
}

void UpdateApplications::on_buttonBox_rejected()
{
    QMessageBox::information(this,"Canceled", "Did not update!");
}

void UpdateApplications::on_comboBox_applications_currentTextChanged(const QString &arg1)
{
    QString job_id = arg1.split(": ")[0];
    if(job_id == ""){
        ui->lineEdit_salary->setText("");
        ui->lineEdit_edra->setText("");
        ui->lineEdit_subDate->setText("");
        ui->req_table->setRowCount(0);
        return;
    }
    QSqlQuery q;
    q.prepare("CALL getJobInfo(?)");
    q.bindValue(0, job_id);
    if(!q.exec()){
        QMessageBox::critical(this, "getJobInfo Error", "Failed to fetch information about the selected job");
    }
    q.next();
    ui->lineEdit_salary->setText(q.value(0).toString());
    ui->lineEdit_edra->setText(q.value(1).toString());
    ui->lineEdit_subDate->setText(q.value(2).toString());
    q.clear();

    /************************************* Determine how many rows will be returned *************************************************/
    q.prepare("CALL getJobrequirements(?)");
    q.bindValue(0,job_id);
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch job requirements!");
    }

    int rows = 0;
    while(q.next()){
        rows++;
    }
    ui->req_table->setRowCount(rows);
    q.clear();
    /********************************* END - Determine how many rows will be returned *************************************************/

    q.prepare("CALL getJobrequirements(?)");
    q.bindValue(0,job_id);
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch the results!");
    }

    int row_count = 0;
    while(q.next()){
        for(int j = 0; j < 3; j++){
            auto *cell = new QTableWidgetItem;
            if(q.value(j).toString() == "" && j == 1){
                cell->setText("Self-existent");
            }
            else{
                cell->setText(q.value(j).toString());
            }
            ui->req_table->setItem(row_count,j,cell);
            ui->req_table->item(row_count,j)->setBackground(QColorConstants::Gray);
            ui->req_table->item(row_count,j)->setTextAlignment(Qt::AlignCenter);
        }
        row_count++;
    }
    q.clear();
}
