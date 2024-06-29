#include "createuserwindow.h"
#include "ui_createuserwindow.h"

CreateUserWindow::CreateUserWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CreateUserWindow)
{
    ui->setupUi(this);
}

CreateUserWindow::~CreateUserWindow()
{
    delete ui;
}

void CreateUserWindow::on_pushButton_create_clicked()
{
    QString name=ui->lineEdit_name->text();
    QString password=ui->lineEdit_password->text();
    QString heigth=ui->lineEdit_heigth->text();
    QString weigth=ui->lineEdit_weigth->text();
    QString goal_weigth=ui->lineEdit_goal_weigth->text();
    QString goal_time=ui->lineEdit_goal_time->text();
    if(name!="" && password!="" && heigth!="" && weigth!="" && goal_weigth!="" && goal_time!=""){
        currentfile.createUser(name,password,heigth,weigth,goal_weigth,goal_time);
        QMessageBox::warning(this,"注意","账户建立成功！",QMessageBox::Ok);
        this->close();
    }else{
        QMessageBox::warning(this,"注意","请完整填写信息！",QMessageBox::Ok);
    }
}

