#pragma once

#include <utility>

#include <player.h>
#include <position.h>
#include <turn.h>

class Game {
	private:
		std::pair<Player, Player> players;
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
		void toggleMode(Position& position);

		/**
		 * Summon a monster card on the field.
		 * @param cardIndex card index on the player's hand
		 */
		void summon(int cardIndex, std::optional<Position&>);

		/**
		 * Attack the opponent.
		 * @param monster the attacker
		 * @param target target position of the attack
		 */
		void attack(Position& monster, std::optional<Position&> target);

		/**
		 * Advance to the next phase.
		 */
		void endPhase();

		/**
		 * Returns the players.
		 */
		std::pair<Player, Player> getPlayers();

		/**
		 * Returns the current turn.
		 */
		Turn getTurn();
};