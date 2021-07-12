#include "ManagerCompany.h"
#include "ui_ManagerCompany.h"

ManagerCompany::ManagerCompany(QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerCompany)
{
    QMetaObject::connectSlotsByName(0);

    ui->setupUi(this);

    QSqlQuery q;
    q.prepare("CALL getComp(?)"); //DOKIMASA NA KANO TO SELECT EDO ALLA DEN MOU TO EPETREPSE
    q.bindValue(0,username);      //MALLON TO ODBC DEN YPOSTHRIZEI (INNER) JOIN
    if(!q.exec()){
        QMessageBox::critical(this,"Critical Error", "Could not find company");
        this->close();
    }
    q.next();
    ui->lineEdit_name->setText(q.value(0).toString());
    ui->lineEdit_afm->setText(q.value(1).toString());
    ui->lineEdit_doy->setText(q.value(2).toString());
    ui->lineEdit_phone->setText(q.value(3).toString());
    ui->lineEdit_country->setText(q.value(4).toString());
    ui->lineEdit_city->setText(q.value(5).toString());
    ui->lineEdit_street->setText(q.value(6).toString());
    ui->lineEdit_num->setText(q.value(7).toString());

    QString logo = ":/images/logo_" + q.value(1).toString() + ".png";
    QPixmap l(logo);
    ui->comp_logo->setPixmap(l);
    //get labels dimentions
    int w = ui->comp_logo->width();
    int h = ui->comp_logo->height();
    //set scaled pixmap and maintain aspect ratio
    ui->comp_logo->setPixmap(l.scaled(w,h,Qt::KeepAspectRatio));
}

ManagerCompany::~ManagerCompany()
{
    delete ui;
}


/*********************************************************************************************/
/************************************* FUNCTIONS *********************************************/
/*********************************************************************************************/

bool ManagerCompany::phone_returnPressed(bool i)
{
    QSqlQuery q;
    QString newphone, afm;
    afm = ui->lineEdit_afm->text();
    newphone = ui->lineEdit_phone->text();
    q.prepare("UPDATE company SET phone = ? WHERE afm = ?");
    q.bindValue(0,newphone);
    q.bindValue(1,afm);
    if(!q.exec() && !i){
        QMessageBox::critical(this,"Critical Error", "Phone number is not updated!");
        return 0;
    }
    else if(!i){
        QMessageBox::information(this,"Success", "Phone number updated successfully!");
    }
    else if(!q.exec() && i){
        return 0;
    }
    return 1;
}

bool ManagerCompany::country_returnPressed(bool i)
{
    QSqlQuery q;
    QString newcountry, afm;
    afm = ui->lineEdit_afm->text();
    newcountry = ui->lineEdit_country->text();
    q.prepare("UPDATE company SET country = ? WHERE afm = ?");
    q.bindValue(0,newcountry);
    q.bindValue(1,afm);
    if(!q.exec() && !i){
        QMessageBox::critical(this,"Critical Error", "Country field is not updated!");
        return 0;
    }
    else if(!i){
        QMessageBox::information(this,"Success", "Country field updated successfully!");
    }
    else if(!q.exec() && i){
        return 0;
    }
    return 1;
}

bool ManagerCompany::city_returnPressed(bool i)
{
    QSqlQuery q;
    QString newcity, afm;
    afm = ui->lineEdit_afm->text();
    newcity = ui->lineEdit_city->text();
    q.prepare("UPDATE company SET city = ? WHERE afm = ?");
    q.bindValue(0,newcity);
    q.bindValue(1,afm);
    if(!q.exec() && !i){
        QMessageBox::critical(this,"Critical Error", "City field is not updated!");
        return 0;
    }
    else if(!i){
        QMessageBox::information(this,"Success", "City field updated successfully!");
    }
    else if(!q.exec() && i){
        return 0;
    }
    return 1;
}



bool ManagerCompany::street_returnPressed(bool i)
{
    QSqlQuery q;
    QString newstreet, afm;
    afm = ui->lineEdit_afm->text();
    newstreet = ui->lineEdit_street->text();
    q.prepare("UPDATE company SET street = ? WHERE afm = ?");
    q.bindValue(0,newstreet);
    q.bindValue(1,afm);
    if(!q.exec() && !i){
        QMessageBox::critical(this,"Critical Error", "Street field is not updated!");
        return 0;
    }
    else if(!i){
        QMessageBox::information(this,"Success", "Street field updated successfully!");
    }
    else if(!q.exec() && i){
        return 0;
    }
    return 1;
}



bool ManagerCompany::num_returnPressed(bool i)
{
    QSqlQuery q;
    QString newnum, afm;
    afm = ui->lineEdit_afm->text();
    newnum = ui->lineEdit_num->text();
    q.prepare("UPDATE company SET street_num = ? WHERE afm = ?");
    q.bindValue(0,newnum);
    q.bindValue(1,afm);
    if(!q.exec() && !i){
        QMessageBox::critical(this,"Critical Error", "Street Number field is not updated!");
        return 0;
    }
    else if(!i){
        QMessageBox::information(this,"Success", "Street Number field updated successfully!");
    }
    else if(!q.exec() && i){
        return 0;
    }
    return 1;
}




/*********************************************************************************************/
/************************************* SLOTS *************************************************/
/*********************************************************************************************/

void ManagerCompany::on_lineEdit_phone_returnPressed()
{
    phone_returnPressed(0);
}

void ManagerCompany::on_lineEdit_country_returnPressed()
{
    country_returnPressed(0);
}

void ManagerCompany::on_lineEdit_city_returnPressed()
{
    city_returnPressed(0);
}



void ManagerCompany::on_lineEdit_street_returnPressed()
{
    street_returnPressed(0);
}



void ManagerCompany::on_lineEdit_num_returnPressed()
{
    num_returnPressed(0);
}


void ManagerCompany::on_pushButton_update_pressed()
{
    QString errors = "The fields below did not update:\n";
    bool ph, count, city, stre, num;
    ph = phone_returnPressed(1);
    count = country_returnPressed(1);
    city = city_returnPressed(1);
    stre = street_returnPressed(1);
    num = num_returnPressed(1);

    if(ph && count && city && stre && num){
        QMessageBox::information(this,"Success", "All fields updated successfully");
    }
    else{
        if(!ph){
            errors += "-> Phone Number\n";

        }
        if(!count){
            errors += "-> Country\n";
        }
        if(!city){
            errors += "-> City\n";
        }
        if(!stre){
            errors += "-> Street\n";
        }
        if(!num){
            errors += "-> Street Number\n";
        }
        QMessageBox::critical(this,"Critical Error", errors);
    }
}


