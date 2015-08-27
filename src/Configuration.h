#ifndef INCLUDE_CONFIGURATION_H
#define INCLUDE_CONFIGURATION_H

#include <string>

/**
* Game configuration class.
* @todo Refactor the Configuration class.
* @todo Implement all the possible resolutions the game will "want".
*/
class Configuration {

	public:
		/**
		* Initializes all the attributes.
		*/
		static void initialize();

		/**
		* @return resolutionWidth
		*/
		static unsigned int getResolutionWidth();

		/**
		* @return resolutionHeight
		*/
		static unsigned int getResolutionHeight();

		/**
		* @return maxFramerate
		*/
		static uint32_t getMaxFramerate();

		/**
		* @return windowTitle
		*/
		static std::string getWindowTitle();

		/**
		* @return initialMultiplier
		* @see Window::rescale
		*/
		static unsigned int getLogicalRenderSize();

		/**
		* @return cameraDistanceWidth
		*/
		static unsigned int getCameraDistanceWidth();

		/**
		* @return cameraDistanceHeight
		*/
		static unsigned int getCameraDistanceHeight();

		/**
		* @return The current screen width.
		*/
		static unsigned int getScreenWidth();

		/**
		* @return The current screen height.
		*/
		static unsigned int getScreenHeight();

	private:
		static const unsigned int resolutionWidth; /**< The game's width resolution. (16) */
		static const unsigned int resolutionHeight; /**< The game's height resolution. (10) */

		static uint32_t maxFramerate; /**< The game's max framerate. */
		static std::string windowTitle; /**< The game window's title. */

		static unsigned int logicalRenderSize; /**< The size of the logical rendering. */

		static unsigned int screenWidth; /**< The screen width. */
		static unsigned int screenHeight; /**< The screen height. */

		static unsigned int cameraDistanceWidth; /**< The width distance of the camera. */
		static unsigned int cameraDistanceHeight; /**< The height distance of the camera. */

};

#endif //INCLUDE_CONFIGURATION_H
