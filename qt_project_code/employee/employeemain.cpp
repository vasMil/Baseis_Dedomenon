#include "employeemain.h"
#include "ui_employeemain.h"

EmployeeMain::EmployeeMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmployeeMain)
{
    ui->setupUi(this);
}
EmployeeMain::EmployeeMain(QString username ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmployeeMain)
{
    this->setFixedSize(341,489);//this->resize(343,489);
       this->username = username;
       QSqlQuery q;
       q.prepare("SELECT firm_afm FROM manager WHERE username = ?");
       q.bindValue(0,this->username);
       if(!q.exec()){
           QMessageBox::critical(this,"Critical Error", "Could not find company");
           this->close();
       }
       q.next();
       this->company = q.value(0).toString();
       q.clear();

       ui->setupUi(this);
       QPixmap pic(":/images/evaluation_cropped.png");
       setWindowIcon(pic);
}
EmployeeMain::~EmployeeMain()
{
    delete ui;
}

void EmployeeMain::on_but_profile_clicked()
{
    prepareForNewWidget();
    EmployeeProfile *prof = new EmployeeProfile(this->username, this);
    setupNewWidget(prof);
}

void EmployeeMain::on_but_applications_clicked()
{
    prepareForNewWidget();
    EmployeeApplications *appl = new EmployeeApplications(this->username, this);
    setupNewWidget(appl);
}

void EmployeeMain::on_but_myFolder_clicked()
{
    prepareForNewWidget();
    myFolder *folder = new myFolder(this->username, this);
    setupNewWidget(folder);
}



void EmployeeMain::on_actionLog_Out_triggered()
{
       exitRoutine();
       //create login window
       Login *l = new Login;
       //show new window
       l->show();
}

void EmployeeMain::on_actionExit_triggered()
{
        exitRoutine();
        close();
}

void EmployeeMain::exitRoutine(){
    if(openWidget != nullptr){
        delete this->openWidget;
    }
    QSqlQuery query;
    if(!query.exec("SET @usrnm = NULL")){
        qDebug() << "Did not set global variable";
    }
    close();
}

void EmployeeMain::prepareForNewWidget(){
    if(this->size() != QSize(891,489)){
        this->setFixedSize(891,489); //this->resize(881,489);
        this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), //center the app after resize
                                              qApp->desktop()->availableGeometry(this)));
    }

    if ( ui->frame->layout() != NULL ){
        QLayoutItem* item;
        while ( ( item = ui->frame->layout()->takeAt( 0 ) ) != NULL ) //if layout !empty -> delete all contents -> delete layout
        {
            delete item->widget();
            delete item;
        }
        delete ui->frame->layout();
    }

    if(this->openWidget != nullptr){
        this->openWidget = nullptr;
    }
}

void EmployeeMain::setupNewWidget(QWidget* widget){
    auto layout = new QVBoxLayout();
    ui->frame->autoFillBackground();
    layout->addWidget(widget);
    ui->frame->setLayout(layout);
    ui->frame->showMaximized();
}


/**********************************************************************************************************************************/
/**************************************************************** BUTTON ANIMATION ************************************************/
/**********************************************************************************************************************************/


void EmployeeMain::on_but_applications_pressed()
{

    ui->but_applications->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 0px; background-color: #5A5150");
}

void EmployeeMain::on_but_applications_released()
{

    ui->but_applications->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 1px; background-color: #776865");
}


void EmployeeMain::on_but_profile_pressed()
{

    ui->but_profile->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 0px; background-color: #5A5150");
}

void EmployeeMain::on_but_profile_released()
{

    ui->but_profile->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 1px; background-color: #776865");
}


void EmployeeMain::on_but_myFolder_pressed()
{
    ui->but_myFolder->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 0px; background-color: #5A5150");
}

void EmployeeMain::on_but_myFolder_released()
{
    ui->but_myFolder->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 1px; background-color: #776865");
}
