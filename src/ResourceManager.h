#ifndef INCLUDE_RESOURCEMANAGER_H
#define INCLUDE_RESOURCEMANAGER_H

#include <map>
#include <string>
#include "Sprite.h"

/**
* General resource management class.
* @todo Generalize the resource manager for audio, not just sprites.
*/
class ResourceManager {

	public:
		/**
		* The constructor.
		* Initializes attributes.
		*/
		ResourceManager();

		/**
		* The destructor.
		* @note Warns about resources being deleted with references still pointing to them.
		*/
		~ResourceManager();
		
		/**
		* Retrieves the sprite from the resources.
		* @return The pointer to the wanted sprite. Creates it, if not already in resources.
		* @param path_ : Path to the desired sprite.
		*/
		Sprite* get(const std::string& path_);

	private:
		/**
		* Constructs the desired sprite.
		* @param path_ : Path to the desired sprite.
		*/
		Sprite::SpritePtr load(const std::string& path_);

		/**
		* Registers the resource on the resources map.
		* @param path_ : Path to the sprite. Will be the key value.
		* @param resource_ : The shared pointer for the resource.
		*/
		void registerResource(const std::string& path_, Sprite::SpritePtr resource_);

		/**
		* Unregisters the resource on the resources map.
		* @param path_ : The key (path to sprite) on the map.
		*/
		void unregisterResource(const std::string& path_);

		std::map<std::string, Sprite::SpritePtr> resources; /**< The map that contains all the
			Sprite resources. */

};

#endif // INCLUDE_RESOURCEMANAGER_H
