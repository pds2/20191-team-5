#include <player.h>

Player::Player(int life){
	this->life=life;
	
	//cada jogador comeca com 3 cartas na mao
	for(int i=0; i<=2; i++)
		this->hand.push_back(this->deck.pop());
}

void Player::changeLife(int delta){
	this->life+=delta;
}

int Player::getLife(){
	return this->life;
}

std::vector<Card> Player::getHand(){
	return this->hand;
}

std::pair<std::optional<MonsterCard>, std::optional<MonsterCard>> Player::getField(){
	return this->field;
}

void Player::drawCard(){
	this->hand.push_back(this->deck.pop());
}