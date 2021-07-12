#include "changesubdate.h"
#include "ui_changesubdate.h"

ChangeSubDate::ChangeSubDate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeSubDate)
{
    ui->setupUi(this);
}
ChangeSubDate::ChangeSubDate(QString username, QString job_id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeSubDate)
{
    ui->setupUi(this);
    connect(this, SIGNAL( fake_click_myJobs() ), this->parent()->parent()->parent()->parent(),
            SLOT( on_but_myJobs_clicked() ) );
    this->username=username;
    this->job_id=job_id;
}

ChangeSubDate::~ChangeSubDate()
{
    delete ui;
}

void ChangeSubDate::on_buttonBox_accepted()
{
    QString newstr;
    QString username,job_id;
           newstr = ui->line_subDate->text();
           username=this->username;
           job_id=this->job_id;

                 QSqlQuery query;
               query.prepare("CALL show4JobFields(?,?)");
               query.bindValue(0,username);
               query.bindValue(1,job_id);
               qDebug()<<username;
               qDebug()<<job_id;
               if(!query.exec()){
                   QMessageBox::critical(this,"Critical Error", "Could not fetch username");
                   return;
               }
              /* QString cur=QDate::currentDate().toString();
                   if (newstr<=cur){
                         QMessageBox::critical(this,"Critical Error","Sub Date has to be bigger than current date ");
               }*/
                        else{
               query.next();
               job_id = query.value(4).toString();
               qDebug()<<job_id;

               if(username.isEmpty() || job_id.isEmpty() ){
                   QMessageBox::critical(this,"Critical Error", "Could not fetch username or job_id is empty");
                   return;
               }
                query.clear();
               query.prepare("UPDATE job SET job.submission_date = ? WHERE job.evaluator_username = ? And job.job_id=?");
               query.bindValue(0,newstr);
               query.bindValue(1,username);
               query.bindValue(2,job_id);

               if(!query.exec()){
                   QMessageBox::critical(this,"Critical Error", "Could not save new Submission Date");
                   return;
               }
               else{
                   QMessageBox::information(this,"Success", "Submission Date Changed!");
               }
    }
fake_click_myJobs();
}

void ChangeSubDate::on_buttonBox_rejected()
{
        QMessageBox::information(this,"Canceled", "Submission Date did not change!");
}
