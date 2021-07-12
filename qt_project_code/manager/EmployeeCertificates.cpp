#include "EmployeeCertificates.h"
#include "ui_EmployeeCertificates.h"

EmployeeCertificates::EmployeeCertificates(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeCertificates)
{
    ui->setupUi(this);
}

EmployeeCertificates::EmployeeCertificates(QString empl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeCertificates)
{

    ui->setupUi(this);
    this->empl = empl;
    QSqlQuery q;

    //Fetch the username of the manager
    q.prepare("SELECT @usrnm");
    if(!q.exec()){
        QMessageBox::critical(this,"Critical Error", "Could not fetch username");
        this->close();
    }
    q.next();
    this->username = q.value(0).toString();
    q.clear();

    /************************************* Determine how many rows will be returned *************************************************/
    int manag_row = 0;
    q.prepare("CALL getReports(?)");
    q.bindValue(0,empl);
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch employee's credentials");
    }

    int rows = 1; //Label: Assuming the current manager does not have a report stored for the employee
    while(q.next()){    //using a while loop, because size() function of QSqlQuery is not supported by the version of the
        rows++;         //database I am using (or the connector)
        if(q.value(0).toString() == username){
            rows--; //Assumption of Label was wrong so I remove the extra row
            this->has_report = 1; //Aswell the has_report attribute in the header file
        }
    }
    ui->tableWidget_reports->setRowCount(rows);
    q.clear();
    /********************************* END - Determine how many rows will be returned *************************************************/


    //Call again the stored procedure in order to add each row to my table
    q.prepare("CALL getReports(?)");
    q.bindValue(0,empl);
    if(!q.exec()){
        QMessageBox::critical(this, "Critical Error", "Could not fetch employee's credentials");
    }
    if(manag_row){ //if manag_row has a value -> that value -1 is the row postition of the current manager's report
        manag_row--;
    }else{
        manag_row = rows - 1; //if manag_row has no value -> manager's report row will be added to the end of the table
    }

    int row_count= 0;
    while(q.next() || row_count == manag_row){
        for(int j = 0; j < 2; j++){
            auto *cell = new QTableWidgetItem;
            QString temp;
            if(q.value(1).isNull()){
                temp = "EMPTY";
            }else{
                temp = q.value(j).toString();
            }
            if(row_count != manag_row){
                cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
                cell->setText(temp);
            }
            else if(j == 0){
                cell->setText(this->username);
                cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
            }else{
                cell->setText(temp);
            }
            ui->tableWidget_reports->setItem(row_count,j,cell);
            ui->tableWidget_reports->item(row_count,j)->setBackground(QColorConstants::Gray);
        }
        row_count++;
    }
    q.clear();

    //******************************************** Set the text to the other two textEdits ********************************************/
    q.prepare("SELECT certificates FROM employee WHERE username = ?");
    q.bindValue(0,empl);
    if(!q.exec()){
        QMessageBox::critical(this,"Critical Error", "Could not fetch employee's certificates");
    }
    q.next();
    ui->certif->setText(q.value(0).toString());
    q.clear();

    q.prepare("SELECT awards FROM employee WHERE username = ?");
    q.bindValue(0,empl);
    if(!q.exec()){
        QMessageBox::critical(this,"Critical Error", "Could not fetch employee's awards");
    }
    q.next();
    ui->awards->setText(q.value(0).toString());
    q.clear();
}

EmployeeCertificates::~EmployeeCertificates()
{
    delete ui;
}

void EmployeeCertificates::on_buttonBox_accepted()
{
    int i = 0;
    auto *cell = new QTableWidgetItem;
    cell = ui->tableWidget_reports->takeItem(i,0);
    while (this->username != cell->text()){
        i++;
        cell = ui->tableWidget_reports->takeItem(i,0);
    }
    QString rep = ui->tableWidget_reports->takeItem(i,1)->text();
    QSqlQuery q;
    //understand if there is a need of insert or update
    //in order to do that -> add an attribute in the class that will be initialized in the constructor
    //in which due to the way it is implemented is known if the manager has already written a report
    //for the employee or it will be an insert
    if(has_report){
        q.prepare("UPDATE report SET report_text = ? WHERE manager_username = ? AND employee_username = ?");
        q.bindValue(0,rep);
        q.bindValue(1,this->username);
        q.bindValue(2,this->empl);
        if(!q.exec()){
            QMessageBox::critical(this,"Critical Error", "Failed to update your report");
        }
        q.clear();
    }
    else{
        q.prepare("INSERT INTO report(manager_username, employee_username, report_text) VALUES (?, ?, ?)");
        q.bindValue(0,this->username);
        q.bindValue(1,this->empl);
        q.bindValue(2,rep);
        if(!q.exec()){
            QMessageBox::critical(this,"Critical Error", "Failed to insert your report");
        }
        q.clear();
    }

    if(ui->certif->toPlainText() != ""){
        QString cert = ui->certif->toPlainText();
        QSqlQuery q2;
        q2.prepare("UPDATE employee SET certificates = ? WHERE username = ?");
        q2.bindValue(0,cert);
        q2.bindValue(1,this->empl);
        if(!q2.exec()){
            QMessageBox::critical(this,"Critical Error", "Failed to add/update employee's certificates");
        }
        q2.clear();
    }

    if(ui->awards->toPlainText() != ""){
        QString award = ui->awards->toPlainText();
        QSqlQuery q2;
        q2.prepare("UPDATE employee SET awards = ? WHERE username = ?");
        q2.bindValue(0,award);
        q2.bindValue(1,this->empl);
        if(!q2.exec()){
            QMessageBox::critical(this,"Critical Error", "Failed to add/update employee's awards");
        }
        q2.clear();
    }
    this->close(); //it is needed cause the ui is a QWidget not a QDialog as it should have been
}

void EmployeeCertificates::on_buttonBox_rejected() //it is needed cause the ui is a QWidget not a QDialog as it should have been
{
    this->close();
}
