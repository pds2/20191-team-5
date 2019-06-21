#include "doctest.h"
#include "magiccard.h"

#define NAME "CARTA"
#define DESCRIPTION "DESC"
#define ATTACK 300
#define DEFENSE 300
#define LIFE 2000
#define DESTROY true

TEST_CASE("Teste 1 - MagicCard")
{
	MagidCard card = MagicCard(NAME, DESCRIPTION, ATACK, DEFENSE, LIFE, DESTROY);
	CHECK_EQ(card.isSummonable(), false);
	CHECK_EQ(card.getDescription(), DESC);
}
