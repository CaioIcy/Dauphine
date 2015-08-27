#ifndef INCLUDE_BSTATEMAGICPROJECTILE_H
#define INCLUDE_BSTATEMAGICPROJECTILE_H

#include "StateBoss.h"

class BStateMagicProjectile : public StateBoss {

	public:
		/**
		* The constructor.
		* @param boss_ : Reference to the Boss.
		*/
		BStateMagicProjectile(Boss* const boss_);
		
		/**
		* The destructor.
		*/
		virtual ~BStateMagicProjectile(){}

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

#endif // INCLUDE_BSTATEMAGICPROJECTILE_H
