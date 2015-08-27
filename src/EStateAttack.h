#ifndef INCLUDE_ESTATEATTACK_H
#define INCLUDE_ESTATEATTACK_H

#include "StateEnemy.h"

class EStateAttack : public StateEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EStateAttack(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EStateAttack(){}

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

#endif // INCLUDE_ESTATEATTACK_H
