#ifndef MANAGERPROFILE_H
#define MANAGERPROFILE_H

#include <QWidget>

namespace Ui {
class ManagerProfile;
}

class ManagerProfile : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerProfile(QWidget *parent = nullptr);
    explicit ManagerProfile(QString username, QWidget *parent = nullptr);
    ~ManagerProfile();

private slots:
    void on_show_button_pressed();
    void on_show_button_released();

    void on_but_chpass_clicked();

    void on_but_chemail_clicked();

private:
    Ui::ManagerProfile *ui;
    QWidget* child = nullptr;
};

#endif // MANAGERPROFILE_H
