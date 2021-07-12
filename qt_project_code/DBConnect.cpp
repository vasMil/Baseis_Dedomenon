#include "DBConnect.h"
#include "ui_DBConnect.h"

DBConnect::DBConnect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DBConnect)
{
    ui->setupUi(this);

    //QPixmap pic(":/images/evaluation_cropped.png");
    //setWindowIcon(pic);
}

DBConnect::~DBConnect()
{
    delete ui;
}

void DBConnect::on_pushButton_clicked()
{
    QString hname, usrname, pass, dbname;
    int port;
    hname = ui->hostname->text();
    port = ui->port->text().toInt();
    usrname = ui->username->text();
    pass = ui->password->text();
    dbname = ui->database->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");
    db.setHostName(hname);
    db.setPort(port);
    db.setUserName(usrname);
    db.setPassword(pass);
    db.setDatabaseName(dbname);

    if(db.open()){
        QSqlQuery query;
        QString exstr = "USE " + dbname;
        if(!query.exec(exstr)){
            QMessageBox::critical(this, "USE ERROR", "Failed to execute USE <database_name>; query");
        }
    }
    else {
         QMessageBox::warning(this, "Not Connected", "Database is not connected");
         this->close();
    }

    Login *login_wind = new Login(); //create a new window of type LoginWindow
    login_wind->QWidget::setWindowTitle("Login Database - " + dbname);
    this->close();//closes the main window (hide() may also be used)
    login_wind->show(); //show the newly created window

}

void DBConnect::on_toolButton_clicked()
{
    QMessageBox::information(this, "Help", "Using ODBC. If the server is setup locally, connect as root using your password\n"
                                    "As Database name use the one that you have declared in your odbc connector");
}
