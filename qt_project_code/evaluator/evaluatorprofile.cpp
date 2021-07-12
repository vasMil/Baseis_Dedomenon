#include "evaluatorprofile.h"
#include "ui_evaluatorprofile.h"

EvaluatorProfile::EvaluatorProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EvaluatorProfile)
{
    ui->setupUi(this);
}
EvaluatorProfile::EvaluatorProfile(QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EvaluatorProfile)
{
    ui->setupUi(this);
    this->username=username;
    QString name, surname, password, exp_years, evaluator_id, firm_afm, email;
    QSqlQuery query;

    query.prepare("CALL getEvalProf(?)");
    query.bindValue(0, username);
    if(!query.exec()){
        QMessageBox::critical(this, "Username Error", "Failed to fetch username");
        }
    query.next();
    name = query.value(0).toString();
    surname = query.value(1).toString();
    password = query.value(2).toString();
    exp_years = query.value(3).toString();
    evaluator_id=query.value(4).toString();
    firm_afm=query.value(5).toString();
    email=query.value(6).toString();

    ui->lineEdit_name->setText(name);
    ui->lineEdit_surname->setText(surname);
    ui->lineEdit_username->setText(username);
    ui->lineEdit_password->setText(password);
    ui->lineEdit_exp->setText(exp_years);
    ui->lineEdit_id->setText(evaluator_id);
    ui->lineEdit_firmAfm->setText(firm_afm);
    ui->lineEdit_email->setText(email);
}


EvaluatorProfile::~EvaluatorProfile()
{
    delete ui;
}

void EvaluatorProfile::on_show_button_pressed()
{
    ui->show_button->setStyleSheet("color: rgb(0, 0, 255); font: bold; background-color: transparent;");
       ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
}

void EvaluatorProfile::on_show_button_released()
{
    ui->show_button->setStyleSheet("color: #000000; background-color: transparent;");
            ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}

void EvaluatorProfile::on_but_chpass_clicked()
{
    auto *d = new ChangeEvalPass(this);
            d->show();
}

void EvaluatorProfile::on_but_chmail_clicked()
{
    auto *d = new ChangeEvalEmail(this);
            d->show();
}
