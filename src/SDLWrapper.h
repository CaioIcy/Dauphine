#ifndef INCLUDE_SDLWRAPPER_H
#define INCLUDE_SDLWRAPPER_H

// Add other SDL libraries here.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL2_framerate.h>

#include <string>

/**
* Wraps the SDL libraries.
* And contains the initializing and closing functions for the system(s). No instances
	necessary.
*/
class SDLWrapper {

	public:
		/**
		* The system initializer.
		* Initializes all the SDL systems and/or subsystems.
		* @return True if every system was initialized successfully, else it returns false.
		* @todo Initialize SDL_TTF. And not do INIT_EVERYTHING.
		*/
		static bool initialize();

		/**
		* Closes all open systems.
		* Closes all systems and/or subsystems opened by the initializer method.
		* @see initialize()
		*/
		static void close();

	private:
		/**
		* Logs the SDL API version.
		* @param what_ : What API is being logged about.
		* @param compiled_ : The compiled version.
		* @param linked_ : The linked version.
		* @param revision_ : If any, the revision.
		*/
		static void logSDLVersion(const std::string& what_, const SDL_version& compiled_,
			std::string revision_ = std::string(""));

};

#endif // INCLUDE_SDLWRAPPER_H 
