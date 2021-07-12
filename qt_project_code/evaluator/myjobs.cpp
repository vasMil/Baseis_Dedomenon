#include "myjobs.h"
#include "ui_myjobs.h"

MyJobs::MyJobs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyJobs)
{
    ui->setupUi(this);
}
MyJobs::MyJobs(QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyJobs)
{
    ui->setupUi(this);
    this->username = username;
    QSqlQuery q;
    ui->comboBox_myjobs->addItem("");
            q.prepare("CALL showMyJobs(?)");
            q.bindValue(0,username);

            if(!q.exec()){
                QMessageBox::critical(this, "Critical Error", "Could not fetch jobs");
            }
            while(q.next()){
                ui->comboBox_myjobs->addItem(q.value(0).toString() + ": " + q.value(1).toString());
            }
            q.clear();
}

MyJobs::~MyJobs()
{
    delete ui;
}



void MyJobs::on_pushButton_salary_clicked()
{
    auto *d = new ChangeEvalSalary(this->username,this->job_id ,this);
            d->show();
}

void MyJobs::on_pushButton_startDate_clicked()
{

    auto *d = new ChangeStartDate(this->username,this->job_id ,this);
            d->show();
}

void MyJobs::on_pushButton_subDate_clicked()
{
    auto *d = new ChangeSubDate(this->username,this->job_id ,this);
            d->show();
}


void MyJobs::on_comboBox_myjobs_currentIndexChanged(const QString &arg1)
{
    QString username, job_id , box;
    username=this->username;
    //job_id=this->job_id;
    QSqlQuery q;
    box=ui->comboBox_myjobs->currentText();
    if(box == ""){ return; }
    auto parts= box.split(": ");
    job_id = parts[0];
    this->job_id=job_id;

    q.prepare("CALL show4JobFields(?,?)");
    q.bindValue(0,username);
    q.bindValue(1,job_id);

    if(!q.exec() && box!=""){
        QMessageBox::critical(this, "Critical Error", "Could not fetch job fields!");
        return;
    }
    while(q.next()){

        ui->lineEdit_salary->setText(q.value(0).toString());
        ui->lineEdit_anDate->setText(q.value(1).toString());
        ui->lineEdit_startDate->setText(q.value(2).toString());
        ui->lineEdit_subDate->setText(q.value(3).toString());

    }
    q.clear();

}

void MyJobs::on_pushButton_add_clicked()
{
    auto *n = new AddJobs(this->username,this);
    n->show();
}
void MyJobs::decr_child_count(){
    this->child_open--;
}
void MyJobs::update_child(QWidget *c){
    this->child = c;
}
