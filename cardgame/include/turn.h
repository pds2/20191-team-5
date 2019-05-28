#pragma once
#include <phase.h>
#include <utility>

class Turn{
public:
	Phase phase;
	int playerIndex;
	bool summonedMonster;
	bool summonedMagic;
	std::pair <bool, bool> attacked;

private:
	Turn (int playerIndex);
	void endPhase();
	Phase getPhase();
	int getplayerIndex();
	bool hasSummonedMonster();
	bool hasSummonedMagic();
	bool hasAttacked(int index);
};