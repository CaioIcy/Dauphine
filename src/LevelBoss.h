#ifndef INCLUDE_LEVELBOSS_H
#define INCLUDE_LEVELBOSS_H

#include "Level.h"

/**
* The first level of the game.
* Derived from Level class.
*/
class LevelBoss : public Level {
	
	public:
		/**
		* The constructor.
		* @see Level::Level()
		*/
		LevelBoss();

		/**
		* The destructor.
		*/
		virtual ~LevelBoss();

		/**
		* Loads the level.
		* From the Level1.lua script, loads all the necessary objects.
		*/
		virtual void load();
		
		/**
		* Updates the objects within the Level.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double dt_);

		/**
		* Unloads everything that was loaded.
		* @see LevelOne::load()
		*/
		virtual void unload();

		/**
		* Renders the level.
		* Always renders on 0,0 position.
		* @see Sprite::render()
		*/
		virtual void render();

};

#endif //INCLUDE_LEVELBOSS_H
