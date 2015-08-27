#ifndef INCLUDE_PLAYERSTATE_H
#define INCLUDE_PLAYERSTATE_H

#include "Player.h"
#include "InputKeys.h"

#include <array>

class Player;

/**
* Parent class for other player states.
* 
*/
class StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		StatePlayer(Player* const player_);

		/**
		* The destructor.
		*/
		virtual ~StatePlayer();

		/**
		* Method called on load.
		* Pure virtual function. Called on state enter.
		*/
		virtual void enter() = 0;

		/**
		* Method called on unload.
		* Pure virtual function. Called on state exit.
		*/
		virtual void exit() = 0;

		/**
		* Update method for the state.
		* While the Player is on the state, this method runs every update.
		* @param keyStates_ : Boolean array that contains all input data.
		*/
		virtual void handleInput(const std::array<bool, GameKeys::MAX> keyStates_) = 0;

		Player* player; /**< Reference to the player. */
		SDL_Rect box;

};

#endif // INCLUDE_PLAYERSTATE_H