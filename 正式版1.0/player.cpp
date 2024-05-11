#include "player.h"
#include <QtMath>

void Player::ChooseKind(int kind) {
    if (kind == 1) {
        SetHp(150);
        SetHarm(14);
        SetMiss(8);
        SetCrit(93);
    } else {
        SetHp(250);
        SetHarm(13);
        SetMiss(18);
        SetCrit(99);
    }
    SetDefend(10);
    SetCoin(10);
    SetExp(0);
    this->level = 0;
    this->posx = 6;
    this->posy = 12;
    this->floor = 0;
    this->toward = 3;
    this->kind = kind;
    this->need = 5;
}//初始数值

void Player::LevelUp() {
    level += 1;
    SetHp(GetHp() + 10);
    SetHarm(GetAttack() + 1);
    SetDefend(GetDefend() + 1);
    need = qFloor(need*1.5) + 1;
}//升级后的函数

