#ifndef INCLUDE_PSTATEAIMING_H
#define INCLUDE_PSTATEAIMING_H

#include "StatePlayer.h"

/**
* The state when the player is idle.
*
*/
class PStateAiming : public StatePlayer {

	public:
		/**
		* The constructor.
		* @param player_ : Reference to the player.
		*/
		PStateAiming(Player* const player_);
		
		/**
		* The destructor.
		*/
		virtual ~PStateAiming(){}

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

	private:
		/**
		*/
		int absoluteCrosshairPlayerDistance();

};

#endif // INCLUDE_PSTATEAIMINGs_H
