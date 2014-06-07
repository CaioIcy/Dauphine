#ifndef INCLUDE_HUD_H
#define INCLUDE_HUD_H

#include "Entity.h"
#include "Sprite.h"
#include "Player.h"

#include <vector>

/**
* The HUD entity class.
* Contains all the relevant implementation relative to the HUD.
*/
class PlayerHUD {

	public:

		/**
		* The constructor.
		* Creates the HUD by setting the position and sprite.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		* @param sprite_ : which sprite to use.
		*/
		PlayerHUD(Player* const player_);

		/**
		* The destructor.
		* Exits the current state and destroys all states.
		*/
		virtual ~PlayerHUD();

		/**
		* Updates the HUD.
		* @see Player::updateInput, Player::updatePosition
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		virtual void update();

		/**
		* Renders the HUD.
		* Uses the HUD's sprite render method.
		* @see Sprite::render
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_);

		void initializeSprites();

	private:
		Sprite* playerHudSprites[5];
		bool canRenderHud[5];
		Player* player;
};

#endif //INCLUDE_HUD_H