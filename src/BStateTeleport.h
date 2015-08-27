#ifndef INCLUDE_BSTATETELEPORT_H
#define INCLUDE_BSTATETELEPORT_H

#include "StateBoss.h"

class BStateTeleport : public StateBoss {

	public:
		/**
		* The constructor.
		* @param boss_ : Reference to the Boss.
		*/
		BStateTeleport(Boss* const boss_);
		
		/**
		* The destructor.
		*/
		virtual ~BStateTeleport(){}

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

#endif // INCLUDE_BSTATETELEPORT_H
