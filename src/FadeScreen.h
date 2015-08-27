#ifndef INCLUDE_FADESCREEN_H
#define INCLUDE_FADESCREEN_H

#include "Entity.h"
#include "Sprite.h"
#include "FadeHandler.h"

class FadeScreen{

	public:
		FadeScreen();
		virtual ~FadeScreen();

		void update(const double dt_);
		void render();
		bool isFaded();
		void fadeOut(const double percentage_, const double time_);
		void fadeIn(const double percentage_, const double time_);

	private:
		Sprite* fadeImage;
		FadeHandler* fadeHandler;

};

#endif // INCLUDE_FADESCREEN_H
