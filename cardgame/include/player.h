#pragma once

#include <stack>
#include <vector>
#include <optional>

class Card;
class MonsterCard;

class Player{
private:
	int life;
	std::stack<Card*>* deck;
	std::vector<Card*>* hand;
	std::vector<std::optional<MonsterCard*>>* field;

public:
	Player(int life);	
	void changeLife(int delta);
	int getLife();
	std::vector<Card*>* getHand();
	std::vector<std::optional<MonsterCard*>>* getField();
	void drawCard();
};


