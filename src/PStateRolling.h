#ifndef INCLUDE_PSTATEROLLING_H
#define INCLUDE_PSTATEROLLING_H

#include "StatePlayer.h"

/**
* The state when the player is rolling.
*
*/
class PStateRolling : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PStateRolling(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PStateRolling(){}

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

#endif // INCLUDE_PSTATEROLLING_H
