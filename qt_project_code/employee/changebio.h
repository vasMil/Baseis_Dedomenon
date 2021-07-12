#ifndef CHANGEBIO_H
#define CHANGEBIO_H

#include <QDialog>
#include "DBConnect.h"
namespace Ui {
class ChangeBio;
}

class ChangeBio : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeBio(QWidget *parent = nullptr);
    ~ChangeBio();

signals:
    void fake_click_profile();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ChangeBio *ui;
};

#endif // CHANGEBIO_H
