#include "evaluatormain.h"
#include "ui_evaluatormain.h"

EvaluatorMain::EvaluatorMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EvaluatorMain)
{
    ui->setupUi(this);
}
EvaluatorMain::EvaluatorMain(QString username, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EvaluatorMain)
{
    ui->setupUi(this);
    this->setFixedSize(343,489);
    this->username=username;
}


EvaluatorMain::~EvaluatorMain()
{
    delete ui;
}



void EvaluatorMain::exitRoutine(){
    if(openWidget != nullptr){
        delete this->openWidget;
    }
    QSqlQuery query;
    if(!query.exec("SET @usrnm = NULL")){
        qDebug() << "Did not set global variable";
    }
    close();
}

void EvaluatorMain::prepareForNewWidget(){
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

void EvaluatorMain::setupNewWidget(QWidget* widget){
    auto layout = new QVBoxLayout();
    ui->frame->autoFillBackground();
    layout->addWidget(widget);
    ui->frame->setLayout(layout);
    ui->frame->showMaximized();
}
void EvaluatorMain::on_actionLog_Out_triggered()
{
    exitRoutine();
    //create login window
    Login *l = new Login;
    //show new window
    l->show();
}

void EvaluatorMain::on_actionExit_triggered()
{
    exitRoutine();
    close();
}
void EvaluatorMain::on_but_myJobs_clicked()
{
    prepareForNewWidget();
    MyJobs *mj = new MyJobs(this->username);
    setupNewWidget(mj);
}

void EvaluatorMain::on_but_profile_clicked()
{
    prepareForNewWidget();
    EvaluatorProfile *prof = new EvaluatorProfile(this->username);
    setupNewWidget(prof);
}

void EvaluatorMain::on_but_jobs_clicked()
{
    prepareForNewWidget();
    EvaluatorJobs *j = new EvaluatorJobs(this->username);
    setupNewWidget(j);
}

void EvaluatorMain::on_but_results_clicked()
{
    prepareForNewWidget();
    EvalResults *j = new EvalResults(this->username);
    setupNewWidget(j);
}
void EvaluatorMain::on_but_myResults_clicked()
{
    prepareForNewWidget();
    MyResultsEval *j = new MyResultsEval(this->username, this);
    setupNewWidget(j);
}
/**********************************************************************************************************************************/
/**************************************************************** BUTTON ANIMATION ************************************************/
/**********************************************************************************************************************************/

void EvaluatorMain::on_but_profile_pressed()
{
    ui->but_profile->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 0px; background-color: #5A5150");

}

void EvaluatorMain::on_but_profile_released()
{
    ui->but_profile->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 1px; background-color: #776865");
}





void EvaluatorMain::on_but_jobs_pressed()
{
    ui->but_jobs->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 0px; background-color: #5A5150");
}

void EvaluatorMain::on_but_jobs_released()
{
    ui->but_jobs->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 1px; background-color: #776865");
}





void EvaluatorMain::on_but_myJobs_released()
{
    ui->but_myJobs->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 1px; background-color: #776865");

}



void EvaluatorMain::on_but_myJobs_pressed()
{
    ui->but_myJobs->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 0px; background-color: #5A5150");
}



void EvaluatorMain::on_but_results_pressed()
{
    ui->but_results->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 0px; background-color: #5A5150");
}

void EvaluatorMain::on_but_results_released()
{
    ui->but_results->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 1px; background-color: #776865");
}


void EvaluatorMain::on_but_myResults_pressed()
{
    ui->but_myResults->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 0px; background-color: #5A5150");
}

void EvaluatorMain::on_but_myResults_released()
{
    ui->but_myResults->setStyleSheet(" border-style: outset; border-radius: 10px;"
                                    "border-color: black; font: bold 12px; border-width: 1px; background-color: #776865");

}


