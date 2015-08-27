#ifndef INCLUDE_ENTITY_H
#define INCLUDE_ENTITY_H

#include "Sprite.h"
#include "SDLWrapper.h"
#include <vector>
#include "CollisionRect.h"

/**
* Base class for all game objects (entities).
* The entity contains the (x,y) position, width and height, and a sprite.
*/
class Entity {

	public:
		/**
		* The destructor.
		*/
		virtual ~Entity();

		/**
		* Updates the entity.
		* Pure virtual function. Purpose is to update whatever is necessary, relative to the
		* 	entity.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double dt_) = 0;

		/**
		* Renders the entity.
		* Pure virtual function. Purpose is to copy the entity's texture onto the renderer.
		* @note Usually just calls the render method from the Sprite class.
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_) = 0;

		/**
		* @return The Entity width.
		*/
		unsigned int getWidth();

		/**
		* @return The Entity height.
		*/
		unsigned int getHeight();

		/**
		* @return The Entity::animationClip.
		*/
		SDL_Rect& getAnimationClip();

		SDL_Rect& getBoundingBox();

		virtual void setCollisionRects(const std::vector<CollisionRect>& collisionRects_);

		double x; /**< The position in the x axis. */
		double y; /**< The position in the y axis. */
		bool isRight; /**< The direction in the x axis. */ 

	protected:
		/**
		* The constructor.
		* Initializes all the attributes.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		* @param sprite_ : which sprite to use.
		*/
		Entity(const double x_, const double y_, const std::string& path_);

		/**
		* The constructor.
		* Initializes all the attributes.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		*/
		Entity(const double x_, const double y_);

		Sprite* sprite; /**< The Sprite attributed to the entity. */
		unsigned int width; /**< The entitys width, from its sprite. */
		unsigned int height; /**< The entitys height, from its sprite. */
		SDL_Rect animationClip; /**< The current clip on the spritesheet, to determine animation. */
		SDL_Rect boundingBox;

		std::vector<CollisionRect> collisionRects; /**< The SDL_Rects containing collidable tiles 
			positions. */

};

#endif //INCLUDE_ENTITY_H
