#pragma once

#include <vector>
#include <utility>

#include <player.h>
#include <position.h>
#include <turn.h>

class Game {
	private:
		std::vector<Player*> players;
		Turn turn;
	public:
		/**
		 * Game constructor
		 */
		Game();

		/**
		 * Draw card for the current player.
		 */
		void draw();

		/**
		 * Change a monster card mode.
		 * @param position the card position on the board
		 */
		void toggleMode(Position* position);

		/**
		 * Summon or apply a card.
		 * @param cardIndex card index on the player's hand
		 * @param target position the card will summoned or applied
		 */
		void summon(int cardIndex, std::optional<Position*> target);

		/**
		 * Attack the opponent.
		 * @param monster the attacker
		 * @param target target position of the attack
		 */
		void attack(Position* monster, std::optional<Position*> target);

		/**
		 * Advance to the next phase.
		 */
		void endPhase();

		/**
		 * Returns the players.
		 */
		std::vector<Player*> getPlayers();

		/**
		 * Returns the current turn.
		 */
		Turn getTurn();
};