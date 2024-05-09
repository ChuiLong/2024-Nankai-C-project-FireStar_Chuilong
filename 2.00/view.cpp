#include "view.h"
#include "player.h"
#include "keys.h"
#include "tools.h"
#include <QKeyEvent>

extern Player player;
extern Tools tools;
extern Keys keys;
extern int map[14][14][10];

View::View(QWidget *parent) : QGraphicsView(parent) {         // 构造函数，初始化欢迎页面
    status = "welcome";
    next_step = 0;
}

View::~View() {         // 析构函数
    status = "";
    next_step = 0;
}

void View::keyPressEvent(QKeyEvent * event) {         // 选择目前键盘活动状态
    if (status == "main") {
        keyMain(event);
        action();
    } else if (status == "tip" || status == "book" || status == "help") {
        SetStatus("main");
        emit change();
    } else if (status == "ending" || status == "fail")
        emit quit();
    else if (status == "fight")
        keyFight();
    else if (status == "shop")
        keyShop(event);
    else if (status == "welcome")
        keyWelcome(event);
    else if (status == "select")
        keySelect(event);
}

void View::keyMain(QKeyEvent * event) {
    switch (event->key()) {
        case Qt::Key_Up:
            if (access(player.GetPosx(), player.GetPosy()-1))
                emit move(0, -1);
            player.SetToward(1);
            break;
        case Qt::Key_Down:
            if (access(player.GetPosx(), player.GetPosy()+1))
                emit move(0, +1);
            player.SetToward(3);
            break;
        case Qt::Key_Left:
            if (access(player.GetPosx()-1, player.GetPosy()))
                emit move(-1, 0);
            player.SetToward(2);
            break;
        case Qt::Key_Right:
            if (access(player.GetPosx()+1, player.GetPosy()))
                emit move(+1, 0);
            player.SetToward(4);
            break;
        case Qt::Key_B:
            if (tools.GetBook()) {
                SetStatus("book");
                emit events("book");
            }
            break;
        case Qt::Key_S:
            emit events("save");
            break;
        case Qt::Key_L:
            emit events("load");
            break;
        case Qt::Key_Q:
            emit events("quit");
            break;
        case Qt::Key_H:
            SetStatus("help");
            emit events("help");
            break;
        default:
            break;
    }
}

void View::keyShop(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_1:
            if (player.GetMoney() >= 50) {
                player.SetCoin(player.GetMoney() - 50);
                player.SetHp(player.GetHp()+30);
            }
            emit events("shop");
            break;
        case Qt::Key_2:
            if (player.GetMoney() >= 50) {
                player.SetCoin(player.GetMoney() - 50);
                player.SetHarm(player.GetAttack()+2);
            }
            emit events("shop");
            break;
        case Qt::Key_3:
            if (player.GetMoney() >= 50) {
                player.SetCoin(player.GetMoney() - 50);
                player.SetDefend(player.GetDefend()+1);
            }
            emit events("shop");
            break;
        case Qt::Key_4:
            if (player.GetMoney() >= 40) {
                player.SetCoin(player.GetMoney() - 40);
                keys.SetYellow(keys.GetYellow()+1);
            }
            emit events("shop");
            break;
        case Qt::Key_5:
            if (player.GetMoney() >= 120) {
                player.SetCoin(player.GetMoney() - 120);
                keys.SetBlue(keys.GetBlue()+1);
            }
            emit events("shop");
            break;
        case Qt::Key_6:
            if (player.GetMoney() > 300) {
                player.SetCoin(player.GetMoney() - 300);
                keys.SetRed(keys.GetRed()+1);
            }
            emit events("shop");
            break;
        case Qt::Key_P:
            SetStatus("main");
            emit change();
            break;
        default:
            break;
    }
}

void View::keyWelcome(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_1:
            emit events("new");
            break;
        case Qt::Key_2:
            SetStatus("main");
            emit events("load");
            emit change();
            break;
        case Qt::Key_3:
            emit events("quit");
            emit change();
            break;
        default:
            break;
    }
}

void View::keySelect(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_1:
            SetStatus("main");
            emit events("boy");
            emit change();
            break;
        case Qt::Key_2:
            SetStatus("main");
            emit events("girl");
            emit change();
            break;
        case Qt::Key_3:
            emit events("quit");
            break;
        default:
            break;
    }
}

void View::keyFight() {
    if (player.GetHp() == 0) {
        SetStatus("fail");
        emit events("fail");
    } else {
        SetStatus("main");
        emit change();
    }
}

void View::action() {//根据不同的信号触发不同的函数
    switch (next_step) {
        case 3:
            keys.SetYellow(qMax(keys.GetYellow()-1, 0));
            break;
        case 4:
            keys.SetBlue(qMax(keys.GetBlue()-1, 0));
            break;
        case 5:
            keys.SetRed(qMax(keys.GetRed()-1, 0));
            break;
        case 6:
            keys.SetYellow(keys.GetYellow()+1);
            break;
        case 7:
            keys.SetBlue(keys.GetBlue()+1);
            break;
        case 8:
            keys.SetRed(keys.GetRed()+1);
            break;
        case 10:
            SetStatus("tip");
            emit events("tip1");
            break;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
            SetStatus("fight");
            emit fight(next_step);
            break;
        case 24:

            player.SetHp(player.GetHp()/3);
            break;
        case 25:

            player.SetDefend(player.GetDefend()/3);
            break;
        case 26:

            player.SetHarm(player.GetAttack()/3);
            break;
        case 27:

            SetStatus("tip");
            emit events("tip2");
            break;
        case 28:
            player.SetCoin(player.GetMoney()+15);
            break;
        case 29:
            player.SetHp(player.GetHp()+18);
            break;
        case 30:
            player.SetHp(player.GetHp()+30);
            break;
        case 31:
            tools.SetSword(1);
            player.SetHarm(player.GetAttack()+10);
            break;
        case 32:
            player.SetHarm(player.GetAttack()+3);
            break;
        case 33:
            tools.SetShield(1);
            player.SetDefend(player.GetDefend()+8);
            break;
        case 34:
            player.SetDefend(player.GetDefend()+2);
            break;
        case 35:
            tools.SetBook(1);
            break;
        case 51:

            SetStatus("shop");
            emit events("shop");
            break;
        case 80:

            player.SetPart(player.GetFloor()+1);
            break;
        case 90:
            player.SetPart(player.GetFloor()-1);
            break;
        case 99:
            SetStatus("ending");
            emit events("ending");
            break;
    }
    if (status == "main")
        emit change();
}

int View::access(int x, int y) {          // 改变next_step值
    int tmp = map[x][y][player.GetFloor()];
    next_step = tmp;
    if (tmp == 0 || (tmp > 5 && tmp < 10) || (tmp > 10 && tmp < 27) || (tmp > 27 && tmp < 35) || tmp == 59 ||
        (tmp == 3 && keys.GetYellow() > 0) || (tmp == 4 && keys.GetBlue() > 0) || (tmp == 5 && keys.GetRed() > 0)) {
        map[x][y][player.GetFloor()] = 0;
        return 1;
    } else
        return 0;
}

