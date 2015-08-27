#ifndef INCLUDE_GSTATEOPTIONS_H
#define INCLUDE_GSTATEOPTIONS_H

#include "StateGame.h"
#include "Sprite.h"
#include "Text.h"

/**
* The state for the initial menu screen.
* Game state that will contain the game over screen.
*/
class GStateOptions : public StateGame {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		GStateOptions();

		/**
		* The destructor.
		*/
		virtual ~GStateOptions();

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
		* @see GStateOptions::load
		*/
		virtual void unload();

		/**
		* Renders the state.
		* Always renders on 0,0 position.
		* @see Sprite::render
		*/
		virtual void render();

	private:
		void applyOptions();

		double elapsedTime;

		enum Option : uint8_t {
			O_RESOLUTION = 0,
			O_VOLUME_MUSIC,
			O_VOLUME_SFX,
			O_APPLY,
			O_RETURN,
			O_TOTAL
		};

		enum Resolution : uint8_t {
			R_800_600 = 0,
			R_768_432,
			R_960_540,
			R_TOTAL
		};

		Sprite* optionsImage; /**< The image shown on the menu. */

		uint8_t currentResolution;
		uint8_t currentOption;

		Sprite* selector; /**< The selector shown on the menu. */
		int selectorXPositionLeft[Option::O_TOTAL]; /**< The X position of the left selector.. */
		int selectorYPositionLeft[Option::O_TOTAL]; /**< The Y position of the left selector.. */
		int selectorXPositionRight[Option::O_TOTAL]; /**< The X position of the left selector.. */
		int selectorYPositionRight[Option::O_TOTAL]; /**< The Y position of the left selector.. */

		static const std::string possibleResolutions[3];

		unsigned int musicVolume;
		unsigned int sfxVolume;

		Text* resolution;
		Text* volumeMusic;
		Text* volumeSFX;
};

#endif // INCLUDE_GSTATEOPTIONS_H
