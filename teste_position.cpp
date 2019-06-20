#include "doctest.h"
#include "position.h"

#define INDEX 2
#define SELF true

TEST_CASE("Teste 1 - Construtor")
{
	Position position = Position(true, 2)
	CHECK_EQ(position.isSelf(), true);
	CHECK_EQ(position.getIndex(), 3);
}

TEST_CASE("Teste 1 - Exceção - Construtor")
{
  CHECK_THROWS(Position(SELF, INDEX));
}