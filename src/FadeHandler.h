#ifndef INCLUDE_FADEHANDLER_H
#define INCLUDE_FADEHANDLER_H

#include "Sprite.h"

class FadeHandler {

	public:
		FadeHandler(Sprite* const sprite_);
		virtual ~FadeHandler();

		void fadeIn(const double percentage_, const double time_);
		void fadeOut(const double percentage_, const double time_);
		void update(const double dt_);
		double getCurrentPercentage();

	private:
		bool shouldFadeIn;
		bool shouldFadeOut;
		double percentageOfStop;
		Sprite* sprite;
		double time;
		double currentPercentage;
		double rate;

};

#endif // INCLUDE_FADEHANDLER_H
