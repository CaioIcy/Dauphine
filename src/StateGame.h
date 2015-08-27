#ifndef INCLUDE_STATEGAME_H
#define INCLUDE_STATEGAME_H

#include "Entity.h"
#include <vector>

/**
* Parent class for other game states.
*/
class StateGame {

	public:
		/**
		* The destructor.
		*/
		virtual ~StateGame();

		/**
		* Loads necessary objects.
		* Pure virtual function. Purpose is to load all things relevant to the state.
		*/
		virtual void load() = 0;

		/**
		* Update all entities.
		* Pure virtual function. Purpose is to update all the entities in the vector.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double dt_) = 0;

		/**
		* Unloads necessary objects.
		* Pure virtual function. Purpose is to unload whatever was previously loaded.
		*/
		virtual void unload() = 0;

		/**
		* Renders the level.
		* Always render on 0,0 position.
		* @see Sprite::render()
		*/
		virtual void render() = 0;

		/**
		* Adds an entity to the vector.
		*/
		void addEntity(Entity* const entity);

		/**
		* Deletes all the entities inside the vector.
		*/
		void cleanEntities();

	protected:
		std::vector<Entity*> entities; /**< List of all the entities in the state. */

};

#endif //INCLUDE_STATEGAME_H
