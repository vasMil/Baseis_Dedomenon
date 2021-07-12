#include "AddSubject.h"
#include "ui_AddSubject.h"

AddSubject::AddSubject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSubject)
{
    ui->setupUi(this);
    this->p = parent;

    ////////////////////////////////////////////////////////////////////////////SETUP THE COMBOBOXES
    QSqlQuery q;
    q.prepare("SELECT title FROM subject");
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch subjects");
    }
    while(q.next()){
        ui->comboBox_belongs_to->addItem(q.value(0).toString());
    }
    q.clear();

    q.prepare("SELECT job_id, position FROM job");
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch jobs");
    }
    while(q.next()){
        ui->comboBox_job_requires->addItem(q.value(0).toString() + ": " + q.value(1).toString());
    }
    q.clear();
    ///////////////////////////////////////////////////////////////////////////////////////////


    connect(this, SIGNAL( decr_child_count() ), this->p, SLOT( decr_child_count() ) );
    connect(this, SIGNAL( update_child(QWidget*) ), this->p, SLOT( update_child(QWidget*) ) );
}

AddSubject::AddSubject(QVariant ar[], QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSubject)
{
    ui->setupUi(this);
    this->p = parent;
    connect(this, SIGNAL( decr_child_count() ), this->p, SLOT( decr_child_count() ) );
    connect(this, SIGNAL( update_child(QWidget*) ), this->p, SLOT( update_child(QWidget*) ) );

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //set window in the middle of the screen
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(),
                                       qApp->desktop()->availableGeometry(this)));
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////SETUP THE COMBOBOXES
    QSqlQuery q;
    q.prepare("SELECT title FROM subject");
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch subjects");
    }
    while(q.next()){
        ui->comboBox_belongs_to->addItem(q.value(0).toString());
    }
    q.clear();

    q.prepare("SELECT job_id, position FROM job");
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch jobs");
    }
    while(q.next()){
        ui->comboBox_job_requires->addItem(q.value(0).toString() + ": " + q.value(1).toString());
    }
    q.clear();
    ///////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////SETUP textEdit and lineEdit and combobox choice after wrong accept
    ui->lineEdit_title->setText(ar[0].toString());
    ui->textEdit_description->setText(ar[1].toString());
    ui->comboBox_belongs_to->setCurrentText(ar[2].toString());
    ui->comboBox_job_requires->setCurrentText(ar[3].toString());
    //////////////////////////////////////////////////////////////////////////////////////////
}

AddSubject::~AddSubject()
{
    delete ui;
}

void AddSubject::fixParent(){
    this->p->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->p->size(), //center the app after resize
                                       qApp->desktop()->availableGeometry(this->p)));
    decr_child_count();
}

void AddSubject::on_buttonBox_rejected()
{
    fixParent();
}

void AddSubject::closeEvent(QCloseEvent *event)
{
    fixParent();
    event->accept();
}

void AddSubject::on_buttonBox_accepted()
{
    bool flag = 0, in_job = 1;
    QVariant ar[4];
    ar[0] = ui->lineEdit_title->text();
    ar[1] = ui->textEdit_description->toPlainText();
    ar[2] = ui->comboBox_belongs_to->currentText();
    ar[3] = ui->comboBox_job_requires->currentText();

    //Make sure all lineEdits are full
    if(ar[0] == "" || ar[1] == ""){
        auto *n = new AddSubject(ar,this->p);
        n->show();
        update_child(n);
        flag = 1;
    }
    if(ar[3] == ""){
        in_job = 0;
    }

    if(!flag){
        //check if there is already a subject with that title
        QSqlQuery query;
        //execute mysql statement -> insert subject
        query.clear();
        query.prepare("INSERT INTO subject(title, descr, belongs_to) VALUES(?,?,?)");
        for(int i = 0; i < 3; i++){
            query.bindValue(i,ar[i]);
        }
        if(!query.exec()){ //query did not execute
            QMessageBox::critical(this, "Critical Error", "Something went wrong - There is already a subject with that title (most likely)");
        }
        else if(in_job){ //query did execute
            query.clear();
            query.prepare("INSERT INTO job_requires(job_id, sub_title) VALUES (?,?)");
            query.bindValue(1,ar[0]);
            //split job_id from ar[3] which is like job_id: position
            ar[3] = ar[3].toString().split(": ")[0];
            //split-end
            query.bindValue(0,ar[3]);
            if(!query.exec()){
                QMessageBox::critical(this, "Critical Error", "Something went wrong - JOB_REQUIRES INSERT FAILED!");
            }
         }
        fixParent();
    }
    else{
        QMessageBox::warning(this, "Warning!", "Title and Description can not be empty!");
    }
}
