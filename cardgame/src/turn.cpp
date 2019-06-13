#include <turn.h>

Turn::Turn(int playerIndex){
	this->playerIndex = playerIndex;
}

Phase Turn::getPhase(){
	return this->phase;
}

void Turn::endPhase(){
	phase = static_cast<Phase>(static_cast<int>(phase) + 1);
	if (phase == Phase::End){
		phase = Phase::Draw;
		playerIndex = (playerIndex + 1) % 2;
	}
}

int Turn::getPlayerIndex() {
	return playerIndex;
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