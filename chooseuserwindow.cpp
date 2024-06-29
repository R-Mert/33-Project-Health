#include "chooseuserwindow.h"
#include "ui_chooseuserwindow.h"

ChooseUserWindow::ChooseUserWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChooseUserWindow)
{
    ui->setupUi(this);
}

ChooseUserWindow::~ChooseUserWindow()
{
    delete ui;
}

void ChooseUserWindow::on_pushButton_login_clicked()
{
    currentfile.loadData();
    QString name;
    QString password;
    name=ui->lineEdit_ID->text();
    password=ui->lineEdit_password->text();
    if(currentfile.checkUser(name,password)){
        QString tmp="cache.txt";
        QFile Cache(tmp);
        if (!Cache.open(QIODevice::WriteOnly)) {
            qWarning() << "无法打开文件进行读取: " << Cache.errorString();
        }
        QTextStream out(&Cache);
        out.seek(0);
        out<<"";
        QString defaultFilePath = name + "_file.txt";
        qDebug()<<"here "+defaultFilePath;

        out<<defaultFilePath;
        Cache.close();
        this->close();
    }else{
        QMessageBox::warning(this,"注意","用户不存在！请检查账号密码是否正确，或者注册新账号！",QMessageBox::Ok);
    }
}


void ChooseUserWindow::on_pushButton_register_clicked()
{
    QString name;
    QString password;
    name=ui->lineEdit_ID->text();
    password=ui->lineEdit_password->text();
    createwindow.show();
}

