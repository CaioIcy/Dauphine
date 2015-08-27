#ifndef INCLUDE_BSTATEIDLE_H
#define INCLUDE_BSTATEIDLE_H

#include "StateBoss.h"

class BStateIdle : public StateBoss {

	public:
		/**
		* The constructor.
		* @param boss_ : Reference to the Boss.
		*/
		BStateIdle(Boss* const boss_);
		
		/**
		* The destructor.
		*/
		virtual ~BStateIdle(){}

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

#endif // INCLUDE_BSTATEIDLE_H
