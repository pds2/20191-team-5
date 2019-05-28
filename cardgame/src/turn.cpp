#include <turn.h>

Turn::Turn(int playerIndex){
	this->playerIndex = playerIndex;
}

Phase Turn::getPhase(){
	return this->phase;
}

void Turn::endPhase(){
	phase = static_cast<Phase>(static_cast<int>(phase) + 1);
	if (phase == End){
		phase = Draw;
		playerIndex = (playerIndex + 1) % 2;
	}
}

bool Turn::hasSummonedMonster(){
	return summonedMonster;
}

bool Turn::hasSummonedMagic(){
	return summonedMagic;
}

bool Turn::hasAttacked(int index){
	if (index == 0)
		return attacked.first;
	else
		return attacked.second;
}