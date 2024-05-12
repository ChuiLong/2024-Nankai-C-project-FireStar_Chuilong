//实现作弊功能
#include "cheat.h"
#include "player.h"
#include "keys.h"
#include "tools.h"
#include <QtMath>

extern Player player;
extern Tools tools;
extern Keys keys;
extern int mode;


void Cheat::slotCheatAttack() {
    player.SetHarm(player.GetAttack()+10);
    emit change();//发送信号，下同
}

void Cheat::slotCheatHp() {
    player.SetHp(player.GetHp() + 100);
    emit change();
}

void Cheat::slotCheatDefend() {
    player.SetDefend(player.GetDefend() + 10);
    emit change();
}

void Cheat::slotCheatCoin() {
    player.SetCoin(player.GetMoney() + 50);
    emit change();
}

void Cheat::slotCheatLevel() {
    player.LevelUp();
    emit change();
}
void Cheat::slotCheatRedKey() {
    keys.SetRed(keys.GetRed() + 1);
    emit change();
}
void Cheat::slotCheatBlueKey() {
    keys.SetBlue(keys.GetBlue() + 1);
    emit change();
}
void Cheat::slotCheatYellowKey() {
    keys.SetYellow(keys.GetYellow() + 1);
    emit change();
}
void Cheat::slotCheatBook() {
    tools.SetBook(1 - tools.GetBook());
    emit change();
}
void Cheat::slotCheatSword() {
    tools.SetSword(1 - tools.GetSword());
    if (tools.GetSword())
        player.SetHarm(player.GetAttack() + 10);
    else
        player.SetHarm(player.GetAttack() - 10);
    emit change();
}
void Cheat::slotCheatShield() {
    tools.SetShield(1 - tools.GetShield());
    if (tools.GetShield())
        player.SetDefend(player.GetDefend() + 8);
    else
        player.SetDefend(player.GetDefend() - 8);
    emit change();
}
void Cheat::slotCheatMode() {
    mode = -mode;
    emit change();
}

