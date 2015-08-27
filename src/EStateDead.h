#ifndef INCLUDE_ESTATEDEAD_H
#define INCLUDE_ESTATEDEAD_H

#include "StateEnemy.h"

class EStateDead : public StateEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EStateDead(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EStateDead(){}

		/**
		* @see StateEnemy::enter
		*/
		virtual void enter();

		/**
		* @see StateEnemy::exit
		*/
		virtual void exit();

		/**
		* @see StateEnemy::update
		*/
		virtual void update(const double dt_);

};

#endif // INCLUDE_ESTATEDEAD_H
