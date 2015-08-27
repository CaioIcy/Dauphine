#ifndef INCLUDE_STATEENEMY_H
#define INCLUDE_STATEENEMY_H

#include "Enemy.h"

class Enemy;

/**
* Parent class for other enemy states.
* 
*/
class StateEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		StateEnemy(Enemy* const enemy_);

		/**
		* The destructor.
		*/
		virtual ~StateEnemy();

		/**
		* Method called on load.
		* Pure virtual function. Called on state enter.
		*/
		virtual void enter() = 0;

		/**
		* Method called on unload.
		* Pure virtual function. Called on state exit.
		*/
		virtual void exit() = 0;

		/**
		* Update method for the state.
		* While the Enemy is on the state, this method runs every update.
		*/
		virtual void update(const double dt_) = 0;

		Enemy* enemy; /**< Reference to the enemy. */

};

#endif // INCLUDE_STATEENEMY_H