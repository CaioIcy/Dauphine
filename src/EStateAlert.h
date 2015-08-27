#ifndef INCLUDE_ESTATEALERT_H
#define INCLUDE_ESTATEALERT_H

#include "StateEnemy.h"

class EStateAlert : public StateEnemy {

	public:
		/**
		* The constructor.
		* @param enemy_ : Reference to the Enemy.
		*/
		EStateAlert(Enemy* const enemy_);
		
		/**
		* The destructor.
		*/
		virtual ~EStateAlert(){}

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

#endif // INCLUDE_ESTATEALERT_H
