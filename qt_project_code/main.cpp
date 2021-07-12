#include "DBConnect.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBConnect m;
    m.show();
    //LoginWindow l;
    //l.show();
    /*QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("staff_evaluation");
    if(db.open()){
        QSqlQuery quse;
        quse.prepare("USE staff_evaluation");
        if(!quse.exec()){
            qDebug() << "Error while initializing db";
            exit(0);
        }
    }else{
        qDebug() << "DB not open";
        exit(0);
    }*/

    return a.exec();
}
