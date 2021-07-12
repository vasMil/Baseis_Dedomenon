#ifndef MANAGERCOMPANY_H
#define MANAGERCOMPANY_H

#include <QWidget>
#include "DBConnect.h"

namespace Ui {
class ManagerCompany;
}

class ManagerCompany : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerCompany(QWidget *parent = nullptr);
    explicit ManagerCompany(QString username, QWidget *parent = nullptr);
    ~ManagerCompany();

private slots:

    void on_lineEdit_phone_returnPressed();

    void on_lineEdit_country_returnPressed();

    void on_lineEdit_city_returnPressed();

    void on_lineEdit_street_returnPressed();

    void on_lineEdit_num_returnPressed();

    void on_pushButton_update_pressed();

private:
//Using functions. Documentation instructs that signals must not have a return type
//and in forums it is said that neither should slots.
//Tried implementing with slots having a return type (bool) but I was getting a warning
//like: "QMetaObject::connectSlotsByName: No matching signal for".
//Even thought all slots and signals where connected and triggered as expected
//I decided that it was an abnormal behaviour and decided to stick with a different technique:
//slots that call normal c++ functions;

    bool phone_returnPressed(bool i = 0);
    bool country_returnPressed(bool i = 0);
    bool city_returnPressed(bool i = 0);
    bool street_returnPressed(bool i = 0);
    bool num_returnPressed(bool i = 0);

    Ui::ManagerCompany *ui;
};


#endif // MANAGERCOMPANY_H
