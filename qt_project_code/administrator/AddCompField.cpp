#include "AddCompField.h"
#include "ui_AddCompField.h"

AddCompField::AddCompField(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCompField)
{
    ui->setupUi(this);
    this->p = parent;
    connect(this, SIGNAL( decr_child_count() ), this->p, SLOT( decr_child_count() ) );

    ////////////////////////////////////////////////////////////////////////////SETUP THE COMBOBOXES
    QSqlQuery q;
    q.prepare("SELECT afm, name FROM company");
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch company afm");
    }
    while(q.next()){
        ui->comboBox_afm->addItem(q.value(0).toString() + ": " + q.value(1).toString());
    }
    q.clear();

    q.prepare("SELECT title FROM action");
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch fields of action");
    }
    while(q.next()){
        ui->comboBox_newfield->addItem(q.value(0).toString());
    }
    q.clear();
    ///////////////////////////////////////////////////////////////////////////////////////////
}

AddCompField::~AddCompField()
{
    delete ui;
}

void AddCompField::add_action(QString title, QString descr){
    //execute the insert query
    QSqlQuery q;
    q.prepare("INSERT INTO action VALUES (?,?)");
    q.bindValue(0, title);
    q.bindValue(1, descr);
    if(!q.exec()){
        centeredMessage(QMessageBox::Critical, "Critical Error!", "Could not insert new action!");
    }
    else{ //if query executed then clear textEdit and LineEdit
        ui->lineEdit_title->setText("");
        ui->textEdit_description->setText("");
        ui->comboBox_newfield->addItem(title);
    }
}

void AddCompField::add_action_to_comp(QString afm, QString newfield){
    //execute the insert query
    QSqlQuery q;
    q.prepare("INSERT INTO company_action VALUES (?,?)");
    q.bindValue(0, afm);
    q.bindValue(1, newfield);
    if(!q.exec()){
        centeredMessage(QMessageBox::Critical, "Critical Error!", "Could not insert new field of action in the specified company!");
    }
    else{ //if query executed then clear the combobox choices
        ui->comboBox_afm->setCurrentText("");
        ui->comboBox_newfield->setCurrentText("");
    }
}

void AddCompField::on_pushButton_add_clicked()
{
    QString afm, newfield;
    afm = ui->comboBox_afm->currentText().split(": ")[0];
    newfield = ui->comboBox_newfield->currentText();
    if(afm != "" && newfield != ""){
        add_action_to_comp(afm, newfield);
    }
    else{
        centeredMessage(QMessageBox::Warning,"Warning!","Company AFM and New Field can not be empty!");
    }
}

void AddCompField::on_pushButton_create_clicked()
{
    QString title, desr;
    title = ui->lineEdit_title->text();
    desr = ui->textEdit_description->toPlainText();
    if(title != "" && desr != ""){
        add_action(title, desr);
    }
    else{
        centeredMessage(QMessageBox::Warning,"Warning!","Field title and description can not be empty!");
    }
}

void AddCompField::closeEvent(QCloseEvent *event)
{
    this->p->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->p->size(), //center the app after resize
                                       qApp->desktop()->availableGeometry(this->p)));
    decr_child_count();
    event->accept();
}
