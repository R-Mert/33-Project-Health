#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QDebug>
#include <iostream>

#include "datainwindow.h"
#include "chooseuserwindow.h"
#include "datamanager.h"
#include "setgoalwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_update_clicked();    //数据输入窗口
    void ChooseUser();    //用户选择窗口
    void SetGoal();    //目标设置窗口
    void ReadFile();    //读取存档
    void Draw();    //绘制图表
    void Encouraging();    //随机激励语
    void BMIset();    //BMI
    void Updateplan();    //同步窗口信息
    void Updatewindow();    //刷新窗口
    void Updatelabel();    //更新目标体重、天数显示
    void on_pushButton_update_clicked();    //刷新页面按钮

private:
    Ui::MainWindow *ui;
    ChooseUserWindow *choosewindow;
    DataInWindow *newwindow;
    SetGoalWindow *setwindow;
    DataManager currentfile;
};
#endif // MAINWINDOW_H
