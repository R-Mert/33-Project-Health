#include "datainwindow.h"
#include "ui_datainwindow.h"

using namespace std;

map<QString,float> foods={{"  ",0},{"燕麦片，香蕉，果仁",3.5},{"鸡胸肉沙拉，橄榄油醋汁",4.0},{"烤鲈鱼，蒸蔬菜，糙米",3.8},{"全麦吐司，鸡蛋，西红柿",3.0},{"鳗鱼寿司卷，鲜蔬沙拉",3.5},{"烤鸡柳，烤红薯，绿叶蔬菜",3.5},
                             {"希腊酸奶，蓝莓，坚果",2.5},{"烤三文鱼，烤蔬菜，糙米",4.2},{"紫甘蓝鸡肉卷，糙米饭",4.0},{"菠菜蘑菇蛋煎饼，水果沙拉",3.2},{"手撕鸡胸肉色拉，沙拉酱",3.8},{"烤鳕鱼，蔬菜炒饭",3.9},
                             {"烤麦片，酸奶，水果块",2.8},{"烤鸡腿，意大利面，番茄酱",3.6},{"烤羊排，烤蔬菜，番茄意大利面",4.5},{"燕麦片，杏仁，鲜果沙拉",3.5},{"清炒时蔬，蒸鸡胸肉",4.0},{"茄汁炒虾仁，蒸青菜，玉米粥",3.8},
                             {"全麦吐司，鳄梨，荷包蛋",3.0},{"紫薯饭团，海苔沙拉",3.5},{"白灼鸡脯，凉拌海带丝",3.5},{"杂粮粥，红枣，核桃",2.5},{"红烧茄子，扬州炒饭",4.2},{"茄汁豆腐，蒸时蔬，莜麦面条",4.0},{"蒸鲈鱼，凉拌黄瓜",3.8},
                             {"紫菜豆腐汤，海带沙拉",3.9},{"高纤水果燕麦粥，全麦面包",2.8},{"蒸蛋羹，糙米饭，酸辣土豆丝",3.6},{"粗粮虾仁炒饭，凉拌海带丝",4.5},{"煎荷包蛋，全麦吐司，新鲜水果",3.0},{"鸡肉沙拉，橄榄油醋汁",4.0},
                             {"鲈鱼蒸蔬菜，莲藕莜麦粥",3.8},{"酸奶，水果，麦片",2.5},{"黑米，鱼香肉丝，香菇青菜汤",3.5},{"煎三文鱼，绿叶蔬菜沙拉",3.5},{"燕麦粥，果仁，水煮蛋",3.2},{"烤三文鱼，糙米饭，清炒时蔬",4.2},
                             {"紫甘蓝蒸鸡块，红豆小米粥",4.0},{"全麦面包夹火腿，牛奶",2.8},{"青椒肉丝，红烧茄子，糙米饭",3.8},{"素炒豆腐，糙米饭，凉拌海带丝",3.9},{"杂粮粥，红枣，豆浆",3.0},{"香煎鸡胸，炒时蔬，糙米饭",3.6},
                             {"清蒸鲈鱼，炒时蔬，糙米饭",4.5}};
map<QString,float> sports={{"  ",0},{"跑步",0.05},{"游泳",0.05},{"篮球",0.06},{"羽毛球",0.1},{"网球",0.05}};

QStringList positive={"幸福","快乐","感激","有希望","喜悦","幸运","温暖","欢欣","笑容","美好","开心"};
QStringList negtive={"悲伤","沮丧","愤怒","压抑","焦虑","恐惧","绝望","失望","痛苦","烦闷","伤心"};

vector<vector<QString>> p={{"燕麦片，香蕉，果仁","鸡胸肉沙拉，橄榄油醋汁","烤鲈鱼，蒸蔬菜，糙米"},{"全麦吐司，鸡蛋，西红柿","鳗鱼寿司卷，鲜蔬沙拉","烤鸡柳，烤红薯，绿叶蔬菜"},
                             {"希腊酸奶，蓝莓，坚果","烤三文鱼，烤蔬菜，糙米","紫甘蓝鸡肉卷，糙米饭"},{"菠菜蘑菇蛋煎饼，水果沙拉","手撕鸡胸肉色拉，沙拉酱","烤鳕鱼，蔬菜炒饭"},
                             {"烤麦片，酸奶，水果块","烤鸡腿，意大利面，番茄酱","烤羊排，烤蔬菜，番茄意大利面"}};
vector<vector<QString>> n={{"燕麦片，杏仁，鲜果沙拉","清炒时蔬，蒸鸡胸肉","茄汁炒虾仁，蒸青菜，玉米粥"},{"全麦吐司，鳄梨，荷包蛋","紫薯饭团，海苔沙拉","白灼鸡脯，凉拌海带丝"},
                             {"杂粮粥，红枣，核桃","红烧茄子，扬州炒饭","茄汁豆腐，蒸时蔬，莜麦面条"},{"菠菜蘑菇蛋煎饼，水果沙拉","蒸鲈鱼，凉拌黄瓜","紫菜豆腐汤，海带沙拉"},
                             {"高纤水果燕麦粥，全麦面包","蒸蛋羹，糙米饭，酸辣土豆丝","粗粮虾仁炒饭，凉拌海带丝"}};
vector<vector<QString>> plain={{"煎荷包蛋，全麦吐司，新鲜水果","鸡肉沙拉，橄榄油醋汁","鲈鱼蒸蔬菜，莲藕莜麦粥"},{"酸奶，水果，麦片","黑米，鱼香肉丝，香菇青菜汤","煎三文鱼，绿叶蔬菜沙拉"},
                                 {"燕麦粥，果仁，水煮蛋","烤三文鱼，糙米饭，清炒时蔬","紫甘蓝蒸鸡块，红豆小米粥"},{"全麦面包夹火腿，牛奶","青椒肉丝，红烧茄子，糙米饭","素炒豆腐，糙米饭，凉拌海带丝"},
                                 {"杂粮粥，红枣，豆浆","香煎鸡胸，炒时蔬，糙米饭","清蒸鲈鱼，炒时蔬，糙米饭"}};

vector<QString> GetRecommendations(QString str){
    vector<QString> rec;
    QStringList tmp=str.split(" ");
    int emotion=0;
    foreach(QString i,tmp){
        if(positive.contains(i)){
            ++emotion;
        }else if(negtive.contains(i)){
            --emotion;
        }
    }

    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(0, 4);

    if(emotion==0){
        rec=plain[distr(eng)];
    }else if(emotion<0){
        rec=n[distr(eng)];
    }else{
        rec=p[distr(eng)];
    }
    rec.push_back("跑步");
    rec.push_back("跑步");
    rec.push_back("跑步");
    return rec;
}

DataInWindow::DataInWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DataInWindow)
{
    ui->setupUi(this);
}

DataInWindow::~DataInWindow()
{
    delete ui;
}

void DataInWindow::on_pushButton_clicked()    //输入数据处理
{
    QString height=ui->inheigth->text();
    QString weigth=ui->inweight->text();
    QStringList bodydata={height,weigth};

    QString breakfast_today=ui->comboBox_breakfast_today->currentText();
    QString breakfast_val=ui->lineEdit_breakfast->text();
    QString lunch_today=ui->comboBox_lunch_today->currentText();
    QString lunch_val=ui->lineEdit_lunch->text();
    QString dinner_today=ui->comboBox_dinner_today->currentText();
    QString dinner_val=ui->lineEdit_dinner->text();

    QString sport_morning_today=ui->comboBox_sport_morning_today->currentText();
    QString sport_m_val=ui->lineEdit_sport_m->text();
    QString sport_noon_today=ui->comboBox_sport_noon_today->currentText();
    QString sport_n_val=ui->lineEdit_sport_n->text();
    QString sport_evening_today=ui->comboBox_sport_evening_today->currentText();
    QString sport_e_val=ui->lineEdit_sport_e->text();

    QString text=ui->textEdit_keyword->toPlainText();
    QString breakfast_tomorrow;
    QString lunch_tomorrow;
    QString dinner_tomorrow;
    QString sport_morning_tomorrow;
    QString sport_noon_tomorrow;
    QString sport_evening_tomorrow;
    if(text.isEmpty()){
        breakfast_tomorrow=ui->comboBox_breakfast_tomorrow->currentText();
        lunch_tomorrow=ui->comboBox_lunch_tomorrow->currentText();
        dinner_tomorrow=ui->comboBox_dinner_tomorrow->currentText();

        sport_morning_tomorrow=ui->comboBox_sport_morning_tomorrow->currentText();
        sport_noon_tomorrow=ui->comboBox_sport_noon_tomorrow->currentText();
        sport_evening_tomorrow=ui->comboBox_sport_evening_tomorrow->currentText();
    }else{
        vector<QString> list=GetRecommendations(text);
        breakfast_tomorrow=list[0];
        lunch_tomorrow=list[1];
        dinner_tomorrow=list[2];

        sport_morning_tomorrow=list[3];
        sport_noon_tomorrow=list[4];
        sport_evening_tomorrow=list[5];
    }

    QStringList eatdata_today={breakfast_today,lunch_today,dinner_today,breakfast_val,lunch_val,dinner_val};
    QStringList eatdata_tomorrow={breakfast_tomorrow,lunch_tomorrow,dinner_tomorrow};
    QStringList sportdata_today={sport_morning_today,sport_noon_today,sport_evening_today,sport_m_val,sport_n_val,sport_e_val};
    QStringList sportdata_tomorrow={sport_morning_tomorrow,sport_noon_tomorrow,sport_evening_tomorrow};

    currentfile.loadData();
    currentfile.tallandweight(bodydata);
    currentfile.eatandsport(eatdata_today);
    currentfile.eatandsport(eatdata_tomorrow);
    currentfile.eatandsport(sportdata_today);
    currentfile.eatandsport(sportdata_tomorrow);
    currentfile.saveData();


    float goal_time=currentfile.keyandvaluedata[0][1].toFloat();
    float goal_weight=currentfile.keyandvaluedata[0][0].toFloat();
    float suggestparam=currentfile.keyandvaluedata[0][2].toFloat();

    float nweigth=currentfile.tallandweightdata.last()[1].toFloat();
    float nheight=currentfile.tallandweightdata.last()[0].toFloat();

    int datasize=currentfile.eatandsportdata.size();
    int datasize2=currentfile.suggestnextdaydata.size();
    QString b_val="104.2";
    QString l_val="145.1";
    QString d_val="137.5";
    QString m_val="0.2";
    QString n_val="0.5";
    QString e_val="0.1";
    QString goalweigth=currentfile.keyandvaluedata[0][0];
    QString newtime=QString::number((currentfile.keyandvaluedata[0][1]).toInt()-1);
    QString param="1";
    if(datasize2!=0)
    {
        float nbreakfast_today=currentfile.eatandsportdata[datasize-4][3].toFloat();
        float nlunch_today=currentfile.eatandsportdata[datasize-4][4].toFloat();
        float ndinner_today=currentfile.eatandsportdata[datasize-4][5].toFloat();

        float nbreakfast_tomorrow=foods[currentfile.eatandsportdata[datasize-3][0]];
        float nlunch_tomorrow=foods[currentfile.eatandsportdata[datasize-3][1]];
        float ndinner_tomorrow=foods[currentfile.eatandsportdata[datasize-3][2]];

        float nsport_morning_today=currentfile.eatandsportdata[datasize-2][3].toFloat();
        float nsport_noon_today=currentfile.eatandsportdata[datasize-2][4].toFloat();
        float nsport_evening_today=currentfile.eatandsportdata[datasize-2][5].toFloat();

        float nsport_morning_tomorrow=sports[currentfile.eatandsportdata[datasize-1][0]];
        float nsport_noon_tomorrow=sports[currentfile.eatandsportdata[datasize-1][1]];
        float nsport_evening_tomorrow=sports[currentfile.eatandsportdata[datasize-1][2]];

        float history_breakfast=currentfile.suggestnextdaydata[datasize2-2][0].toFloat();
        float history_lunch=currentfile.suggestnextdaydata[datasize2-2][1].toFloat();
        float history_dinner=currentfile.suggestnextdaydata[datasize2-2][2].toFloat();

        float history_morning=currentfile.suggestnextdaydata[datasize2-1][0].toFloat();
        float history_noon=currentfile.suggestnextdaydata[datasize2-1][1].toFloat();
        float history_evening=currentfile.suggestnextdaydata[datasize2-1][2].toFloat();

        tuple<float, float, float> diet_tomorrow=std::make_tuple(nbreakfast_tomorrow,nlunch_tomorrow,ndinner_tomorrow);
        tuple<float, float, float> sport_tomorrow=std::make_tuple(nsport_morning_tomorrow,nsport_noon_tomorrow,nsport_evening_tomorrow);

        pair<float, float> nbreakfast=std::make_pair(nbreakfast_today,history_breakfast);
        pair<float, float> nlunch=std::make_pair(nlunch_today,history_lunch);
        pair<float, float> ndinner=std::make_pair(ndinner_today,history_dinner);
        tuple<pair<float, float>, pair<float, float>, pair<float, float> > diet_pair=std::make_tuple(nbreakfast,nlunch,ndinner);

        pair<float, float> morning=std::make_pair(nsport_morning_today,history_morning);
        pair<float, float> noon=std::make_pair(nsport_noon_today,history_noon);
        pair<float, float> evening=std::make_pair(nsport_evening_today,history_evening);
        tuple<float,int,float> sparam=std::make_tuple(goal_weight,goal_time,suggestparam);
        tuple<pair<float, float>, pair<float, float>, pair<float, float> > sport_pair=std::make_tuple(morning,noon,evening);

        std::tuple<std::tuple<float, float, float>, std::tuple<float,float,float>, std::tuple<float,int, float> > suggest=calculate_in.getRecommendationAndUpdatedParams(nheight, nweigth, diet_pair, sport_pair, diet_tomorrow, sport_tomorrow, sparam);

        b_val=QString::number(std::get<0>(std::get<0>(suggest)),'f',1);
        l_val=QString::number(std::get<1>(std::get<0>(suggest)),'f',1);
        d_val=QString::number(std::get<2>(std::get<0>(suggest)),'f',1);

        m_val=QString::number(std::get<0>(std::get<1>(suggest)),'f',1);
        n_val=QString::number(std::get<1>(std::get<1>(suggest)),'f',1);
        e_val=QString::number(std::get<2>(std::get<1>(suggest)),'f',1);

        newtime=QString::number(std::get<1>(std::get<2>(suggest)));
        param=QString::number(std::get<2>(std::get<2>(suggest)));

    }

    currentfile.suggestnextday({b_val,l_val,d_val});
    currentfile.suggestnextday({m_val,n_val,e_val});

    currentfile.keyandvalue({goalweigth,newtime,param});
    currentfile.saveData();

    this->close();

}

