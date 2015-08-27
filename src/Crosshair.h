#ifndef INCLUDE_CROSSHAIR_H
#define INCLUDE_CROSSHAIR_H

#include "Entity.h"

/**
* @todo Refactor.
*/
class Crosshair : public Entity {
	public:
		Crosshair(const double x_, const double y_, const std::string& path_);
		virtual ~Crosshair();
		virtual void update(const double dt_);
		virtual void render(const double cameraX_, const double cameraY_);
		unsigned int getWidth();
		unsigned int getHeight();
		bool activated;

};

#endif // INCLUDE_CROSSHAIR_H
