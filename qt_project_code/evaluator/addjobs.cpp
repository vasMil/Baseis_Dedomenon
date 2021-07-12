#include "addjobs.h"
#include "ui_addjobs.h"

AddJobs::AddJobs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddJobs)
{
    ui->setupUi(this);
}

AddJobs::AddJobs(QString username ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddJobs)
{
    ui->setupUi(this);
    connect(this, SIGNAL( fake_click_myJobs() ), this->parent()->parent()->parent()->parent(),
            SLOT( on_but_myJobs_clicked() ) );
    QVariant ar[6];
    this->username = username;
    ui->lineEdit_username->setText(username);
    ui->lineEdit_position->setText(ar[2].toString());
    ui->lineEdit_edra->setText(ar[3].toString());
    ui->lineEdit_salary->setText(ar[1].toString());
    ui->lineEdit_stDate->setText(ar[0].toString());
    ui->lineEdit_sub_date->setText(ar[5].toString());
    ui->lineEdit_announc_date->setText("AUTO INSERT");

}

AddJobs::~AddJobs()
{
    delete ui;
}

void AddJobs::on_buttonBox_accepted()
{
    QString username;
    username =this->username;
    qDebug()<<username;
    QVariant ar[7];
    QSqlQuery query;
    ar[4]= ui->lineEdit_username->text();
    ar[2]=ui->lineEdit_position->text();
    ar[1]=ui->lineEdit_salary->text();
    ar[3]=ui->lineEdit_edra->text();
    ar[0]=ui->lineEdit_stDate->text();
    ar[5]=ui->lineEdit_sub_date->text();
    ui->lineEdit_username->setText(username);
    query.clear();
    query.prepare("INSERT INTO job(start_date, salary, position, edra, evaluator_username, submission_date) "
                    "VALUES(?,?,?,?,?,?)");

      for(int i = 0; i < 6; i++){
        query.bindValue(i,ar[i]);
      }

     if(!query.exec()){
         QMessageBox::critical(this, "Critical Error", "Something went wrong - COMPANY INSERT FAILED!");
     }
     else{
         QMessageBox::information(this,"Success", "Job Added!");
     }
     fake_click_myJobs();
}

void AddJobs::on_buttonBox_rejected()
{
     QMessageBox::critical(this, "CANCELLED", "Did not add new job!");
}

