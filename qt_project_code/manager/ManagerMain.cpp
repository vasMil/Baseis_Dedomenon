#include "ManagerMain.h"
#include "ui_ManagerMain.h"
#include "DBConnect.h"

ManagerMain::ManagerMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerMain)
{
    this->setFixedSize(343,489);//this->resize(343,489);   ui->setupUi(this);
}

ManagerMain::ManagerMain(QString username, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerMain)
{
    this->setFixedSize(343,489);//this->resize(343,489);
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

ManagerMain::~ManagerMain()
{
    delete ui;
}

/*void ManagerWindow::on_pushButton_clicked() //debugging code DO NOT FORGET TO UNCOMMENT THE SLOT FROM THE HEADER
{
    QSqlQuery query;
    query.exec("SELECT @usrnm");
    query.next();
    QString str =  query.value(0).toString();
    if(str == NULL){qDebug() << "NULL";}
    qDebug() << "Str is: " << qPrintable(str);
} //gets the global value @usrnm from the db and prints it to the debuger */

void ManagerMain::on_but_myprof_clicked()
{
    prepareForNewWidget();
    ManagerProfile *myprof = new ManagerProfile(this->username);
    setupNewWidget(myprof);

}

void ManagerMain::on_but_comp_clicked()
{
    prepareForNewWidget();
    ManagerCompany *comp = new ManagerCompany(this->username);
    setupNewWidget(comp);
}

void ManagerMain::on_but_empl_clicked()
{
    prepareForNewWidget();
    ManagerEmployee *empl = new ManagerEmployee(this->username);
    setupNewWidget(empl);
}

void ManagerMain::on_but_eval_clicked()
{
    prepareForNewWidget();
    EvaluatorAverage *eval = new EvaluatorAverage(this->company);
    setupNewWidget(eval);
}

void ManagerMain::on_but_res_clicked()
{
    prepareForNewWidget();
    ManagerResult *res = new ManagerResult(this->company);
    setupNewWidget(res);
}

void ManagerMain::on_changeSalary_clicked()
{
    prepareForNewWidget();
    ChangeSalary *chsal = new ChangeSalary(this->company);
    openWidget = chsal;
    setupNewWidget(chsal);
}

void ManagerMain::on_actionLogout_triggered()
{
    exitRoutine();
    //create login window
    Login *l = new Login;
    //show new window
    l->show();
}


void ManagerMain::on_actionExit_triggered()
{
    exitRoutine();
    close();
}

void ManagerMain::exitRoutine(){
    if(openWidget != nullptr){
        delete this->openWidget;
    }
    QSqlQuery query;
    if(!query.exec("SET @usrnm = NULL")){
        qDebug() << "Did not set global variable";
    }
    close();
}

void ManagerMain::prepareForNewWidget(){
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

void ManagerMain::setupNewWidget(QWidget* widget){
    auto layout = new QVBoxLayout();
    ui->frame->autoFillBackground();
    layout->addWidget(widget);
    ui->frame->setLayout(layout);
    ui->frame->showMaximized();
}


/**********************************************************************************************************************************/
/**************************************************************** BUTTON ANIMATION ************************************************/
/**********************************************************************************************************************************/

void ManagerMain::on_but_myprof_pressed()
{
    ui->but_myprof->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 0px; background-color: #5A5150");
}

void ManagerMain::on_but_myprof_released()
{
    ui->but_myprof->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 1px; background-color: #776865");
}

void ManagerMain::on_but_comp_pressed()
{
    ui->but_comp->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 0px; background-color: #5A5150");
}

void ManagerMain::on_but_comp_released()
{
    ui->but_comp->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 1px; background-color: #776865");
}

void ManagerMain::on_but_empl_pressed()
{
    ui->but_empl->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 0px; background-color: #5A5150");
}

void ManagerMain::on_but_empl_released()
{
    ui->but_empl->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 1px; background-color: #776865");
}

void ManagerMain::on_but_eval_pressed()
{
    ui->but_eval->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 0px; background-color: #5A5150");
}

void ManagerMain::on_but_eval_released()
{
    ui->but_eval->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 1px; background-color: #776865");
}

void ManagerMain::on_but_res_pressed()
{
    ui->but_res->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 0px; background-color: #5A5150");
}

void ManagerMain::on_but_res_released()
{
    ui->but_res->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 1px; background-color: #776865");
}
