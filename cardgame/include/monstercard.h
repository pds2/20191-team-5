#ifndef PDS2_MONSTERCARD_H
#define PDS2_MONSTERCARD_H

#include "card.h"

using namespace std;

class MonsterCard : public Card
{
private:
    int attack;
    int defense;
    Mode mode;
public:
    MonsterCard();
    MonsterCard(string _name, int _attack, int _defense);
    ~MonsterCard();

    Mode toggleMode();
    int getAttack();
    int getDefense();
    Mode getMode();

};

#endif /* PDS2_MonsterCard_H */