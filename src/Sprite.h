#ifndef INCLUDE_SPRITE_H
#define INCLUDE_SPRITE_H

#include "SDLWrapper.h"
#include <memory>
#include <string>

/**
* Visual representation of game objects.
* Holds the SDL_Texture from the SDL2 library.
*/
class Sprite {

	public:
		typedef std::shared_ptr<Sprite> SpritePtr; /**< Typedef of a Sprite shared pointer. */

		/**
		* The constructor.
		* Initializes all the data, and sets the desired renderer. Loads image with the desired
		* 	path.
		* @param path_ : the image path.
		* @see Sprite::loadFrom
		*/
		Sprite(const std::string& path_);
		Sprite(SDL_Surface* const surface_);

		/**
		* The destructor.
		* Destroys the SDL_Texture.
		*/
		~Sprite();

		/**
		* Renders the sprite.
		* Copy the SDL_Texture onto the renderer, at the desired x,y position.
		* @param x_ : The position on the x axis of the screen.
		* @param y_ : The position on the y axis of the screen.
		* @param clip_ : Clips the texture, on the SDL_Rect bounds. If omitted, renders entire
		* 	texture.
		* @param stretch_ : Whether to stretch the image to the entire screen or not.
		* @param angle_ : An angle in degrees that indicates the rotation that will be applied
		* 	to the renderQuad. If omitted, no rotation will be applied.
		* @param center_ : A point indicating the point around which renderQuad will be
		* 	rotated. If omitted, rotation will be done in width/height center.
		* @param flip_ : Value static which flipping actions should be performed on the
		* 	texture.
		* @note The only obligatory parameters are x_ and y_.
		* @note If the Window renderer is null, will halt the game.
		* @note If it fails to render, logs an error message.
		*/
		void render(const double x_, const double y_, SDL_Rect* const clip_ = nullptr,
			const bool stretch_ = false, const double angle_ = 0.0,
			SDL_Point* const center_ = nullptr, SDL_RendererFlip flip_ = SDL_FLIP_NONE);

		/**
		* @return The Sprite width.
		*/
		unsigned int getWidth();

		void setWidth(unsigned int width_);

		void setHeight(unsigned int height_);

		/**
		* @return The Sprite height.
		*/
		unsigned int getHeight();

		std::string getPath();

		double getAlpha();
		void setAlpha(int alpha_);
		
	private:
		/**
		* Loads image from a path.
		* Given an existing path for an image, loads the SDL_Texture from it.
		* @param path_ : the image path.
		* @note Error message is logged if the sprite's SDL_Texture (sdlTexture) is null after
			method.
		*/
		void loadFrom(const std::string& path_);

		SDL_Texture* surfaceToTexture(SDL_Surface* const surface_);

		SDL_Texture* sdlTexture; /**< The SDL texture to use as the image. */

		void setBlendMode(SDL_BlendMode blending_);

		unsigned int width; /**< The loaded image's width. */
		unsigned int height; /**< The loaded image's width. */
		const std::string path; /**< Holds the path from where the Sprite was loaded. */
		bool flipHorizontal; /**< When true flip the image */

};

#endif //INCLUDE_SPRITE_H
