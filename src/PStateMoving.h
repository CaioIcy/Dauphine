#ifndef INCLUDE_PSTATEMOVING_H
#define INCLUDE_PSTATEMOVING_H

#include "StatePlayer.h"

/**
* The state when the player is grounded and moving.
*
*/
class PStateMoving : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PStateMoving(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PStateMoving(){}

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

#endif // INCLUDE_PSTATEMOVING_H
