#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>

class DataManager : public QObject
{
    Q_OBJECT

public:
    explicit DataManager(QObject *parent = nullptr);//
    void saveData();    //保存修改
    void loadData();    //读取存档
    void keyandvalue(const QStringList &data);    //修改目标体重、天数、推荐算法参数
    void tallandweight(const QStringList &data);    //添加身高、体重记录
    void eatandsport(const QStringList &data);    //添加食谱、运动记录
    void suggestnextday(const QStringList &data);    //添加历史推荐记录
    void upgradecache();    //更新当前读取存档
    bool checkUser(const QString &username, const QString &password);    //检查用户是否存在
    QString getUserAddress(const QString &username);    //获取用户地址
    bool createUser(const QString &username, const QString &password, const QString &heigth, const QString &weigth, const QString &goal_weigth, const QString &goal_time);    //创建用户存档

    QString filelocation;
    QList<QStringList> keyandvaluedata;
    QList<QStringList> tallandweightdata;
    QList<QStringList> eatandsportdata;
    QList<QStringList> suggestnextdaydata;

private:
    void saveTable(const QList<QStringList> &tableData, QDataStream &out);
    void loadTable(QList<QStringList> &tableData, QDataStream &in);
};

#endif // DATAMANAGER_H
