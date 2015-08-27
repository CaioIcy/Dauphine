#include "TileMap.h"
#include "Game.h"
#include "Collision.h"
#include "Logger.h"
#include "Configuration.h"
#include <cassert>

TileMap::TileMap(const std::string& mapPath_) :
	map(nullptr),
	layers(0),
	mapWidth(0),
	mapHeight(0),
	initialX(0),
	initialY(0)
{
	load(mapPath_);
}

TileMap::~TileMap(){
	if(this->map != nullptr){
		delete this->map;
		this->map = nullptr;
	}
}

void TileMap::load(const std::string& mapPath_){
	this->map = new Tmx::Map();
	this->map->ParseFile(mapPath_);

	if(!this->map->HasError()){

		const Tmx::Tileset* metaTileset = nullptr;

		// Iterating through the tilesets to load their respective sprites.
		for (int i = 0; i < this->map->GetNumTilesets(); i++) {
			const Tmx::Tileset* tileSet = this->map->GetTileset(i);

			if(tileSet->GetProperties().HasProperty("meta")){
				metaTileset = tileSet;
			}

			addTileSet("assets/maps/" + tileSet->GetImage()->GetSource());
		}

		if(metaTileset == nullptr){
			Log(ERROR) << "The map (" << mapPath_ << ") does not contain a meta tileset!";
		}

		// Getting the number of layers inside the map.
		this->layers = this->map->GetNumLayers();

		// Getting the map width/height by the first layer, since theoretically the
		// width/height should be the same for all layers.
		this->mapWidth = this->map->GetLayer(0)->GetWidth();
		this->mapHeight = this->map->GetLayer(0)->GetHeight();

		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int k = 0;

		// Setting the size of the TileMap::tileMatrix, defaulting values to zero.
		// First dimension.
		this->tileMatrix.resize(this->mapWidth);

		// Second dimension.
		for (i = 0; i < this->tileMatrix.size(); i++){
			this->tileMatrix[i].resize(this->mapHeight);
		}

		// Third dimension.
		for (i = 0; i < this->tileMatrix.size(); i++){
			for (j = 0; j < this->tileMatrix[0].size(); j++){
				this->tileMatrix[i][j].resize(this->layers, 0);
			}
		}

		const Tmx::Layer* currentLayer;
		for (i = 0; i < this->layers; i++){
			currentLayer = this->map->GetLayer(i);

			// Saving all the tile IDs on the TileMap::tileMatrix
			for (j = 0; j < this->mapWidth; j++){
				for (k = 0; k < this->mapHeight; k++){

					int tileId = currentLayer->GetTileId(j, k);

					if (currentLayer->IsTileFlippedDiagonally(j, k)){
						tileId |= Tmx::FlippedDiagonallyFlag;
					}
					if (currentLayer->IsTileFlippedHorizontally(j, k)){
						tileId |= Tmx::FlippedHorizontallyFlag;
					}
					if (currentLayer->IsTileFlippedVertically(j, k)){
						tileId |= Tmx::FlippedVerticallyFlag;
					}

					this->tileMatrix[j][k][i] = tileId;

					if(currentLayer->GetName() == "Collision"){
						if(this->tileMatrix[j][k][i] > 0){
							const Tmx::Tile* tile = metaTileset->GetTile(tileId);
							const std::string property = tile->GetProperties().GetList().begin()->second;
							SDL_Rect tileRect = {(int)(j * TILE_SIZE), (int)(k * TILE_SIZE), TILE_SIZE, TILE_SIZE};

							if(property == "level_begin"){
								this->initialX = tileRect.x;
								this->initialY = tileRect.y;
								continue;
							}
							else if(property == "enemy_patrol" || property == "enemy_no_patrol"){
								this->enemiesX.push_back(tileRect.x);
								this->enemiesY.push_back(tileRect.y);
								this->enemiesPatrol.push_back((property == "enemy_patrol") ? true : false);
								continue;
							}

							TypeCollision type = CollisionRect::stringToType(property);
							CollisionRect collisionRect(tileRect, type);
							this->collisionRects.push_back(collisionRect);
						}
					}
				}
			}
		}

		Log(DEBUG) << "TileMap::load Map loaded (width:" << this->mapWidth << " height:" << this->mapHeight << " layers:" << this->layers << ")";

	}
	else{
		Log(ERROR) << "Unable to parse map at \"" << mapPath_ << "\" with error: " <<
			this->map->GetErrorText();
	}
}

void TileMap::render(const double cameraX_, const double cameraY_){
	assert((this->tilesetSprites.size() > 0) && "No tilesets detected for the TileMap!");

	const Tmx::Layer* currentLayer;
	for(unsigned int i = 0; i < this->layers - 1; i++){
		currentLayer = this->map->GetLayer(i);
		if (i > this->tileMatrix[0][0].size()){
			Log(ERROR) << "Invalid layer number for rendering a TileMap layer.";
			continue;
		}

		if(currentLayer->GetName() == "Background02"){
			renderLayer(cameraX_/20, cameraY_, i);
		}
		else if(currentLayer->GetName() == "Background01"){
			renderLayer(cameraX_/10, cameraY_, i);
		}
		else if(currentLayer->GetName() == "Background00"){
			renderLayer(cameraX_/1.6, cameraY_, i);
		}
		else{
			renderLayer(cameraX_, cameraY_, i);
		}
	}
}


void TileMap::renderLayer(const double cameraX_, const double cameraY_, const unsigned int layer_){
	const int tilesInX = this->tileMatrix.size();
	const int tilesInY = this->tileMatrix[0].size();

	const Tmx::Layer* currentLayer = this->map->GetLayer(layer_);

	SDL_Rect camera = {(int)cameraX_, (int)cameraY_, (int)Configuration::getCameraDistanceWidth(), (int)Configuration::getCameraDistanceHeight()};

	for (int x = 0; x < tilesInX; x++){
		for (int y = 0; y < tilesInY; y++){

			SDL_Rect tileRect = {(x * TILE_SIZE), (y * TILE_SIZE), TILE_SIZE, TILE_SIZE};
			const bool tileIsOnScreen = Collision::rectsCollided(camera, tileRect);

			if(tileIsOnScreen){
				// Getting the tile position inside its tileset.
				unsigned int tilePosition = tileMatrix[x][y][layer_];
				SDL_RendererFlip flip = SDL_FLIP_NONE;

				if((tilePosition & Tmx::FlippedDiagonallyFlag) != 0){
					/// @todo Figure out how to make g++ stop bitching about (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL).
					//flip = (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
				}
				if((tilePosition & Tmx::FlippedHorizontallyFlag) != 0){
					flip = SDL_FLIP_HORIZONTAL;	
				}
				if((tilePosition & Tmx::FlippedVerticallyFlag) != 0){
					flip = SDL_FLIP_VERTICAL;
				}

				tilePosition &= ~(Tmx::FlippedDiagonallyFlag | Tmx::FlippedHorizontallyFlag | Tmx::FlippedVerticallyFlag);

				// If its a valid tile.
				if (tilePosition > 0){
					// The x,y position in the level of the tile.
					const double posX = ((x * TILE_SIZE) - cameraX_);
					const double posY = ((y * TILE_SIZE) - cameraY_);

					// Which tileset sprite the tile belongs to.
					const int tilesetId = currentLayer->GetTileTilesetIndex(x,y);

					Sprite* const tilesetSprite = this->tilesetSprites.at(tilesetId);

					// The number of tiles per line, on that tileset.
					const int tilesPerLine = tilesetSprite->getWidth() / TILE_SIZE;

					// The clip for the tileset.
					SDL_Rect tileClip;
					tileClip.x = (tilePosition%tilesPerLine) * TILE_SIZE;
					tileClip.y = (tilePosition/tilesPerLine) * TILE_SIZE;
					tileClip.w = TILE_SIZE;
					tileClip.h = TILE_SIZE;
					
					tilesetSprite->render(posX, posY, &tileClip, false, 0.0, nullptr, flip);
					
				}
				else{
					// Do nothing, no rendering an empty tilespace.
				}
			}
			else{
				// Tile is not on screen, don't render.
			}
			
		}
	}
}

void TileMap::addTileSet(const std::string& path_){
	Sprite* newTileSet = Game::instance().getResources().get(path_);
	this->tilesetSprites.push_back(newTileSet);
}

std::vector <CollisionRect>& TileMap::getCollisionRects(){
	return this->collisionRects;
}

unsigned int TileMap::getMapWidth(){
	return this->mapWidth * TILE_SIZE;
}

unsigned int TileMap::getMapHeight(){
	return this->mapHeight * TILE_SIZE;
}

double TileMap::getInitialX(){
	return (double)this->initialX;
}

double TileMap::getInitialY(){
	return (double)this->initialY;
}

std::vector<int>& TileMap::getEnemiesX(){
	return this->enemiesX;
}

std::vector<int>& TileMap::getEnemiesY(){
	return this->enemiesY;
}

std::vector<bool>& TileMap::getEnemiesPatrol(){
	return this->enemiesPatrol;
}
