#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

QString encouraging[5]={
    "精诚所至，金石为开。",
    "锲而舍之，朽木不折；锲而不舍，金石可镂。",
    "天道酬勤。",
    "暂时不能给你明确答复。",
    "日日行，不怕千万里；常常做，不怕千万事。"
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ReadFile();
    cout<<"read passed"<<endl;
    Draw();
    cout<<"draw passed"<<endl;
    Encouraging();
    cout<<"words passed"<<endl;
    BMIset();
    cout<<"bmi passed"<<endl;
    Updateplan();
    cout<<"updateplan passed"<<endl;
    Updatelabel();
    connect(ui->chooseUser,SIGNAL(triggered()),this,SLOT(ChooseUser()));
    connect(ui->setGoal,SIGNAL(triggered()),this,SLOT(SetGoal()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_update_clicked()
{
    newwindow=new DataInWindow();
    newwindow->show();
}

void MainWindow::ChooseUser()
{
    choosewindow=new ChooseUserWindow();
    choosewindow->show();
}

void MainWindow::SetGoal()
{
    setwindow=new SetGoalWindow();
    setwindow->show();
}

void MainWindow::ReadFile()
{
    currentfile.loadData();
}

void MainWindow::Draw()
{
    QChart *chart = new QChart();
    chart->legend()->hide();

    currentfile.loadData();
    QLineSeries *lineseries = new QLineSeries();
    int datalength=currentfile.tallandweightdata.length();
    for(int i=1;i<datalength+1;++i){
        *lineseries<<QPointF(i,currentfile.tallandweightdata[i-1][1].toFloat());
    }
    chart->addSeries(lineseries);
    qDebug()<<"weigth draw successful";
    if(datalength>=5){
        TestAlgorithm near;
        vector<float> time,weigth;
        for(int i=1;i<datalength+1;++i){
            time.push_back(i);
            weigth.push_back(currentfile.tallandweightdata[i-1][1].toFloat());
        }
        QLineSeries *nearline=new QLineSeries();
        string kind=near.getBestFittingAlgorithm(time,weigth);
        qDebug()<<kind;
        switch (kind[0]){
        case 'l' : {
            auto param=near.getLineParams(time,weigth);
            float k,b;
            k=param.first;
            b=param.second;
            for(int i=1;i<datalength+1;++i){
                *nearline<<QPointF(i,k*i+b);
            }
            chart->addSeries(nearline);
            break;
        }
        case 'i' : {
            auto param=near.getInverseParams(time,weigth);
            float a,b;
            a=param.first;
            b=param.second;
            for(int i=1;i<datalength+1;++i){
                *nearline<<QPointF(i,a/(i)+b);
            }
            chart->addSeries(nearline);
            break;
        }
        case 't' : {
            auto param=near.getThreeTimesParams(time,weigth);
            float a,b,c,d;
            a=get<0>(param);
            b=get<1>(param);
            c=get<2>(param);
            d=get<3>(param);
            for(int i=1;i<datalength+1;++i){
                *nearline<<QPointF(i,(a*i+b)*(i-c)*(i-c)+d);
            }
            chart->addSeries(nearline);
            break;
        }
        case 's' : {
            auto param=near.getSigmaParams(time,weigth);
            float a=param;
            for(int i=1;i<datalength+1;++i){
                *nearline<<QPointF(i,a/(1+exp(-i)));
            }
            chart->addSeries(nearline);
            break;
        }
        }
    }

    chart->createDefaultAxes();
    ui->weight_graphic->setChart(chart);
}

void MainWindow::Encouraging()
{
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(0, 4);
    int random=distr(eng);
    ui->label_encouraging->setText(encouraging[random]);
}

void MainWindow::BMIset()
{
    currentfile.loadData();
    float bmi;
    if(currentfile.tallandweightdata.isEmpty()){
        qDebug()<<currentfile.tallandweightdata;
        bmi=0;
    }
    else{
        bmi=currentfile.tallandweightdata.last()[1].toFloat()/
              (currentfile.tallandweightdata.last()[0].toFloat()*currentfile.tallandweightdata.last()[0].toFloat())*10000;
    }
    ui->label_bmi->setText(QString::number(bmi,'f',1));
}

void MainWindow::Updateplan()
{
    currentfile.loadData();
    if(!currentfile.eatandsportdata.isEmpty())
    {
        int datasize=currentfile.eatandsportdata.size();
        int datasize2=currentfile.suggestnextdaydata.size();
        ui->label_breakfast->setText(currentfile.eatandsportdata[datasize-3][0]);
        ui->label_b_val->setText(currentfile.suggestnextdaydata[datasize2-2][0]);
        ui->label_lunch->setText(currentfile.eatandsportdata[datasize-3][1]);
        ui->label_l_val->setText(currentfile.suggestnextdaydata[datasize2-2][1]);
        ui->label_dinner->setText(currentfile.eatandsportdata[datasize-3][2]);
        ui->label_d_val->setText(currentfile.suggestnextdaydata[datasize2-2][2]);

        ui->label_sport_1->setText(currentfile.eatandsportdata[datasize-1][0]);
        ui->label_sport_1_val->setText(currentfile.suggestnextdaydata[datasize2-1][0]);
        ui->label_sport_2->setText(currentfile.eatandsportdata[datasize-1][1]);
        ui->label_sport_2_val->setText(currentfile.suggestnextdaydata[datasize2-1][1]);
        ui->label_sport_3->setText(currentfile.eatandsportdata[datasize-1][2]);
        ui->label_sport_3_val->setText(currentfile.suggestnextdaydata[datasize2-1][2]);
    }else{
        ui->label_breakfast->setText("No Data");
        ui->label_b_val->setText("No Data");
        ui->label_lunch->setText("No Data");
        ui->label_l_val->setText("No Data");
        ui->label_dinner->setText("No Data");
        ui->label_d_val->setText("No Data");

        ui->label_sport_1->setText("No Data");
        ui->label_sport_1_val->setText("No Data");
        ui->label_sport_2->setText("No Data");
        ui->label_sport_2_val->setText("No Data");
        ui->label_sport_3->setText("No Data");
        ui->label_sport_3_val->setText("No Data");
    }

}

void MainWindow::Updatelabel()
{
    currentfile.loadData();
    if(!currentfile.keyandvaluedata.isEmpty())
    {
        QString gweigth=currentfile.keyandvaluedata[0][0];
        QString gtime=currentfile.keyandvaluedata[0][1];
        ui->label_goal_weigth->setText(gweigth);
        ui->label_goal_time->setText(gtime);
    }else{
        qDebug()<<"keyandvaluedata empty";
    }
}

void MainWindow::Updatewindow()
{
    ReadFile();
    Draw();
    Encouraging();
    BMIset();
    Updateplan();
    Updatelabel();
}

void MainWindow::on_pushButton_update_clicked()    //刷新
{
    Updatewindow();
}

