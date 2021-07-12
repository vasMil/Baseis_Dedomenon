#include "MyResultsEval.h"
#include "ui_MyResultsEval.h"

MyResultsEval::MyResultsEval(QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyResultsEval)
{
    ui->setupUi(this);
    QString job_id;
    job_id=this->job_id;
    this->username=username;
    connect(this, SIGNAL( fake_click_MyResultsEval() ), this->parentWidget()
            , SLOT( on_but_myResults_clicked() ) );
    QSqlQuery q;
    ui->comboBox_myResults->addItem(" ");

            q.prepare("CALL showMyResults(?)");
            q.bindValue(0,username);

            if(!q.exec()){
                QMessageBox::critical(this, "Critical Error", "Could not fetch jobs");
            }
            while(q.next()){
               ui->comboBox_myResults->addItem(q.value(0).toString() + ":" + q.value(1).toString()+ ":"+ q.value(2).toString());
            }
            q.clear();
}

MyResultsEval::~MyResultsEval()
{
    delete ui;
}

void MyResultsEval::on_pushButton_5_clicked()
{
    QString job_id,box,empl,ph1,ph2,ph3,comms;
    box=ui->comboBox_myResults->currentText();
    if(box == " "){
        QMessageBox::critical(this, "Critical Error", "comboBox cannot be empty!");
        return;
    }
    job_id= this->job_id;
    empl=this->empl;
    ph1=ui->lineEdit_ph1->text();
    ph2=ui->lineEdit_ph2->text();
    ph3=ui->lineEdit_ph3->text();
    comms=ui->lineEdit_comms->text();
    auto parts= box.split(":");
    job_id = parts[0];
    empl =parts[2];
    QSqlQuery q;
    if(ph1 == "NULL"){
        ph1 = "-1";
    }
    if(ph2 == "NULL"){
        ph2 = "-1";
    }
    if(ph3 == "NULL"){
        ph3 = "-1";
    }
    q.prepare(" CALL updatePhases(?,?,?,?,?,?)");
    q.bindValue(0,empl);
    q.bindValue(1,job_id);
    q.bindValue(2,ph1);
    q.bindValue(3,ph2);
    q.bindValue(4,ph3);
    q.bindValue(5,comms);
    if(!q.exec()){
       QMessageBox::critical(this, "Critical Error", "Could not fetch phases");
    }
     while(q.next()){
         ui->lineEdit_comms->setText(comms);
         ui->lineEdit_ph1->setText(ph1);
         ui->lineEdit_ph2->setText(ph2);
         ui->lineEdit_ph3->setText(ph3);
         QMessageBox::information(this,"UPDATED ","Fields updated" );
     }
     fake_click_MyResultsEval();
}

void MyResultsEval::on_comboBox_myResults_currentTextChanged(const QString &arg1)
{
    // qDebug()<<ui->comboBox_myResults->currentText();

     if(ui->comboBox_myResults->currentText()==" "){
        return;
     }
     QString username, job_id ,empl ,position, box, string_2;
     username=this->username;
     //empl= this->empl;
     job_id= this->job_id;
     QSqlQuery q;
     box=ui->comboBox_myResults->currentText();
     auto parts= box.split(":");
     job_id = parts[0];
     empl =parts[2];
     q.prepare("CALL show5ResultFields(?,?,?)");
     q.bindValue(0,username);
     q.bindValue(1,job_id);
     q.bindValue(2,empl);

    if(!q.exec() && box==" "){
       QMessageBox::critical(this, "Critical Error", "Could not fetch Results");
    }
     while(q.next()){
         ui->lineEdit_empl->setText(q.value(0).toString());
         if(q.value(1).toString() == "-1"){
             ui->lineEdit_grade->setText("Evaluation In Progress");
         }
         else{
             ui->lineEdit_grade->setText(q.value(1).toString());
         }
         if(q.value(2).toString() == "No Comments yet"){
             ui->lineEdit_comms->setText("No Comments yet");
         }
         else{
             ui->lineEdit_comms->setText(q.value(2).toString());
         }
         if(q.value(3).toString() == "-1"){
             ui->lineEdit_ph1->setText("NULL");
         }
         else{
             ui->lineEdit_ph1->setText(q.value(3).toString());
         }
         if(q.value(4).toString() == "-1"){
             ui->lineEdit_ph2->setText("NULL");
         }
         else{
             ui->lineEdit_ph2->setText(q.value(4).toString());
         }
         if(q.value(5).toString() == "-1"){
             ui->lineEdit_ph3->setText("NULL");
         }
         else{
             ui->lineEdit_ph3->setText(q.value(5).toString());
         }
     }
     q.clear();
}
