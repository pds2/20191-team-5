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
	* Returns the pahse the player is in the game
	*/
	Phase getPhase();

	/**
	* Returns the player's index of the run
	*/
	int getplayerIndex();

	/**
	* Returns the summoned monster card
	*/
	bool hasSummonedMonster();

	/**
	* Returns the summoned magic card
	*/
	bool hasSummonedMagic();

	/**
	* Returns the monster that attacked
	*/
	bool hasAttacked(int index);
};
