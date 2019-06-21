#include <player.h>
#include <deckfactory.h>
#include <card.h>

Player::Player(int life){
	this->life=life;

	this->hand = new std::vector<Card*>;
	this->field = new std::vector<std::optional<MonsterCard*>>(20);
	this->deck = new std::stack(DeckFactory::getNewDeck());
	
	//cada jogador comeca com 3 cartas na mao
	for(int i=0; i<=2; i++)
		this->drawCard();
}

void Player::changeLife(int delta){
	this->life+=delta;
}

int Player::getLife(){
	return this->life;
}

std::vector<Card*>* Player::getHand(){
	return this->hand;
}

std::vector<std::optional<MonsterCard*>>* Player::getField(){
	return this->field;
}

void Player::drawCard(){
	auto topCard = this->deck->top();
	this->hand->push_back(topCard);
	this->deck->pop();
}