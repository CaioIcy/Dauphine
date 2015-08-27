#ifndef INCLUDE_PSTATEATTACKJUMPING_H
#define INCLUDE_PSTATEATTACKJUMPING_H

#include "StatePlayer.h"

/**
* The state when the player is idle.
*
*/
class PStateAttackJumping : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PStateAttackJumping(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PStateAttackJumping(){}

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

#endif // INCLUDE_PSTATEATTACKJUMPING_H
