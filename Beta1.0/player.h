//用于配合player.cpp使用的头文件 定义了一些变量
#ifndef PLAYER_H
#define PLAYER_H

#include "role.h"
#include <QString>

class Player : public Role {
public:
    Player() {}
    ~Player() {}
    int GetLevel() { return level; }
    int GetPosx() { return posx; }
    int GetPosy() { return posy; }
    int GetFloor() {return floor; }
    int GetToward() {return toward; }
    int GetSex() {return kind; }
    int GetNeed() {return need; }

    void SetLevel(int level) { this->level = level; }
    void SetPosx(int posx) { this->posx = posx; }
    void SetPosy(int posy) { this->posy = posy; }
    void SetPart(int floor) { this->floor = floor; }
    void SetToward(int toward) { this->toward = toward; }
    void SetSex(int sex) { this->kind = sex; }
    void SetNeed(int need) { this->need = need; }
    void ChooseSex(int);
    void LevelUp();

private:
    int level;
    int posx;
    int posy;
    int floor;
    int toward;
    int kind;
    int need;
};

#endif
