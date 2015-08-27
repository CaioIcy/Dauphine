#ifndef INCLUDE_PSTATEDEAD_H
#define INCLUDE_PSTATEDEAD_H

#include "StatePlayer.h"

/**
* The state when the player is idle.
*
*/
class PStateDead : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PStateDead(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PStateDead(){}

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

#endif // INCLUDE_PSTATEDEAD_H
