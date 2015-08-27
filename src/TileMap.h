#ifndef INCLUDE_TILEMAP_H
#define INCLUDE_TILEMAP_H

#include "../externals/TmxParser/Tmx.h"
#include "Sprite.h"
#include <vector>
#include "CollisionRect.h"

const int TILE_SIZE = 64;

/**
* Represents the tile distrubution for a level.
* @todo Revise Tile placement implementation.
*/
class TileMap {

	public:
		/**
		* The constructor.
		* @param mapPath_ : Path to the desired Tiled map.
		*/
		TileMap(const std::string& mapPath_);

		/**
		* The destructor.
		*/
		~TileMap();

		/**
		* Renders the TileMap.
		* 
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		void render(const double cameraX_, const double cameraY_);

		unsigned int getMapWidth();
		unsigned int getMapHeight();
		std::vector <CollisionRect>& getCollisionRects();

		double getInitialX();
		double getInitialY();

		std::vector<int>& getEnemiesX();
		std::vector<int>& getEnemiesY();
		std::vector<bool>& getEnemiesPatrol();		

	private:
		/**
		*
		*/
		void load(const std::string& mapPath_);

		/**
		*
		*/
		void addTileSet(const std::string& path_);

		/**
		* Renders a certain layer from the TileMap.
		* 
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		void renderLayer(const double cameraX_, const double cameraY_, const unsigned int layer_);

		Tmx::Map* map;

		unsigned int layers;
		unsigned int mapWidth;
		unsigned int mapHeight;
		unsigned int initialX;
		unsigned int initialY;

		std::vector <std::vector <std::vector <unsigned int>>> tileMatrix; /**< Three-dimensional
			matrix, that contains x = width, y = height, z = layers */

		std::vector <Sprite*> tilesetSprites;

		std::vector <CollisionRect> collisionRects;

		std::vector<int> enemiesX;
		std::vector<int> enemiesY;
		std::vector<bool> enemiesPatrol;

};

#endif // INCLUDE_TILEMAP_H
