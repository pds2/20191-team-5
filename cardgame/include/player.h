#pragma once

#include <card.h>
#include <monstercard.h>
#include <magiccard.h>
#include <stack>
#include <vector>
#include <utility>

class Player{
public:
	int life;
	std::stack<Card> deck;
	std::vector<Card> hand;
	std::pair<std::optional<MonsterCard>, std::optional<MonsterCard>> field;

private:
	Player(int life);	
	void changeLife(int delta);
	int getLife();
	std::vector<Card> getHand();
	std::pair<std::optional<MonsterCard>, std::optional<MonsterCard>> getField();
	void drawCard();
};


