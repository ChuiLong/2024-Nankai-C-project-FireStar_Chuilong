#include "mainwindow.cpp"
#include "database.cpp"
#include "view.cpp"
#include "player.cpp"
#include "cheat.cpp"
#include "keys.h"
#include "tools.h"
#include "monster.h"
#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QTimer>
//全局变量
DataBase db;
Player player;
Monster monsters[13];
Tools tools;
Keys keys;
int map[14][14][10];//map数据
int mode = 1;
//主函数，总体内容
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //添加游戏的背景音乐
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sound/The music for the game.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);//循环播放
    QMediaPlayer *bgm = new QMediaPlayer();
    bgm->setPlaylist(playlist);bgm->play();// 传递数据库文件 前面函数用于显示路径 **匹配不同计算机的安装位置**
    db.Connect(a.applicationDirPath()  + "/data.sql");
    MainWindow w;
    w.show();
    //显示主窗口
    return a.exec();
    //执行程序直到游戏退出
}
