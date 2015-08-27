#ifndef INCLUDE_DYNAMICENTITY_H
#define INCLUDE_DYNAMICENTITY_H

#include "Entity.h"
#include "Crosshair.h"
#include <array>

enum CollisionSide : uint8_t {
	SOLID_TOP = 0,
	SOLID_BOTTOM,
	SOLID_RIGHT,
	SOLID_LEFT,
	SOLID_TOTAL
};

/**
* Subclass of Entity.
* The objects of this class are entities, but have physics applied to them (such as velocity).
*/
class DynamicEntity : public Entity {

	public:
		/**
		* The constructor.
		* Initializes all attributes.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		* @param sprite_ : which sprite to use.
		*/
		DynamicEntity(const double x_, const double y_, const std::string& path_);

		/**
		* The destructor.
		*/
		virtual ~DynamicEntity();

		virtual void jump();
		virtual void applyGravity();
		virtual void move(const bool movingLeft_, const bool movingRight_);
		virtual void moveVertical(const bool movingUp_, const bool movingDown_);
		virtual void slowVx();
		virtual void slowVy();
		virtual void roll();
		virtual void aim(Crosshair* const crosshair, double direction);

		/**
		* @param width_,height_ : Tells the player what the width and height of the level is.
		* @see Level::update()
		*/
		virtual void setLevelWH(const unsigned int width_, const unsigned int height_);

		double vx; /**< The dynamic entity's speed on the x axis. */
		double vy; /**< The dynamic entity's speed on the x axis. */
		double speed; /**< Speed that moves dynamic entity on input. */
		double maxSpeed; /**< Dynamic entity max speed. */		
		bool isGrounded; /**< Check for if the dynamic entity is on the ground. */
		double nextX;
		double nextY;
		bool reachedLevelEnd;

	    bool activated;
	    int strength;
	    int distance;
	    double flightTime;

	    bool isClimbing;

	protected:
		/**
		* Updates the position of the dynamic entity
		* Update is based on what input was recieved, and the players velocity.
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		virtual void updatePosition(const double dt_);

		virtual void scoutPosition(const double dt_); 

		/**
		* @return A bool array with the sides the DynamicEntity collided.
		*/
		virtual std::array<bool, CollisionSide::SOLID_TOTAL> detectCollision();

		/**
		* Handles the collision.
		*/
		virtual void handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_) = 0;

		virtual SDL_RendererFlip getFlip();

		virtual void updateBoundingBox() = 0;

		unsigned int levelW; /**< The width of the level. */
		unsigned int levelH; /**< The height of the level. */

};

#endif // INCLUDE_DYNAMICENTITY_H
