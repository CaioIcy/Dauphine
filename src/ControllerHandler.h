#ifndef INCLUDE_CONTROLLERHANDLER_H
#define INCLUDE_CONTROLLERHANDLER_H

#define CONTROLLERSTICK_DEAD_ZONE 8000
#define TRIGGER_DEAD_ZONE 8000

#include "InputKeys.h"
#include "SDLWrapper.h"

#include <array>

namespace controllerMap{

	/**
	* Button Enumeration for the Joystick
	*/

	enum buttons{		
 		FACE_DOWN, //X on PS4 controller - 0
 		FACE_RIGHT, //O on PS4 controller - 1
 		FACE_LEFT, //[] on PS4 controller - 2
 		FACE_UP, ///\ on PS4 controller - 3
 		
 		SELECT, //SHARE on PS4 controller - 4
 		HOME, // PS Button on PS4 controller - 5
 		START, //OPTIONS on PS4 controller - 6
 		
 		L3, //Left analogue button - 7
 		R3, //Right analogue button  - 8
 		
 		LDTRIGGER, //Left Digital Trigger - 9
 		RDTRIGGER, //Right Digital Trigger  - 10
 		 
 		DUP, //D-Pad up - 11
 		DDOWN, //D-Pad down - 12
 		DLEFT, //D-Pad left - 13
 		DRIGHT, //D-Pad rigth - 14

 		PRESSED,
 		RELEASED
	};

	enum axes{
		LHORIZONTAL, //Left Analogue Stick X - 0
		LVERTICAL, //Left Analogue Stick Y - 1
		
		RHORIZONTAL, //Left Analogue Stick X - 2
		RVERTICAL, //Left Analogue Stick Y - 3

		LATRIGGER, //Left Analogue Trigger - 4
		RATRIGGER //Left Analogue Trigger Y - 5
	};
}

/**
* The input handler for joysticks.
*/
class ControllerHandler {
	
	public:
		/**
		* The constructor.
		* Verifies if there is a joystick present.
		*/
		ControllerHandler();
		
		/**
		* Handles controller the input.
		* Detects the pending events, and simulates an appropriate KeyEvent by pushing one into
		* 	a stack.
		* @param sdlEvent_ : The SDL internal event structure.
		*/
		void handleInput(SDL_Event& sdlEvent_);

		std::array<bool, GameKeys::MAX> keyStates; /**< Boolean array that controls which keys are
		pressed or not. */

	private:
		SDL_GameController* gameController; /**< Pointer to the controller. */
};

#endif
