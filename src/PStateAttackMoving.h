#ifndef INCLUDE_PSTATEATTACKMOVING_H
#define INCLUDE_PSTATEATTACKMOVING_H

#include "StatePlayer.h"

/**
* The state when the player is idle.
*
*/
class PStateAttackMoving : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PStateAttackMoving(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PStateAttackMoving(){}

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

#endif // INCLUDE_PSTATEATTACKMOVING_H
