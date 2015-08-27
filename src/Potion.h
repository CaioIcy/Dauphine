#ifndef INCLUDE_POTION_H
#define INCLUDE_POTION_H

#include "DynamicEntity.h"
#include "Animation.h"
/**
* Class for the bomb potion.
*/
class Potion : public DynamicEntity {
	public:
		/**
		* The constructor.
		*/
		Potion(const double x_, const double y_, const std::string& path_, const int strength_, const int inertia_, const int distance_, const bool isRight_);

		/**
		* The destructor.
		*/
		virtual ~Potion();

		/**
		*
		*/
		virtual void update(const double dt_);

		/**
		*
		*
		*/
		virtual void render(const double cameraX_, const double cameraY_);

		bool activated;

		Animation* getAnimation();

		bool canExplode;
		bool isExploding;

	private:
		/**
		*/
		virtual void handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_);
		virtual void updateBoundingBox();
		int strength;
		int distance;
		double flightTime;
		Animation* animation;

};

#endif // INCLUDE_BOMBPOTION_H
