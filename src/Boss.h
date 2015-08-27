#ifndef INCLUDE_BOSS_H
#define INCLUDE_BOSS_H

#include "DynamicEntity.h"
#include "StateBoss.h"
#include "Animation.h"
#include "Potion.h"
#include <map>
#include <vector>
#include "Player.h"

class StateBoss;

class Boss : public DynamicEntity {

	public:

		enum BStates : uint8_t {
			IDLE = 0,
			ATTACK,
			SHIELD,
			TELEPORT,
			ICEPRISION,
			MAGICPROJECTILE,
			DEAD
		};

		/**
		* The constructor.
		*/
		Boss(const double x_, const double y_, const std::string& path_, Player* const player_);

		/**
		* The destructor.
		*/
		virtual ~Boss();

		/**
		* Updates the player.
		* @see Player::updateInput, Player::updatePosition
		* @param dt_ : Delta time. Time elapsed between one frame and the other, independent
		* 	of processing speed.
		*/
		virtual void update(const double dt_);

		void initializeStates();
		void destroyStates();
		void changeState(const BStates state_);

		/**
		* Renders the player.
		* Uses the player's sprite render method.
		* @see Sprite::render
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_);

		void usePotion(const int strength_, const int distance_);
		
		Animation* getAnimation();
		bool isDead();
		void setDead(bool isDead_);

		enum BossSkills : uint8_t {
			BS_MAGIC_SHIELD = 0,
			BS_TELEPORT,
			BS_MAGIC_PROJECTILE,
			BS_INVOKE_WIND,
			BS_ICE_PRISION,
			BS_FINAL_SPLENDOR
		};

		void randomSkill(const unsigned int index_);
		bool teleport();
		bool magicProjectile();
		bool invokeWind();
		bool icePrision();
		bool finalSplendor();

		unsigned int potionsLeft;

		bool sawPlayer;
		std::vector<Potion*> potions;

		unsigned int life;
		bool hasShield;
		bool canWalk;
		Player* player;
		Animation* powerAnimation;
		double powerX;
		double powerY;
		bool powerIsActivated;
		Sprite* power;
		SDL_Rect powerClip;
		SDL_RendererFlip powerFlip;
		Animation* shieldAnimation;
		Sprite* shield;
		SDL_Rect shieldClip;

	private:
		virtual void updateBoundingBox();
		virtual void handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_);
		
		StateBoss* currentState;
		Animation* animation;
		std::map<BStates, StateBoss*> statesMap;
		bool dead;

};

#endif // INCLUDE_BOSS_H
