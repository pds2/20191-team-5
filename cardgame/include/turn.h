#pragma once
#include <phase.h>
#include <utility>

class Turn{
private:
	Phase phase;
	int playerIndex;
	bool summonedMonster;
	bool summonedMagic;
	std::pair <bool, bool> attacked;

public:
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
	int getPlayerIndex();

	/**
	* Returns true if the player has summoned a monster card
	*/
	bool hasSummonedMonster();

	/**
	 * Mark turn with summoned monster status
	 */
	void setSummonedMonster();

	/**
	* Returns true if the player has summoned a magic card
	*/
	bool hasSummonedMagic();

	/**
	 * Mark turn with summoned magic status
	 */
	void setSummonedMagic();

	/**
	* Returns true if the monster card has attacked
	* @param index monster index on field
	*/
	bool hasAttacked(int index);

	/**
	 * Mark turn monster with attacked status
	 * @param index monster index on field
	 */
	void setAttacked(int index);
};
