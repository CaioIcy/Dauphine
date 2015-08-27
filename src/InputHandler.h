#ifndef INCLUDE_INPUTHANDLER_H
#define INCLUDE_INPUTHANDLER_H

#include "SDLWrapper.h"
#include "InputKeys.h"
#include "ControllerHandler.h"

#include <array>

/**
* Handles player input.
* Using SDL event handling, recieves the player input accordingly.
*/
class InputHandler {

	public:
		/**
		* The constructor.
		* Used to create the input handler instance.
		*/
		InputHandler();
		
		/**
		* The destructor.
		* Deletes the InputHandler instance.
		*/
		~InputHandler();

		/**
		* Handles the input.
		* Detects the pending events, and handles them appropriately.
		*/
		void handleInput();

		/**
		* @return InputHandler::keyStates
		*/
		std::array<bool, GameKeys::MAX> getKeyStates();

		/**
		* @return InputHandler::quitFlag
		*/
		bool isQuitFlag();

		void clearKey(const GameKeys key_);

	private:
		/**
		* Sets InputHandler::quitFlag to true.
		*/
		void signalExit();

		ControllerHandler* controllerHandler; /**< Handles input if joystick is present. */
		std::array<bool, GameKeys::MAX> keyStates; /**< Boolean array that controls which keys are
			pressed or not. */
		SDL_Event sdlEvent; /**< SDL internal event structure. */
		bool quitFlag; /**< If the quit signal was recieved or not. */

};

#endif //INCLUDE_INPUTHANDLER_H
