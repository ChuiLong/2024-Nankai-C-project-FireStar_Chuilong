#include "database.h"
#include "player.h"
#include "tools.h"
#include "keys.h"
#include "monster.h"
#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

extern Player player;
extern Monster monsters[13];
extern Tools tools;
extern Keys keys;
extern int map[14][14][10];


const int kMapLen = 14;
const int kMaxFloor = 10;

DataBase::DataBase() {         // 构造函数 创建一个SQL数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
}

DataBase::~DataBase() {         // 析构函数 删除数据库
    db.close();
}

void DataBase::Connect(QString dbpath) {
    db.setDatabaseName(dbpath);//连接到数据库
    if (!db.open()) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(db.lastError().text());//获取并返回错误信息
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();//如果创建不成功，提示用户
    }

    QFile file(":/database/data.sql");         // 打开数据文件
    if(!file.exists()){
        qDebug() << "Database init file not exist, expected: " << file.fileName();
    }

    QSqlQuery query(db);//创建一个对象

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))//文件只读打开
    {
        QStringList scriptQueries = QTextStream(&file).readAll().split(';');//这行代码读取了文件中的所有内容，并按照分号将其分割成一个字符串列表，每个元素都是一个 SQL 查询语句。
        foreach (QString queryTxt, scriptQueries) {
            if (queryTxt.trimmed().isEmpty()) {
                continue;
            }
            if (!query.exec(queryTxt))
            {
                qFatal("One of the query failed to execute. Error detail: %s", query.lastError().text().toStdString().c_str());
            }
            query.finish();
        }
    }
    file.close();
    qDebug( "Database connected." );
}

void DataBase::LoadMap(int num) {         // 加载map数据，0代表新数据，否则旧数据
    QSqlQuery query(db);
    QString str = "SELECT layer0, layer1, layer2, layer3, layer4, layer5, layer6, layer7, layer8, layer9 FROM map WHERE id = " + QString::number(num+1, kDecimal);//构建了一个 SQL 查询语句，根据参数 num 的值选择加载新数据还是旧数据。
    query.exec(str);//查询
    query.next();
    for (int i = 0; i < kMaxFloor; i++) {
        QString floors = query.value(i).toString();
        floors = floors.simplified();
        int tmp = 0;
        while (floors.length() > 3) {
            map[tmp%kMapLen][tmp/kMapLen][i] = floors.left(2).toInt();
            floors.remove(0,3);
            tmp++;
        }
        map[kMapLen-1][kMapLen-1][i] = floors.toInt();
    }
    query.clear();//释放
}

void DataBase::LoadPlayer() {         // 加载人物数据
    QSqlQuery query(db);
    query.exec("SELECT hp, attack, defend, money, exp, miss, crit, level, posx, posy, floor, toward, sex, need FROM player WHERE id = 1");
    query.next();
    player.SetHp(query.value(0).toInt());
    player.SetHarm(query.value(1).toInt());
    player.SetDefend(query.value(2).toInt());
    player.SetCoin(query.value(3).toInt());
    player.SetExp(query.value(4).toInt());
    player.SetMiss(query.value(5).toInt());
    player.SetCrit(query.value(6).toInt());
    player.SetLevel(query.value(7).toInt());
    player.SetPosx(query.value(8).toInt());
    player.SetPosy(query.value(9).toInt());
    player.SetPart(query.value(10).toInt());
    player.SetToward(query.value(11).toInt());
    player.SetSex(query.value(12).toInt());
    player.SetNeed(query.value(13).toInt());
    query.clear();
}

void DataBase::LoadMonsters() {         // 加载怪物数据
    QSqlQuery query(db);
    query.exec("SELECT hp, attack, defend, money, exp, miss, crit FROM monster");
    for (int i = 0; i < 13; i++) {
        query.next();
        monsters[i].SetHp(query.value(0).toInt());
        monsters[i].SetHarm(query.value(1).toInt());
        monsters[i].SetDefend(query.value(2).toInt());
        monsters[i].SetCoin(query.value(3).toInt());
        monsters[i].SetExp(query.value(4).toInt());
        monsters[i].SetMiss(query.value(5).toInt());
        monsters[i].SetCrit(query.value(6).toInt());
    }
    query.clear();
}

void DataBase::LoadTools(int num) {         // 加载工具数据
    QSqlQuery query(db);
    QString str = "SELECT book, shield, sword FROM tools WHERE id = " + QString::number(num+1, kDecimal);
    query.exec(str);
    query.next();
    tools.SetBook(query.value(0).toInt());
    tools.SetShield(query.value(1).toInt());
    tools.SetSword(query.value(2).toInt());
    query.clear();
}

void DataBase::LoadKeys(int num) {         // 加载钥匙数据
    QSqlQuery query(db);
    QString str = "SELECT red, blue, yellow FROM keys WHERE id = " + QString::number(num+1, kDecimal);
    query.exec(str);
    query.next();
    keys.SetRed(query.value(0).toInt());
    keys.SetBlue(query.value(1).toInt());
    keys.SetYellow(query.value(2).toInt());
    query.clear();
}

void DataBase::SaveMap(int num) {         // 保存 下同
    QSqlQuery query(db);
    QString str = "UPDATE map SET layer0=?, layer1=?, layer2=?, layer3=?, layer4=?, layer5=?, layer6=?, layer7=?, layer8=?, layer9=? WHERE id=" + QString::number(num+1, kDecimal);
    query.prepare(str);
    query.bindValue(0, layer(0));
    query.bindValue(1, layer(1));
    query.bindValue(2, layer(2));
    query.bindValue(3, layer(3));
    query.bindValue(4, layer(4));
    query.bindValue(5, layer(5));
    query.bindValue(6, layer(6));
    query.bindValue(7, layer(7));
    query.bindValue(8, layer(8));
    query.bindValue(9, layer(9));
    query.exec();
    query.clear();
}

void DataBase::SavePlayer() {
    QSqlQuery query(db);
    QString str = "UPDATE player SET hp=?, attack=?, defend=?,money=?, exp=?, miss=?, crit=?, level=?, posx=?, posy=?, floor=?, toward=?, sex=?, need=? WHERE id=1";
    query.prepare(str);
    query.bindValue(0, player.GetHp());
    query.bindValue(1, player.GetAttack());
    query.bindValue(2, player.GetDefend());
    query.bindValue(3, player.GetMoney());
    query.bindValue(4, player.GetExp());
    query.bindValue(5, player.GetMiss());
    query.bindValue(6, player.GetCrit());
    query.bindValue(7, player.GetLevel());
    query.bindValue(8, player.GetPosx());
    query.bindValue(9, player.GetPosy());
    query.bindValue(10, player.GetFloor());
    query.bindValue(11, player.GetToward());
    query.bindValue(12, player.GetSex());
    query.bindValue(13, player.GetNeed());
    query.exec();
    query.clear();
}

void DataBase::SaveTools(int num) {
    QSqlQuery query(db);
    QString str = "UPDATE tools SET book=?, shield=?, sword=? WHERE id=" + QString::number(num+1, kDecimal);
    query.prepare(str);
    query.bindValue(0, tools.GetBook());
    query.bindValue(1, tools.GetShield());
    query.bindValue(2, tools.GetSword());
    query.exec();
    query.clear();
}

void DataBase::SaveKeys(int num) {
    QSqlQuery query(db);
    QString str = "UPDATE keys SET red=?, blue=?, yellow=? WHERE id=" + QString::number(num+1, kDecimal);
    query.prepare(str);
    query.bindValue(0, keys.GetRed());
    query.bindValue(1, keys.GetBlue());
    query.bindValue(2, keys.GetYellow());
    query.exec();
    query.clear();
}

QString DataBase::layer(int num) {
    QString str = " ";
    for (int i = 0; i < 14; i++)
        for (int j = 0; j < 14; j++) {
            if (map[j][i][num] < 10)
                str += "0";
            str += QString::number(map[j][i][num], kDecimal);
            str += " ";
        }
    return str;
}
