#ifndef INCLUDE_PSTATEATTACK_H
#define INCLUDE_PSTATEATTACK_H

#include "StatePlayer.h"

/**
* The state when the player is grounded and moving.
*
*/
class PStateAttack : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PStateAttack(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PStateAttack(){}

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

#endif // INCLUDE_PSTATEATTACK_H
