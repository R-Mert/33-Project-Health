#ifndef CREATEUSERWINDOW_H
#define CREATEUSERWINDOW_H

#include <QMainWindow>
#include "datamanager.h"

namespace Ui {
class CreateUserWindow;
}

class CreateUserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateUserWindow(QWidget *parent = nullptr);
    ~CreateUserWindow();

private slots:
    void on_pushButton_create_clicked();    //创建用户

private:
    Ui::CreateUserWindow *ui;
    DataManager currentfile;
};

#endif // CREATEUSERWINDOW_H
