#include "setgoalwindow.h"
#include "ui_setgoalwindow.h"

SetGoalWindow::SetGoalWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SetGoalWindow)
{
    ui->setupUi(this);
    Setlabel();
}

SetGoalWindow::~SetGoalWindow()
{
    delete ui;
}

void SetGoalWindow::Setlabel(){
    currentfile.loadData();
    auto weigth=currentfile.keyandvaluedata[0][0];
    auto time=currentfile.keyandvaluedata[0][1];
    ui->label_goalweigth->setText(weigth);
    ui->label_goaltime->setText(time);
}

void SetGoalWindow::on_pushButton_clicked()
{
    currentfile.loadData();
    auto newweigth=ui->lineEdit_newweigth->text();
    auto newtime=ui->lineEdit_newtime->text();
    auto param=currentfile.keyandvaluedata[0][2];
    currentfile.keyandvalue({newweigth,newtime,param});
    currentfile.saveData();
    this->close();
}

