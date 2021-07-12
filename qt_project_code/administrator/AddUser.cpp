#include "AddUser.h"
#include "ui_AddUser.h"
#include "DBConnect.h"

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
    this->p = parent;
    QSqlQuery q;
    q.prepare("SELECT afm FROM company");
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch AFMs");
    }
    while(q.next()){
        ui->comboBox_afm->addItem(q.value(0).toString());
    }
    connect(this, SIGNAL( decr_child_count() ), this->p, SLOT( decr_child_count() ) );
    connect(this, SIGNAL( update_child(QWidget*) ), this->p, SLOT( update_child(QWidget*) ) );
}

AddUser::AddUser(QVariant ar[], QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
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

    QSqlQuery q;
    q.prepare("SELECT afm FROM company");
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch AFMs");
    }
    while(q.next()){
        ui->comboBox_afm->addItem(q.value(0).toString());
    }
    //itarate through the list and set lineEdit text;
    //QListIterator<QVariant> i(list);
    //or that
    ui->lineEdit_username->setText(ar[0].toString());
    ui->lineEdit_password->setText(ar[1].toString());
    ui->lineEdit_name->setText(ar[2].toString());
    ui->lineEdit_surname->setText(ar[3].toString());
    ui->lineEdit_email->setText(ar[4].toString());
    ui->lineEdit_exp->setText(ar[5].toString());
    ui->comboBox_afm->setCurrentText(ar[6].toString());

}

void AddUser::closeEvent(QCloseEvent *event)
{
    fixParent();
    event->accept();
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::on_buttonBox_accepted()
{
    bool flag = 0;
    QVariant ar[7];
    ar[0] = ui->lineEdit_username->text();
    ar[1] = ui->lineEdit_password->text();
    ar[2] = ui->lineEdit_name->text();
    ar[3] = ui->lineEdit_surname->text();
    ar[4] = ui->lineEdit_email->text();
    ar[5] = ui->lineEdit_exp->text();
    ar[6] = ui->comboBox_afm->currentText();

    //Make sure all lineEdits are full
    for(int i = 0; i < 6; i++){
        if(ar[i] == ""){
            auto *n = new AddUser(ar,this->p);
            n->show();
            update_child(n);
            flag = 1;
            break;
        }
    }

    if(!flag){
        //check if there is already a user with that username
        QSqlQuery query;
        query.prepare("CALL verify_user(?, ?)");
        query.bindValue(0,ar[0]);
        query.bindValue(1,ar[1]);
        if (!query.exec()) {
            QMessageBox::critical(this,"Query ERROR","That is not a valid account");
            return;
        }
        query.next();
        if(query.value(0).toInt() != -1){
            QMessageBox::critical(this, "Critical Error", "There is already a user registered with that username");
        }
        else{
            //execute mysql statement -> insert user
            query.clear();
            query.prepare("INSERT INTO user(username, password, name, surname, email) VALUES (?,?,?,?,?)");
            for(int i = 0; i < 6; i++){
                query.bindValue(i,ar[i]);
            }
            if(!query.exec()){
                QMessageBox::critical(this, "Critical Error", "Something went wrong - USER INSERT FAILED!");
            }
            else{
                query.clear();
                query.prepare("INSERT INTO " + ui->comboBox_users->currentText() + "(username, firm_afm, exp_years) VALUES (?,?,?)");
                query.bindValue(0,ar[0]);
                query.bindValue(1,ar[6]);
                query.bindValue(2,ar[5]);
                if(!query.exec()){
                    QMessageBox::critical(this, "Critical Error", "Something went wrong - " + ui->comboBox_users->currentText() + " INSERT FAILED!");
                }
            }

        }

        fixParent();
    }
    else{
        QMessageBox::warning(this, "Warning!", "No field can be empty!");
    }
}

void AddUser::on_buttonBox_rejected()
{
    fixParent();
}

void AddUser::fixParent(){
    this->p->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->p->size(), //center the app after resize
                                       qApp->desktop()->availableGeometry(this->p)));
    decr_child_count();
}
