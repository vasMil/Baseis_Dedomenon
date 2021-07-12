#include "myFolder.h"
#include "ui_myFolder.h"

myFolder::myFolder(QString username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myFolder)
{
    ui->setupUi(this);
    this->username = username;
    connect(this, SIGNAL( fake_click_myFolder() ), this->parent(),
            SLOT( on_but_myFolder_clicked() ) );

    QSqlQuery q;

       /************************************* Determine how many rows will be returned *************************************************/
       q.prepare("CALL getDegrees(?)");
       q.bindValue(0,username);
       if(!q.exec()){
           QMessageBox::critical(this, "Critical Error", "Could not fetch Degrees!");
       }


        int rows = 0;
        while(q.next()){
            rows++;
        }
        ui->degrees->setRowCount(rows);
        q.clear();
        /********************************* END - Determine how many rows will be returned *************************************************/

        q.prepare("CALL getDegrees(?)");
        q.bindValue(0,username);
        if(!q.exec()){
            QMessageBox::critical(this, "Critical Error", "Could not fetch Degrees!");
        }

        int row_count = 0;
        while(q.next()){
            for(int j = 0; j < 5; j++){
                auto *cell = new QTableWidgetItem;
                cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
                cell->setText(q.value(j).toString());
                if(j == 2){
                    cell->setText(QString::number(q.value(j).toFloat()));
                }
                ui->degrees->setItem(row_count,j,cell);
                ui->degrees->item(row_count,j)->setBackground(QColorConstants::Gray);
                ui->degrees->item(row_count,j)->setTextAlignment(Qt::AlignCenter);
            }
            row_count++;
        }
        q.clear();
/*****************************************************************************************************************************/
/*****************************************************************************************************************************/
/*****************************************************************************************************************************/
/*****************************************************************************************************************************/
        ui->projects->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

/************************************* Determine how many rows will be returned *************************************************/
        q.prepare("CALL getProjects(?)");
        q.bindValue(0,username);
        if(!q.exec()){
            QMessageBox::critical(this, "Critical Error", "Could not fetch projects!");
        }
         rows = 0;
         while(q.next()){
             rows++;
         }
         ui->projects->setRowCount(rows);
         q.clear();
         /********************************* END - Determine how many rows will be returned *************************************************/

         q.prepare("CALL getProjects(?)");
         q.bindValue(0,username);
         if(!q.exec()){
             QMessageBox::critical(this, "Critical Error", "Could not fetch projects!");
         }

         row_count = 0;
         while(q.next()){
             for(int j = 0; j < 3; j++){
                 auto *cell = new QTableWidgetItem;
                 if(j == 0){
                     cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
                 }
                 cell->setText(q.value(j).toString());
                 ui->projects->setItem(row_count,j,cell);
                 ui->projects->item(row_count,j)->setBackground(QColorConstants::Gray);
                 ui->projects->item(row_count,j)->setTextAlignment(Qt::AlignCenter);
             }
             row_count++;
         }
         q.clear();

}

myFolder::~myFolder()
{
    delete ui;
}

void myFolder::on_addnew_deg_clicked()
{
    int lastRowIndex = ui->degrees->rowCount();
    ui->degrees->insertRow(lastRowIndex);
    lastRowIndex = ui->degrees->rowCount() - 1;
    QComboBox *bathmida_enum = new QComboBox;
    bathmida_enum->setEditable(true);
    bathmida_enum->lineEdit()->setReadOnly(true);
    bathmida_enum->lineEdit()->setAlignment(Qt::AlignCenter);
    bathmida_enum->addItem("     LYKEIO");
    bathmida_enum->addItem("     UNIV");
    bathmida_enum->addItem("     MASTER");
    bathmida_enum->addItem("     PHD");
    bathmida_enum->setStyleSheet("background: #a8a4a4; font: 12px;");
    ui->degrees->setCellWidget(lastRowIndex,0, bathmida_enum);
    for (int col = 1; col < 5; col++){
        auto *cell = new QTableWidgetItem;
        cell->setTextAlignment(Qt::AlignCenter);
        ui->degrees->setItem(lastRowIndex,col,cell);
        ui->degrees->item(lastRowIndex,col)->setBackground(QColorConstants::Gray);
    }
    this->newDegCount++;
}

void myFolder::on_addnew_proj_clicked()
{
    int num;
    int lastRowIndex = ui->projects->rowCount();
    ui->projects->insertRow(lastRowIndex);
    lastRowIndex = ui->projects->rowCount() - 1;
    for (int col = 0; col < 3; col++){
        auto *cell = new QTableWidgetItem;
        if(col == 0){
            num = (lastRowIndex != 0) ? ui->projects->item(lastRowIndex - 1,0)->text().toInt() + 1 : 1;
            cell->setText(QString::number(num));
        }
        cell->setTextAlignment(Qt::AlignCenter);
        ui->projects->setItem(lastRowIndex,col,cell);
        ui->projects->item(lastRowIndex,col)->setBackground(QColorConstants::Gray);
    }
}

void myFolder::on_buttonBox_rejected()
{
    fake_click_myFolder();
}

void myFolder::on_buttonBox_accepted()
{
    QSqlQuery q;
    int i;
    for(i = 0; i < ui->projects->rowCount(); i++){
        q.prepare("CALL project_update(?,?,?,?)");
        q.bindValue(0,this->username);
        q.bindValue(1,ui->projects->item(i,0)->text());
        q.bindValue(2,ui->projects->item(i,1)->text());
        q.bindValue(3,ui->projects->item(i,2)->text());
        if(!q.exec()){
            QMessageBox::critical(this, "Projects did not update as expected!\n\n", q.lastError().text());
            fake_click_myFolder();
        }
    }
    q.clear();
    int lastRow = ui->degrees->rowCount() - 1;
    if(lastRow == -1){return;}
    for(i = lastRow; i > lastRow - this->newDegCount; i--){
        q.prepare("CALL degree_update(?,?,?,?,?,?)");
        q.bindValue(0,this->username);
        q.bindValue(1,ui->degrees->item(i,1)->text());
        q.bindValue(2,ui->degrees->item(i,2)->text());
        q.bindValue(3,ui->degrees->item(i,3)->text());
        QComboBox *temp = new QComboBox;
        temp = (QComboBox*)ui->degrees->cellWidget(i,0);
        q.bindValue(4,temp->currentText().trimmed());
        q.bindValue(5,ui->degrees->item(i,4)->text());
        if(!q.exec()){
            QMessageBox::critical(this, "Degrees did not update as expected!\n\n", q.lastError().text());
            fake_click_myFolder();
            return;
        }
    }

}
