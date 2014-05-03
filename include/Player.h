#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "DynamicEntity.h"
#include "Sprite.h"
#include "InputKeys.h"
#include "StatePlayer.h"

#include <map>

class StatePlayer;

/**
* The player entity class.
* Contains all the relevant implementation relative to the player.
*/
class Player : public DynamicEntity {

	public:
		enum PStates : uint8_t {
			IDLE = 0,
			MOVING,
			AERIAL,
			ROLLING
		};

		/**
		* The constructor.
		* Creates the player by setting the position and sprite.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		* @param sprite_ : which sprite to use.
		*/
		Player(double x_, double y_, Sprite* sprite_);

		/**
		* The destructor.
		* Deletes the sprite.
		* @todo See if just the entity deleting the sprite is enough.
		*/
		virtual ~Player();

		/**
		* Updates the player.
		* @see Player::updateInput, Player::updatePosition
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		virtual void update(const double dt_);

		/**
		* Renders the player.
		* Uses the player's sprite render method.
		* @see Sprite::render
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_);

		/**
		* Loads all the states.
		* Every new state implemented should be initialized here.
		*/
		void initializeStates();

		/**
		* Deletes all the loaded states.
		* Every new state implemented should be deleted here.
		*/
		void destroyStates();

		/**
		* Sets the current game state.
		* @see StatePlayer::load
		* @see StatePlayer::unload
		* @param state_ : The state you want to be changed into. All states are inside Player.
		*/
		void changeState(PStates state_);

		Animation& getAnimation();

	private:
		Animation* animation;
		StatePlayer* currentState; /**< The current state, which the player is in. */
		std::map<PStates, StatePlayer*> statesMap; /**< Map containing all possible states. */
		
};

#endif //INCLUDE_PLAYER_H
