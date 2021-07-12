#include "ManagerEmployee.h"
#include "ui_ManagerEmployee.h"

ManagerEmployee::ManagerEmployee(QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerEmployee)
{
    ui->setupUi(this);
    ui->tableWidget_compl->hide();
    ui->label_compl->hide();
    ui->tableWidget_progr->hide();
    ui->label_progr->hide();

    QString employee;
    QSqlQuery q;
    q.prepare("CALL getEmployees_ofManager(?)");
    q.bindValue(0,username);
    if(!q.exec()){
        QMessageBox::critical(this,"Critical Error", "Failed to fetch employees");
        this->close();
    }
    while(q.next()){
        employee += q.value(0).toString();
        employee += ' ';
        employee += q.value(1).toString();
        ui->comboBox->addItem(employee);
        employee.clear();
    }
}

ManagerEmployee::~ManagerEmployee()
{
    delete ui;
}

void ManagerEmployee::on_but_show_clicked()
{
    this->show(); //fere to para8iro sto proskinio
    ui->tableWidget_compl->show();
    ui->tableWidget_progr->show();
    ui->label_compl->show();
    ui->label_progr->show();

    QString empl = ui->comboBox->currentText();
    auto parts = empl.split(' '); //https://doc.qt.io/qt-5/qstring.html#split
    QString name, surname;
    surname = parts[0];
    name = parts[1];
    //qDebug() << "Surname: " << surname << "Name: " << name;

    QSqlQuery q;
    q.prepare("CALL get_all_applications(?,?)");
    q.bindValue(0,name);
    q.bindValue(1,surname);
    if(!q.exec()){
        QMessageBox::critical(this,"Critical Error", "Could not retrieve applications!");
    }
    QString id, pos, salary, evname, evsur, ph1, ph2, ph3, total;

    int num_compl = 0, num_progr = 0;
    while(q.next()){
          if(q.value(5).toString() == "-1"){
                num_progr++;
          }
          else{
                num_compl++;
          }
    }
    ui->tableWidget_progr->setRowCount(num_progr);
    ui->tableWidget_compl->setRowCount(num_compl);
    q.clear();

    q.prepare("CALL get_all_applications(?,?)");
    q.bindValue(0,name);
    q.bindValue(1,surname);
    if(!q.exec()){
        QMessageBox::critical(this,"Critical Error", "Could not retrieve applications!");
    }
    int i1 = 0, i2 = 0;
    while(q.next()){
        if(q.value(5).toString() == "-1"){
              for(int j = 0; j < 9; j++){
                  auto *cell = new QTableWidgetItem;
                  QString temp;
                  if(q.value(j).toString() == "-1"){temp = "NULL";}else{temp =q.value(j).toString();}
                  cell->setText(temp);
                  ui->tableWidget_progr->setItem(i1,j,cell);
              }
              i1++;
        }
        else{
            for(int j = 0; j < 6; j++){
                auto *cell = new QTableWidgetItem;
                QString temp;
                if(q.value(j).toString() == "-1"){temp = "NULL";}else{temp =q.value(j).toString();}
                cell->setText(temp);
                ui->tableWidget_compl->setItem(i2,j,cell);
            }
            //auto *cell = new QTableWidgetItem;
            //cell->setText(q.value(8).toString());
            //ui->tableWidget_compl->setItem(i2,5,cell);

            i2++;
        }
    }
}

void ManagerEmployee::on_but_update_clicked()
{
    QSqlQuery q;
    QString empl = ui->comboBox->currentText();
    auto parts = empl.split(' ');
    QString name, surname;
    surname = parts[0];
    name = parts[1];

    q.prepare("SELECT username FROM user WHERE user.name = ? AND user.surname = ?");
    q.bindValue(0,name);
    q.bindValue(1,surname);
    if(!q.exec()){
        QMessageBox::critical(this,"Critical Error", "Could not get employee's username");
    }
    q.next();
    empl = q.value(0).toString();
    if(this->child != nullptr){
        this->child->close();
    }
    EmployeeCertificates *d = new EmployeeCertificates(empl,this);
    this->child = d;
    d->show();
}
