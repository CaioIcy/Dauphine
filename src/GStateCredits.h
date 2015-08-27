#ifndef INCLUDE_GSTATECREDITS_H
#define INCLUDE_GSTATECREDITS_H

#include "StateGame.h"
#include "Sprite.h"

/**
* The state for the initial menu screen.
* Game state that will contain the game over screen.
*/
class GStateCredits : public StateGame {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		GStateCredits();

		/**
		* The destructor.
		*/
		virtual ~GStateCredits();

		/**
		* Loads the level.
		* From the menu.lua script, loads all the necessary objects.
		*/
		virtual void load();

		/**
		* Updates the objects within the StateGame.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double dt_);

		/**
		* Unloads everything that was loaded.
		* @see GStateCredits::load
		*/
		virtual void unload();

		/**
		* Renders the state.
		* Always renders on 0,0 position.
		* @see Sprite::render
		*/
		virtual void render();

	private:
		Sprite* creditsImage; /**< The image shown on the credits. */
		const int creditsHeightSize;
		const int creditsChangeSpeed;
		SDL_Rect creditsClip; /**< The clip shown on the credits. */
		
};

#endif // INCLUDE_GSTATECREDITS_H
