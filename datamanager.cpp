#include "datamanager.h"
#include <QDebug>

DataManager::DataManager(QObject *parent) : QObject(parent)
{
    upgradecache();
}

void DataManager::keyandvalue(const QStringList &data)
{
    keyandvaluedata.clear();
    keyandvaluedata.append(data);
}

void DataManager::tallandweight(const QStringList &data)
{
    tallandweightdata.append(data);
}

void DataManager::eatandsport(const QStringList &data)
{
    eatandsportdata.append(data);
}

void DataManager::suggestnextday(const QStringList &data)
{
    suggestnextdaydata.append(data);
}

void DataManager::saveData()
{
    upgradecache();
    QFile file(filelocation);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "无法打开文件进行写入: " << file.errorString();
        return;
    }
    QDataStream out(&file);

    saveTable(keyandvaluedata, out);
    saveTable(tallandweightdata, out);
    saveTable(eatandsportdata, out);
    saveTable(suggestnextdaydata, out);

    file.close();
    qDebug() << "数据已成功保存";
}

void DataManager::loadData()
{
    upgradecache();
    QFile file(filelocation);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "无法打开文件进行读取: " << file.errorString();
        return;
    }
    QDataStream in(&file);

    loadTable(keyandvaluedata, in);
    loadTable(tallandweightdata, in);
    loadTable(eatandsportdata, in);
    loadTable(suggestnextdaydata, in);

    file.close();

    qDebug() << "数据已成功加载";
    qDebug() << "keyandvaluedata:" << keyandvaluedata;
    qDebug() << "tallandweightdata:" << tallandweightdata;
    qDebug() << "eatandsportdata:" << eatandsportdata;
    qDebug() << "suggestnextdaydata:" << suggestnextdaydata;
}

void DataManager::saveTable(const QList<QStringList> &tableData, QDataStream &out)
{
    int rows = tableData.size();
    out << rows;
    for (const QStringList &row : tableData) {
        out << row;
    }
}

void DataManager::loadTable(QList<QStringList> &tableData, QDataStream &in)
{
    int rows;
    in >> rows;
    tableData.clear();
    for (int i = 0; i < rows; ++i) {
        QStringList row;
        in >> row;
        tableData.append(row);
    }
}

void DataManager::upgradecache()
{
    QString tmp="cache.txt";
    QFile Cache(tmp);
    if (!Cache.open(QIODevice::ReadOnly)) {
        qWarning() << "无法打开文件进行读取: " << Cache.errorString();
        return;
    }
    QTextStream in(&Cache);
    filelocation=in.readLine();
    Cache.close();
}

bool DataManager::checkUser(const QString &username, const QString &password)
{
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() >= 2 && parts[0] == username && parts[1] == password) {
            return true;
        }
    }
    return false;
}

QString DataManager::getUserAddress(const QString &username)
{
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() >= 3 && parts[0] == username) {
            return parts[2];
        }
    }
    return QString();
}

bool DataManager::createUser(const QString &username, const QString &password, const QString &heigth, const QString &weigth, const QString &goal_weigth, const QString &goal_time)
{
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return false;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() >= 2 && parts[0] == username) {
            return false; // User already exists
        }
    }

    QTextStream out(&file);
    file.seek(file.size());
    QString defaultFilePath = username + "_file.txt";
    out << username << "," << password << "," << defaultFilePath << "\n";

    // Create the user's file
    QFile userFile(defaultFilePath);
    if (!userFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QString tmp="cache.txt";
    //QString tmp=QDir::currentPath() + "/cache.txt";
    QFile Cache(tmp);
    if (!Cache.open(QIODevice::WriteOnly)) {
        qWarning() << "无法打开文件进行读取: " << Cache.errorString();
    }
    QTextStream changecache(&Cache);
    changecache.seek(0);
    changecache<<"";
    changecache<<defaultFilePath;
    Cache.close();

    loadData();

    QStringList goal={goal_weigth,goal_time,"1"};
    keyandvalue(goal);

    QStringList body={heigth,weigth};
    tallandweight(body);
    saveData();
    userFile.close();

    return true;
}
