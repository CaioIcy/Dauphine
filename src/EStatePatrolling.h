#ifndef INCLUDE_ESTATEPATROLLING_H
#define INCLUDE_ESTATEPATROLLING_H

#include "StateEnemy.h"

class EStatePatrolling : public StateEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EStatePatrolling(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EStatePatrolling(){}

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

	private:
		double direction;

};

#endif // INCLUDE_ESTATEPATROLLING_H
