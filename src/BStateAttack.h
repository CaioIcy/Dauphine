#ifndef INCLUDE_BSTATEATTACK_H
#define INCLUDE_BSTATEATTACK_H

#include "StateBoss.h"

class BStateAttack : public StateBoss {

	public:
		/**
		* The constructor.
		* @param boss_ : Reference to the Boss.
		*/
		BStateAttack(Boss* const boss_);
		
		/**
		* The destructor.
		*/
		virtual ~BStateAttack(){}

		/**
		* @see StateBoss::enter
		*/
		virtual void enter();

		/**
		* @see StateBoss::exit
		*/
		virtual void exit();

		/**
		* @see StateBoss::update
		*/
		virtual void update(const double dt_);

};

#endif // INCLUDE_BSTATEATTACK_H
