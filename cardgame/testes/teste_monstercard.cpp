#include "doctest.h"
#include "monstercard.h"

#define ATACK 300
#define DEFENSE 300
#define MODE 1
TEST_CASE("Teste 1 -  Construtror MonsterCard")
{
	MonsterCard monstro = MonsterCard(ATACK, DEFENSE, MODE);
    CHECK_EQ(monstro.getAttack(), ATTACK);
    CHECK_EQ(monstro.getDefense(), DEFENSE);
    CHECK_EQ(monstro.getMode(), MODE);
}

TEST_CASE("Teste 1 - Exceção - Consrutor MonsterCard")
{
    CHECK_THROWS(MonsterCard(400, 400, 2));
    CHECK_THROWS(MonsterCard(300, 300, 1));
}