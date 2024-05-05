#include "mainwindow.h"
#include "database.h"
#include "player.h"
#include "tools.h"
#include "monster.h"
#include "keys.h"
#include "cheat.h"
#include <QTime>
#include <QtMath>
#include <QApplication>
#include <QDebug>
const int kPixlen = 32;
const int kOffsetX = 174;
const int kOffsetY = 224;
const int kDecimal = 10;
//规定各种颜色，方便应用
const QString kGreen = "#00EE00";
const QString kBlue = "#0000EE";
const QString kYellow = "#EEEE00";
const QString kPurple = "#8B008B";
const QString kRed = "#EE0000";
extern DataBase db;
extern Player player;
extern Keys keys;
extern Tools tools;
extern Monster monsters[13];
extern int map[14][14][10];
extern int mode;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    cheats = new Cheat();
    scene = new QGraphicsScene;
    view = new View(this);
    // 创建action
    CreateActions();

    // 创建menu
    CreateMenus();
    scene->setSceneRect(-400,-400,800,800);//可视区域

    view->setScene(scene);
    view->setMinimumSize(800,800);//最小尺寸
    view->setRenderHint(QPainter::Antialiasing);//渲染，使视图平滑
    view->show();

    // 创建mainwindow和view之间的连接
    connect(view, SIGNAL(quit()), this, SLOT(close()));
    connect(view, SIGNAL(change()), this, SLOT(slotDrawScene()));
    connect(view, SIGNAL(fight(int)), this, SLOT(slotFight(int)));
    connect(view, SIGNAL(events(QString)), this, SLOT(slotEvent(QString)));
    connect(view, SIGNAL(move(int, int)), this, SLOT(slotMovePlayerItem(int, int)));

    //设置中央部件和标题
    setCentralWidget(view);
    resize(1050,920);
    setWindowTitle(tr("Fight For Your Girl!"));

    // 欢迎界面
    Welcome();
}

//析构函数
MainWindow::~MainWindow() {
    delete scene;
    delete view;
    delete cheats;
}

void MainWindow::Welcome() {
    slotEvent("welcome");
//用于唤起“welcome”对应的函数
}

void MainWindow::CreateActions() {
    // tr用于翻译成对应语言的字符串，QAction用于显示菜单栏，这是用于作弊的内容
    clear = new QAction(tr("Clear"), this);
    newGame = new QAction(tr("NewGame"), this);
    saveGame = new QAction(tr("SaveGame"), this);
    loadGame = new QAction(tr("LoadGame"), this);
    exitGame = new QAction(tr("Quit"), this);
    cheatHp = new QAction(tr("HP+100"), this);
    cheatAttack = new QAction(tr("Attack+3"), this);
    cheatDefend = new QAction(tr("Defend+2"), this);
    cheatMoney = new QAction(tr("Money+50"), this);
    cheatLevel = new QAction(tr("Level+1"), this);
    cheatYellowKey = new QAction(tr("YellowKey+1"), this);
    cheatBlueKey = new QAction(tr("BlueKey+1"), this);
    cheatRedKey = new QAction(tr("RedKey+1"), this);
    cheatBook = new QAction(tr("Book"), this);
    cheatSword = new QAction(tr("Sword"), this);
    cheatShield = new QAction(tr("Shield"), this);
    cheatMode = new QAction(tr("GodMode"), this);

    newGame->setShortcut(tr("N"));
    saveGame->setShortcut(tr("S"));
    loadGame->setShortcut(tr("L"));
    exitGame->setShortcut(tr("Q"));
    //上述代码用于创造快捷键

    //将按钮按下与函数执行直接联系到一起
    connect(cheats, SIGNAL(change()), this, SLOT(slotDrawScene()));
    connect(newGame, SIGNAL(triggered()), this, SLOT(slotNewGame()));
    connect(saveGame, SIGNAL(triggered()), this, SLOT(slotSaveGame()));
    connect(loadGame, SIGNAL(triggered()), this, SLOT(slotLoadGame()));
    connect(exitGame, SIGNAL(triggered()), this, SLOT(close()));
    connect(cheatHp, SIGNAL(triggered()), cheats, SLOT(slotCheatHp()));
    connect(cheatAttack, SIGNAL(triggered()), cheats, SLOT(slotCheatAttack()));
    connect(cheatDefend, SIGNAL(triggered()), cheats, SLOT(slotCheatDefend()));
    connect(cheatMoney, SIGNAL(triggered()), cheats, SLOT(slotCheatMoney()));
    connect(cheatLevel, SIGNAL(triggered()), cheats, SLOT(slotCheatLevel()));
    connect(cheatYellowKey, SIGNAL(triggered()), cheats, SLOT(slotCheatYellowKey()));
    connect(cheatBlueKey, SIGNAL(triggered()), cheats, SLOT(slotCheatBlueKey()));
    connect(cheatRedKey, SIGNAL(triggered()), cheats, SLOT(slotCheatRedKey()));
    connect(cheatBook, SIGNAL(triggered()), cheats, SLOT(slotCheatBook()));
    connect(cheatSword, SIGNAL(triggered()), cheats, SLOT(slotCheatSword()));
    connect(cheatShield, SIGNAL(triggered()), cheats, SLOT(slotCheatShield()));
    connect(cheatMode, SIGNAL(triggered()), cheats, SLOT(slotCheatMode()));
    //结束
}
//创建menu
void MainWindow::CreateMenus() {
    //创建一个名为 "Menu" 的菜单，并将其添加到主窗口的菜单栏上。
    QMenu *fileMenu = menuBar()->addMenu(tr(" Menu "));
    fileMenu->addAction(newGame);
    fileMenu->addAction(saveGame);
    fileMenu->addAction(loadGame);
    fileMenu->addSeparator();   //分割线
    fileMenu->addAction(exitGame);
//创建一个名为 "Cheat!" 的菜单，并将其添加到主窗口的菜单栏上。
    QMenu *cheatMenu = menuBar()->addMenu(tr(" Cheat! "));
    cheatMenu->addAction(cheatHp);
    cheatMenu->addAction(cheatAttack);
    cheatMenu->addAction(cheatDefend);
    cheatMenu->addAction(cheatMoney);
    cheatMenu->addAction(cheatLevel);
    cheatMenu->addSeparator();
    cheatMenu->addAction(cheatYellowKey);
    cheatMenu->addAction(cheatBlueKey);
    cheatMenu->addAction(cheatRedKey);
    cheatMenu->addSeparator();
    cheatMenu->addAction(cheatBook);
    cheatMenu->addAction(cheatSword);
    cheatMenu->addAction(cheatShield);
    cheatMenu->addSeparator();
    cheatMenu->addAction(cheatMode);
    //下属菜单
}

void MainWindow::CreateInform() {
    AddPictureItem(-102, 0, "sidebg");
    AddPictureItem(-97, 30, "side");
    AddPictureItem(-85, 5, "info1");
    AddPictureItem(-65, 60, "sex"+QString::number(player.GetSex(), kDecimal));
    AddPictureItem(-82, 130, "info2");
    AddPictureItem(-83, 145, "info3");
    AddPictureItem(-83, 230, "info4");
    //把图片加入到对应的位置上去
    AddTextItem(-50, 5, QString::number(player.GetFloor()+1, kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-65, 100, "Lv "+QString::number(player.GetLevel() +1, kDecimal), 10, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-43, 126, QString::number(player.GetHp(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-43, 142, QString::number(player.GetAttack(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-43, 158, QString::number(player.GetDefend(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-43, 174, QString::number(player.GetMoney(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-43, 190, QString::number(player.GetNeed() - player.GetExp(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-40, 240, QString::number(keys.GetYellow(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-40, 265, QString::number(keys.GetBlue(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    AddTextItem(-40, 290, QString::number(keys.GetRed(), kDecimal), 8, QColor(qrand()%256,qrand()%256,qrand()%256));
    //生成文本项
    if (mode == -1)
        AddTextItem(-90, 30, "God Mode!!!", 12, kRed);
    if (tools.GetBook())
        AddPictureItem(-63, 323, "book");
    if (tools.GetSword())
        AddPictureItem(-60, 367, "sword");
    if (tools.GetShield())
        AddPictureItem(-60, 405, "shield");
    //如果 mode 变量的值等于 -1，即处于上帝模式，那么会在位置 (-90, 30) 添加一个文本项，文本内容是 "God Mode!!!"，字体大小为 12，并且文本的颜色是 kRed，即红色。
    //如果角色拥有书籍（tools.GetBook() 返回真），则在位置 (-63, 323) 添加一张名为 "book" 的图片。
    //如果角色拥有剑（tools.GetSword() 返回真），则在位置 (-60, 367) 添加一张名为 "sword" 的图片。
    //如果角色拥有盾牌（tools.GetShield() 返回真），则在位置 (-60, 405) 添加一张名为 "shield" 的图片。
}

void MainWindow::slotDrawScene() {          // 绘制主界面
    if (view->GetStatus() != "main") return;
    Clear();
    CreateInform();
    AddPictureItem(0, 0, "tile");
    for (int i = 0; i < 14; i++)
        for (int j = 0; j < 14; j++)
            AddMapItem(i, j, map[i][j][player.GetFloor()]);
    AddPlayerItem(player.GetPosx(), player.GetPosy(), player.GetToward(), player.GetSex());
}

void MainWindow::slotShop() {               // 绘制shop界面
    Clear();
    AddPictureItem(0, 0, "shop");
    CreateInform();
}

void MainWindow::slotBook() {               // 绘制book
    Clear();
    int exist[30];
    for (int i = 0; i < 30; i++)
        exist[i] = 0;
    for (int i = 0; i < 14; i++)
        for (int j = 0; j < 14; j++)
            if (map[i][j][player.GetFloor()] > 10 && map[i][j][player.GetFloor()] < 24)
                exist[map[i][j][player.GetFloor()]] = 1;
    AddPictureItem(-102, 0, "background");
    int tmp = 0;
    for (int i = 11; i < 24; i++)           //写出怪物的信息
        if (exist[i]) {
            tmp++;
            AddPictureItem(-80, -26 + tmp*40, QString::number(i, kDecimal));
            AddTextItem(-35, -28 + tmp*40, "Hp:", 8, kGreen);
            AddTextItem(63, -28 + tmp*40, "Attack:", 8, kGreen);
            AddTextItem(183, -28 + tmp*40, "Defend:", 8, kGreen);
            AddTextItem(196, -12 + tmp*40, "Miss:", 8, kPurple);
            AddTextItem(343, -12 + tmp*40, "Crit:", 8, kPurple);
            AddTextItem(-40, -12 + tmp*40, "Exp:", 8, kBlue);
            AddTextItem(62, -12 + tmp*40, "Money:", 8, kBlue);
            AddTextItem(280, -28 + tmp*40, "Expected damage:", 8,  kYellow);

            AddTextItem(-5, -28 + tmp*40, QString::number(monsters[i-11].GetHp(), kDecimal), 8, kGreen);
            AddTextItem(110, -28 + tmp*40, QString::number(monsters[i-11].GetAttack(), kDecimal), 8, kGreen);
            AddTextItem(240, -28 + tmp*40, QString::number(monsters[i-11].GetDefend(), kDecimal), 8, kGreen);
            AddTextItem(240, -12 + tmp*40, QString::number(monsters[i-11].GetMiss(), kDecimal)+"%", 8, kPurple);
            AddTextItem(380, -12 + tmp*40, QString::number(100 - monsters[i-11].GetCrit(), kDecimal)+"%", 8, kPurple);
            AddTextItem(-5, -12 + tmp*40, QString::number(monsters[i-11].GetExp(), kDecimal), 8, kBlue);
            AddTextItem(110, -12 + tmp*40, QString::number(monsters[i-11].GetMoney(), kDecimal), 8, kBlue);
            AddTextItem(380, -28 + tmp*40, GetExpectedDamage(i-11), 8, kYellow);
        }
}
//根据传入的str字符串判断执行哪个函数
void MainWindow::slotEvent(QString str) {
    if (str == "new") slotNewGame();

    else if (str == "boy") player.ChooseSex(1);
    else if (str == "girl") player.ChooseSex(0);

    else if (str == "save") slotSaveGame();
    else if (str == "load") slotLoadGame();
    else if (str == "book") slotBook();
    else if (str == "shop") slotShop();
    else if (str == "quit") close();

    else {
        Clear();
        AddPictureItem(-102, 0, "background");
        if (str == "ending")                // 结局的确定
            str += QString::number(player.GetSex(), kDecimal);
        AddPictureItem(-102, 0, str);
    }
}

void MainWindow::CreateFight(int num) {     // 绘制战斗有关的场景和框架
    if (player.GetFloor() == 5)
        AddPictureItem(-102, 0, "firebg");
    else if (player.GetFloor() == 6)
        AddPictureItem(-102, 0, "icebg");
    else if (player.GetFloor() == 9)
        AddPictureItem(-102, 0, "highbg");
    else
        AddPictureItem(-102, 0, "lowbg");
    AddPictureItem(40, 50, "fight1");
    AddPictureItem(152, 67, "vs");
    if (tools.GetSword())
        AddPictureItem(53, 70, "sword");
    if (tools.GetShield())
        AddPictureItem(123, 70, "shield");
    AddPictureItem(85, 65, "sex" + QString::number(player.GetSex(), kDecimal));
    AddPictureItem(231, 65, QString::number(num, kDecimal));
    AddPictureItem(40, 140, "fight2");
    AddPictureItem(40, 256, "fight3");
}

void MainWindow::slotFight(int num) {       // 模拟战斗并生成具体的战斗结果
    Clear();
    CreateFight(num);

    int random, damage, time = 0;
    int playerHp, monsterHp;
    int playerMiss = 0, monsterMiss = 0;
    int playerCrit = 0, monsterCrit = 0;
    QString str1, str2;
    QTime t = QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    num -= 11;

    monsterHp = monsters[num].GetHp();
    playerHp = player.GetHp();
    str1 = QString::number(playerHp, kDecimal) + "   ->   ";
    str2 = QString::number(monsterHp, kDecimal) + "   ->   ";

    // 轮流攻击
    while (1) {
        random = qrand() % 99 + 1;
        damage = qMax(player.GetAttack() - monsters[num].GetDefend(), 1);
        damage += qFloor(damage*0.5*(random >= player.GetCrit()));    // Check if Crit or not
        monsterHp -= damage * (random > monsters[num].GetMiss());     // Check if Miss or not
        if (random <= monsters[num].GetMiss())
            playerMiss++;
        if (random >= player.GetCrit())
            monsterCrit++;
        if (monsterHp <= 0) {
            monsterHp = 0;
            break;
        }
        random = qrand() % 99 + 1;
        damage = qMax(monsters[num].GetAttack() - player.GetDefend(), 1);
        damage += qFloor(damage*0.5*(random >= monsters[num].GetCrit()));    // Check if Crit or not
        playerHp -= mode * damage * (random > player.GetMiss());             // Check if Miss or not, also check cheat mode
        if (random <= player.GetMiss())
            monsterMiss++;
        if (random >= monsters[num].GetCrit())
            playerCrit++;
        if (playerHp <= 0) {
            playerHp = 0;
            break;
        }
        time++;
    }

    //战斗结果
    str1 += QString::number(playerHp, kDecimal);
    str2 += QString::number(monsterHp, kDecimal);
    AddTextItem(60, 155, str1, 12, "WHITE");
    AddTextItem(205, 155, str2, 12, "WHITE");
    AddTextItem(75, 171, "Crit : " + QString::number(playerCrit, kDecimal), 12, kRed);
    AddTextItem(215, 171, "Crit : " + QString::number(monsterCrit, kDecimal), 12, kRed);
    AddTextItem(75, 188, "Miss : " + QString::number(playerMiss, kDecimal), 12, kGreen);
    AddTextItem(215, 188, "Miss : " + QString::number(monsterMiss, kDecimal), 12, kGreen);
    AddTextItem(75, 265, "Money + " + QString::number(monsters[num].GetMoney(), kDecimal), 12, kYellow);
    AddTextItem(210, 265, "Exp + " + QString::number(monsters[num].GetExp(), kDecimal), 12, kYellow);

    //收益
    player.SetCoin(player.GetMoney() + monsters[num].GetMoney());
    player.SetExp(player.GetExp() + monsters[num].GetExp());
    player.SetHp(playerHp);

    // 没死的话 判断是否需要升级
    if (player.GetExp() >= player.GetNeed() && player.GetHp() > 0) {
        player.SetExp(player.GetExp() - player.GetNeed());
        player.LevelUp();
        AddPictureItem(65, 355, "levelup");
    }
}

void MainWindow::Clear() {              // 清空场景：通过不断迭代并移除列表中的第一个元素，直到列表为空，这段代码确保了场景中的所有图形项都被移除。
    QList<QGraphicsItem*> listItem = scene->items();
    while(!listItem.empty()) {
        scene->removeItem(listItem.at(0));
        listItem.removeAt(0);
    }
}

void MainWindow::slotNewGame() {        // 开始一个新游戏
    Clear();

    // Load initial data
    db.LoadMap(0);
    db.LoadTools(0);
    db.LoadKeys(0);
    db.LoadMonsters();

    // 选择角色
    view->SetStatus("select");
    slotEvent("select");
}

void MainWindow::slotSaveGame() {           // 保存数据
    db.SaveMap(1);
    db.SaveTools(1);
    db.SaveKeys(1);
    db.SavePlayer();
}

void MainWindow::slotLoadGame() {           // 加载数据
    db.LoadMap(1);
    db.LoadTools(1);
    db.LoadKeys(1);
    db.LoadPlayer();
    db.LoadMonsters();
    view->SetStatus("main");
    slotDrawScene();
}

void MainWindow::slotMovePlayerItem(int x, int y) {             // 移动玩家的位置
    if (playerItem->zValue() == 0) {
        playerItem->moveBy(x*kPixlen, y*kPixlen);
        player.SetPosx(player.GetPosx() + x);
        player.SetPosy(player.GetPosy() + y);
        map[player.GetPosx()][player.GetPosy()][player.GetFloor()] = 0;
    }
}

void MainWindow::AddMapItem(int x, int y, int num) {            // 加入地图的元素
    QGraphicsPixmapItem *item = scene->addPixmap(QPixmap(":/images/" + QString::number(num, kDecimal)));
    //item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setPos(x*kPixlen-kOffsetX,y*kPixlen-kOffsetY);
}

void MainWindow::AddPictureItem(int x, int y, QString str) {           // 加入一张图片
    QGraphicsPixmapItem *item = scene->addPixmap(QPixmap(":/images/" + str));
    //item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setPos(x-kOffsetX,y-kOffsetY);
}

void MainWindow::AddPlayerItem(int x, int y, int toward, int sex) {         // 加入一个玩家
    QString str = ":/images/1" + QString::number(sex, kDecimal) + QString::number(toward, kDecimal);
    playerItem = scene->addPixmap(QPixmap(str));
    playerItem->setPos(x*kPixlen-kOffsetX, y*kPixlen-kOffsetY);
}

void MainWindow::AddTextItem(int x, int y, QString str, int size, QColor color) {           // 加入文本元素
    QFont font("Times", size);
    QGraphicsTextItem *item = new QGraphicsTextItem(str);
    item->setFont(font);
    item->setDefaultTextColor(color);
    scene->addItem(item);
    item->setPos(x-kOffsetX,y-kOffsetY);
}
QString MainWindow::GetExpectedDamage(int num) {            // 收到伤害数值
    int ans;
    int damage1 = player.GetAttack() - monsters[num].GetDefend();
    int damage2 = monsters[num].GetAttack() - player.GetDefend();
    if (damage1 < 1)
        damage1 = 1;
    if (damage2 < 1)
        damage2 = 1;
    if (monsters[num].GetHp()%damage1 == 0)
        ans = (monsters[num].GetHp()/damage1 - 1)*damage2;
    else
        ans = (monsters[num].GetHp()/damage1)*damage2;
    return QString::number(ans, kDecimal);
}
