#ifndef INCLUDE_ANIMATION_H
#define INCLUDE_ANIMATION_H

#include "SDLWrapper.h"

/**
* Class in control of animating a sprite.
*/
class Animation{

	public:
		/**
		* The constructor.
		* Initializes all attributes.
		* @param x_ : The x position on the spritesheet.
		* @param y_ : The y position on the spritesheet.
		* @param spriteWidth_ : The width of the sprite to animate.
		* @param spriteHeight_ : The height of the sprite to animate.
		* @param numberOfImages_ : The number of images to animate inside the spritesheet.
		* @param loop_ : Whether to loop or not.
		*/
		Animation(const int x_, const int y_, const int spriteWidth_, const int spriteHeight_,
			const unsigned int numberOfImages_, const bool loop_);

		/**
		* The destructor.
		*/
		~Animation();

		/**
		* Updates the animation clip.
		* @param clip_ : Reference to the clip of whatever object the animation is a part of.
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		* @param totalTime_ : How much time each frame should have. Affects the speed on which
		* 	the animation changes.
		*/
		void update(SDL_Rect& clip_, const double dt_);

		int getCurrentFrame();

		void changeWidthHeight(int width_, int height_);
		
		/**
		* Changes the animation to another.
		* @note See Animation::Animation for the parameters descriptions.
		*/
		void changeAnimation(const int x_, const int y_, const unsigned int numberOfImages_, const bool loop_, const double totalTime_);

		unsigned int ANIMATION_LIMIT;

	private:
		/**
		* Updates the clip to a new position.
		* @param clip_ : The clip to update.
		* @param x_ : New x position.
		* @param y_ : New y position.
		*/
		void updateClip(SDL_Rect& clip_, const int x_, const int y_);

		int x; /**< The position on x axis on the sprite. */
		int y; /**< The position on x axis on the sprite. */
		int initialX; /**< Where to start/restart the animation on x. */
		int initialY; /**< Where to start/restart the animation on y. */
		int spriteWidth; /**< The sprite width. */
		int spriteHeight; /**< The sprite height. */
		int numberOfImages; /**< The number of images to animate inside the spritesheet. */
		bool loop; /**< Whether to loop or not. */
		double totalElapsedTime; /**< Total time elapsed on the animation, to check if the
			frame changed. */
		double totalTime; /**< Total time for each animation loop. */

		int animationCount;

};

#endif //INCLUDE_ANIMATION_H
