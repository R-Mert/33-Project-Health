#ifndef DATAINWINDOW_H
#define DATAINWINDOW_H

#include <QMainWindow>
#include <random>
#include "datamanager.h"
#include "agl.cpp"

namespace Ui {
class DataInWindow;
}

class DataInWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DataInWindow(QWidget *parent = nullptr);
    ~DataInWindow();

private slots:
    void on_pushButton_clicked();    //将填写好的数据提交

private:
    Ui::DataInWindow *ui;
    DataManager currentfile;
    RecommendationCalculator calculate_in;

};

#endif // DATAINWINDOW_H
