#include "doctest.h"
#include "player.h"

#define LIFE 2000

TEST_CASE("Teste 1 - Construtor ")
{
	Player player = Player(2000);
    CHECK_EQ(player.getLife(), 2000);
}

TEST_CASE("Teste 1 - Exceção - Construtor")
{
    CHECK_THROWS(Player(1000);

}