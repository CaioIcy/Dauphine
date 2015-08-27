#ifndef INCLUDE_PSTATEHIT_H
#define INCLUDE_PSTATEHIT_H

#include "StatePlayer.h"

/**
* The state when the player is idle.
*
*/
class PStateHit : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PStateHit(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PStateHit(){}

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

#endif // INCLUDE_PSTATEHIT_H
