#ifndef INCLUDE_PSTATEIDLE_H
#define INCLUDE_PSTATEIDLE_H

#include "StatePlayer.h"

/**
* The state when the player is idle.
*
*/
class PStateIdle : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PStateIdle(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PStateIdle(){}

		/**
		* @see StatePlayer::enter
		*/
		virtual void enter();

		/**
		* @see StatePlayer::exit
		*/
		virtual void exit();

		/**
		* @see StatePlayer::handleInput
		*/
		virtual void handleInput(const std::array<bool, GameKeys::MAX> keyStates_);

};

#endif // INCLUDE_PSTATEIDLE_H
