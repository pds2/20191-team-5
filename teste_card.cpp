#include "doctest.h"
#include "card.h"

#define NAME "CARTA"


TEST_CASE("Teste 1 - Construtor das cartas")
{
	Card card = Card("CARTA1");
	CHECK_EQ(card.getName(), NAME);
}

TEST_CASE("Teste 1 -  Construtor de cartas ")
{
    CHECK_THROWS(Card("CARTA");
}