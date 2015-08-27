#ifndef INCLUDE_ENEMY_H
#define INCLUDE_ENEMY_H

#include "DynamicEntity.h"
#include "StateEnemy.h"
#include "Animation.h"
#include <map>

class StateEnemy;

class Enemy : public DynamicEntity {

	public:
		enum EStates : uint8_t {
			IDLE = 0,
			AERIAL,
			PATROLLING,
			CURIOUS,
			ALERT,
			ATTACK,
			DEAD
		};

		/**
		* The constructor.
		*/
		Enemy(const double x_, const double y_, const std::string& path_, const bool patrol_,
			const double patrolLength_);

		/**
		* The destructor.
		*/
		virtual ~Enemy();

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
		
		void initializeStates();
		void destroyStates();
		void changeState(const EStates state_);
		Animation* getAnimation();
		bool isDead();
		void setDead(bool isDead_);

		static double px;
		static double py;
		static unsigned int pLife;
		static bool pVulnerable;
		static double alertRange;
		static double curiousRange;

		double originalX;
		bool patrol;
		double patrolLength;
		unsigned int life;
	
	private:
		virtual void updateBoundingBox();
		virtual void handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_);
		void forceMaxSpeed();
		StateEnemy* currentState;
		Animation* animation;
		std::map<EStates, StateEnemy*> statesMap;
		bool dead;

};

#endif // INCLUDE_ENEMY_H
