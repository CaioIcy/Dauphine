#ifndef INCLUDE_CAMERA_H
#define INCLUDE_CAMERA_H

#include "SDLWrapper.h"
#include "Entity.h"

/**
* The camera class.
* Contains all the relevant implementation relative to the camera.
*/
class Camera {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		* @param entity_ : The entity to centralize the camera on.
		*/
		Camera(Entity* const entity_);

		/**
		* The destructor.
		*/
		~Camera();

		/**
		* Updates the camera.
		* @see Camera::updatePosition
		* Centralizes the player on the screen.
		*/
		void update();

		/**
		* Changes the entity to centralize upon.
		* @param entity_ : The entity to centralize the camera on.
		*/
		void centralizeOn(Entity* const entity_);

		/**
		* @return The camera clip (an SDL_Rect).
		*/
		SDL_Rect& getClip();

		/**
		* @param width_,height_ : Tells the camera what the width and height of the level is.
		* @see Level::update()
		*/
		void setLevelWH(const unsigned int width_, const unsigned int height_);

	private:
		/**
		* Updates the cameras position.
		* Based on the players position, change cameras position.
		*/
		void updatePosition();

		Entity* entity; /**< Reference to the entity. */
		unsigned int levelW; /**< The width of the level. */
		unsigned int levelH; /**< The height of the level. */
		SDL_Rect clip; /**< Clip which will be used to clip the rendering only to the extent of
			the camera. */

};

#endif //INCLUDE_CAMERA_H
