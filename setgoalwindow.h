#ifndef SETGOALWINDOW_H
#define SETGOALWINDOW_H

#include <QMainWindow>

#include "datamanager.h"

namespace Ui {
class SetGoalWindow;
}

class SetGoalWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SetGoalWindow(QWidget *parent = nullptr);
    ~SetGoalWindow();
    void Setlabel();

private slots:
    void on_pushButton_clicked();    //更改目标

private:
    Ui::SetGoalWindow *ui;
    DataManager currentfile;
};

#endif // SETGOALWINDOW_H
