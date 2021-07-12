#include "changeevalsalary.h"
#include "ui_changeevalsalary.h"

ChangeEvalSalary::ChangeEvalSalary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeEvalSalary)
{
    ui->setupUi(this);
}

ChangeEvalSalary::ChangeEvalSalary(QString username, QString job_id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeEvalSalary)
{
    ui->setupUi(this);
    connect(this, SIGNAL( fake_click_myJobs() ), this->parent()->parent()->parent()->parent(),
            SLOT( on_but_myJobs_clicked() ) );
    this->username=username;
    this->job_id=job_id;
}


ChangeEvalSalary::~ChangeEvalSalary()
{
    delete ui;
}

void ChangeEvalSalary::on_buttonBox_accepted()
{
    QString newsal;
    QString username,job_id;
           newsal = ui->line_salary->text();
           username=this->username;
           job_id=this->job_id;

           if(newsal.isEmpty()){
               QMessageBox::critical(this,"Invalid Salary", "New Salary should not be empty!");
               auto *newch = new ChangeEvalSalary(this->parentWidget());
               newch->show();
               this->close();
           } else{

               QSqlQuery query;
               query.prepare("CALL show4JobFields(?,?)");
               query.bindValue(0,username);
               query.bindValue(1,job_id);
               qDebug()<<username;
               qDebug()<<job_id;
               if(!query.exec()){
                   QMessageBox::critical(this,"Critical Error", "Could not fetch username");
                   this->close();
               }
               query.next();
               job_id = query.value(4).toString();
               qDebug()<<job_id;

               if(username.isEmpty() || job_id.isEmpty() ){
                   QMessageBox::critical(this,"Critical Error", "Could not fetch username or job_id is empty");
                   this->close();
               }
                query.clear();
               query.prepare("UPDATE job SET job.salary = ? WHERE job.evaluator_username = ? And job.job_id=?");
               query.bindValue(0,newsal);
               query.bindValue(1,username);
               query.bindValue(2,job_id);

               if(!query.exec()){
                   QMessageBox::critical(this,"Critical Error", "Could not save new salary");
                   this->close();
               }
               else{
                   QMessageBox::information(this,"Success", "Salary Changed!");
               }
           }
fake_click_myJobs();
}

void ChangeEvalSalary::on_buttonBox_rejected()
{
    QMessageBox::information(this,"Canceled", "Salary did not change!");
}
