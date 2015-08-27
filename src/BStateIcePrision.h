#ifndef INCLUDE_BSTATEICEPRISION_H
#define INCLUDE_BSTATEICEPRISION_H

#include "StateBoss.h"

class BStateIcePrision : public StateBoss {

	public:
		/**
		* The constructor.
		* @param boss_ : Reference to the Boss.
		*/
		BStateIcePrision(Boss* const boss_);
		
		/**
		* The destructor.
		*/
		virtual ~BStateIcePrision(){}

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

#endif // INCLUDE_BSTATEICEPRISION_H
