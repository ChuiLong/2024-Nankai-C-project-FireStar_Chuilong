#ifndef CHEAT_H
#define CHEAT_H
#include <QObject>

class Cheat : public QObject {
    Q_OBJECT
public:
    Cheat() {}
    ~Cheat() {}
signals:
    void change();//这个函数不需要具体的实现 用于在作弊按钮被点击后 进行信号的传输与通知
public slots:
    void slotCheatHp();
    void slotCheatAttack();
    void slotCheatDefend();
    void slotCheatCoin();
    void slotCheatLevel();
    void slotCheatRedKey();
    void slotCheatBlueKey();
    void slotCheatYellowKey();
    void slotCheatBook();
    void slotCheatSword();
    void slotCheatShield();
    void slotCheatMode();
};

#endif
