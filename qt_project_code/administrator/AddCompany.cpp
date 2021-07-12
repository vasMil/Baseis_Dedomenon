#include "AddCompany.h"
#include "ui_AddCompany.h"

AddCompany::AddCompany(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCompany)
{
    ui->setupUi(this);
    this->p = parent;
    connect(this, SIGNAL( decr_child_count() ), this->p, SLOT( decr_child_count() ) );
    connect(this, SIGNAL( update_child(QWidget*) ), this->p, SLOT( update_child(QWidget*) ) );
}

AddCompany::AddCompany(QVariant ar[], QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCompany)
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

    ui->lineEdit_afm->setText(ar[0].toString());
    ui->lineEdit_doy->setText(ar[1].toString());
    ui->lineEdit_name->setText(ar[2].toString());
    ui->lineEdit_phone->setText(ar[3].toString());
    ui->lineEdit_country->setText(ar[4].toString());
    ui->lineEdit_city->setText(ar[5].toString());
    ui->lineEdit_street->setText(ar[6].toString());
    ui->lineEdit_number->setText(ar[7].toString());
}

void AddCompany::closeEvent(QCloseEvent *event)
{
    fixParent();
    event->accept();
}

AddCompany::~AddCompany()
{
    delete ui;
}

void AddCompany::on_buttonBox_accepted()
{
    bool flag = 0;
    QVariant ar[8];
    ar[0] = ui->lineEdit_afm->text();
    ar[1] = ui->lineEdit_doy->text();
    ar[2] = ui->lineEdit_name->text();
    ar[3] = ui->lineEdit_phone->text();
    ar[4] = ui->lineEdit_country->text();
    ar[5] = ui->lineEdit_city->text();
    ar[6] = ui->lineEdit_street->text();
    ar[7] = ui->lineEdit_number->text();

    //Make sure all lineEdits are full
    for(int i = 0; i < 8; i++){
        if(ar[i] == ""){
            auto *n = new AddCompany(ar,this->p);
            n->show();
            update_child(n);
            flag = 1;
            break;
        }
    }

    if(!flag){
        //check if there is already a user with that username
        QSqlQuery query;
        query.prepare("SELECT afm FROM company WHERE afm = ?");
        query.bindValue(0,ar[0]);
        if (!query.exec()) {
            QMessageBox::critical(this,"Query ERROR","That is not a valid company");
            return;
        }
        query.next();
        if(query.value(0).toString() != ""){
            QMessageBox::critical(this, "Critical Error", "There is already a company registered with that afm");
        }
        else{
            //execute mysql statement -> insert user
            query.clear();
            query.prepare("INSERT INTO company(afm, doy, name, phone, country, city, street, street_num) VALUES (?,?,?,?,?,?,?,?)");
            for(int i = 0; i < 8; i++){
                query.bindValue(i,ar[i]);
            }
            if(!query.exec()){
                QMessageBox::critical(this, "Critical Error", "Something went wrong - COMPANY INSERT FAILED!");
            }

        }

        fixParent();
    }
    else{
        QMessageBox::warning(this, "Warning!", "No field can be empty!");
    }
}

void AddCompany::on_buttonBox_rejected()
{
    fixParent();
}

void AddCompany::fixParent(){
    this->p->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->p->size(), //center the app after resize
                                       qApp->desktop()->availableGeometry(this->p)));
    decr_child_count();
}
