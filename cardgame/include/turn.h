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
	/**
	* Points to the turn player
	*/
	Turn (int playerIndex);

	/**
	* Change of phase and if the last turn changes the turn
	*/
	void endPhase();

	/**
	* Returns the phase the player is in the game
	*/
	Phase getPhase();

	/**
	* Returns the player's index of the run
	*/
	int getplayerIndex();

	/**
	* Returns true if the player has summoned a monster card
	*/
	bool hasSummonedMonster();

	/**
	* Returns true if the player has summoned a magic card
	*/
	bool hasSummonedMagic();

	/**
	* Returns true if the monster card has attacked
	*/
	bool hasAttacked(int index);
};
