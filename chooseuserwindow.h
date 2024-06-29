#ifndef CHOOSEUSERWINDOW_H
#define CHOOSEUSERWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "datamanager.h"
#include "createuserwindow.h"

namespace Ui {
class ChooseUserWindow;
}

class ChooseUserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseUserWindow(QWidget *parent = nullptr);
    ~ChooseUserWindow();
    void login();    //登录
    void registr();    //注册用户

private slots:
    void on_pushButton_login_clicked();    //登录

    void on_pushButton_register_clicked();    //注册，呼出注册页面

private:
    Ui::ChooseUserWindow *ui;
    DataManager currentfile;
    CreateUserWindow createwindow;
};

#endif // CHOOSEUSERWINDOW_H
