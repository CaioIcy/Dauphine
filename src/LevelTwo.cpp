#include "LevelTwo.h"
#include "Game.h"
#include "LuaScript.h"
#include "Logger.h"
#include "Enemy.h"
#include "Crosshair.h"
#include "TileMap.h"
#include "Collision.h"
#include "Crosshair.h"

LevelTwo::LevelTwo() :
	Level(),
	items{{4090 - 3*64, 7870 - 3*64, 0, 0},{2776, 1700, 0, 0}},
	caughtItems{false,false,true,false}
{
	this->changeCheckpoints(2, {4090,7870}, {2776,1700});
}

LevelTwo::~LevelTwo(){

}

void LevelTwo::load(){
	// Changing the music.
	Game::instance().getAudioHandler().changeMusic("assets/audio/lv1.wav");

	// Loading the tile/tilemap.
	this->tileMap = new TileMap("assets/maps/level2.tmx");

	// Setting the level width/height.
	this->width = this->tileMap->getMapWidth();
	this->height = this->tileMap->getMapHeight();
	SDL_Rect bounds = {0, 0, (int)this->width, (int)this->height};
	this->quadTree = new QuadTree(0, bounds);

	this->background = Game::instance().getResources().get("assets/images/lv1_background.png");
	for(int i = 0; i < this->NUMBER_OF_CHECKPOINTS; ++i){
		this->checkpoints.push_back(Game::instance().getResources().get("assets/images/checkpoint.png"));
	}
	this->image = Game::instance().getResources().get("assets/images/potion.png");

	// Getting information from lua script.
	LuaScript luaLevel1("lua/Level1.lua");
	const std::string pathPlayerSpriteSheet = luaLevel1.unlua_get<std::string>(
		"level.player.spriteSheet");
	const std::string pathBackgroundAudio = luaLevel1.unlua_get<std::string>(
		"level.audio.background");
	const std::string pathEnemy = luaLevel1.unlua_get<std::string>("level.enemy");

	// Changing the music.
	// Game::instance().getAudioHandler().changeMusic(pathBackgroundAudio);

	// Loading the player and the camera.
	Player* lPlayer = nullptr;
	
	if(Game::instance().getSaves().isSaved(Game::instance().currentSlot) && Game::instance().getSaves().getSavedLevel(Game::instance().currentSlot) == 2){
		double savedPX = 0.0;
		double savedPY = 0.0;

		Game::instance().getSaves().getPlayerPosition(savedPX, savedPY, Game::instance().currentSlot);

		lPlayer = new Player(savedPX, savedPY, pathPlayerSpriteSheet);
	}
	else{
		lPlayer = new Player(this->tileMap->getInitialX(), this->tileMap->getInitialY(), pathPlayerSpriteSheet);
	}
	
	Camera* lCamera = new Camera(lPlayer); 
	
	this->playerHud = new PlayerHUD(lPlayer);

	// Load all the enemies from the tileMap.
	for(unsigned int i = 0; i < this->tileMap->getEnemiesX().size(); i++){
		Enemy* enemy = new Enemy(this->tileMap->getEnemiesX().at(i),
			this->tileMap->getEnemiesY().at(i), pathEnemy,
			this->tileMap->getEnemiesPatrol().at(i), 0.0);

		if(Game::instance().getSaves().isSaved(Game::instance().currentSlot)){
			if(Game::instance().getSaves().isEnemyDead(i, Game::instance().currentSlot) && Game::instance().getSaves().getSavedLevel(Game::instance().currentSlot) == 2){
				enemy->setDead(true);
			}
		}
		enemy->setLevelWH(this->width, this->height);
		this->enemies.push_back(enemy);
	}

	// Finally, setting the player and the camera.
	setPlayer(lPlayer);
	Enemy::pLife = this->player->life;

	setCamera(lCamera);

	Game::instance().getFade().fadeOut(0, 0.002);
}

void LevelTwo::unload(){
	Log(DEBUG) << "\tUnloading level 2...";

	cleanEntities();
	clearEnemies();
	clearDocuments();

	for (int i = 0; i < NUMBER_ITEMS; ++i){
		caughtItems[i] = false;
	}

	//this->checkpointVisited = false;	
}

void LevelTwo::update(const double dt_){
	// Populating the QuadTree.
	this->quadTree->setObjects(this->tileMap->getCollisionRects());

	// Updating the entities, using the QuadTree.
	std::vector<CollisionRect> returnObjects;
	for (auto entity : this->entities) {
		returnObjects.clear();
		this->quadTree->retrieve(returnObjects, entity->getBoundingBox());
		entity->setCollisionRects(returnObjects);
		entity->update(dt_);
	}

	// Updating the enemies.
	for(auto enemy : this->enemies){
		returnObjects.clear();
		this->quadTree->retrieve(returnObjects, enemy->getBoundingBox());
		enemy->setCollisionRects(returnObjects);
		enemy->update(dt_);
	}

	// Set to GameOver if the player is dead.
	if(this->player->isDead()){
		Game::instance().setState(Game::GStates::GAMEOVER);
		return;
	}

	// Updating the potions.
	for(auto potion : this->player->potions){
		returnObjects.clear();
		this->quadTree->retrieve(returnObjects, potion->getBoundingBox());
		potion->setCollisionRects(returnObjects);
	}

	/// @todo Maybe refactor this static Enemy::px, Enemy::py.
	// Updating player info for the enemies.
	Enemy::px = this->player->x;
	Enemy::py = this->player->y;
	Enemy::pVulnerable = this->player->isVulnerable;

	for (int i = 0; i < NUMBER_ITEMS; ++i){	
		if(Collision::rectsCollided(this->player->getBoundingBox(), {items[0][i], items[1][i], 192, 192}) && caughtItems[i] == false){
			this->player->addPotions(3);
			caughtItems[i]=true;
		}
	}

	if(this->player->life != Enemy::pLife){
		if(this->player->isVulnerable){
			this->player->life--;
			Enemy::pLife = this->player->life;
			this->player->changeState(Player::PStates::HITED);
			this->player->isVulnerable = false;
		}
		else{

		}
	}

	// Updating the HUD.
	this->playerHud->update();

	// Updating the camera.
	this->camera->update();

	// Set next level if end is reached.
	if(this->player->reachedLevelEnd){
		Game::instance().transitionTo = Game::GStates::LEVEL_THREE;
		Game::instance().setState(Game::GStates::TRANSITION);
		return;
	}

	// Updating the potion/enemy collision.
	for(auto potion : this->player->potions){
		for(auto enemy : this->enemies){
			if(Collision::rectsCollided(potion->getBoundingBox(), enemy->getBoundingBox())){
				if(potion->activated){
					
					if(enemy->life > 0 && this->player->canAttack){
						enemy->life -= 100;
						potion->activated = false;
					}
					// Log(DEBUG) << "Enemy Life = " << enemy->life;

					if(enemy->life <= 0)
						enemy->changeState(Enemy::EStates::DEAD);
				}
			}
		}
	}

	// Updating the player attack/enemy collision.
	for(auto enemy : this->enemies){
		if(Collision::rectsCollided(this->player->getBoundingBox(), enemy->getBoundingBox())){
			if(this->player->isRight != enemy->isRight)
				if(this->player->isCurrentState(Player::PStates::ATTACK) || this->player->isCurrentState(Player::PStates::ATTACKMOVING)){
					
					if(enemy->life > 0 && this->player->canAttack){
						enemy->life -= this->player->attackStrength;
						this->player->canAttack = false;
					}
					// Log(DEBUG) << "Enemy Life = " << enemy->life;

					if(enemy->life <= 0)
						enemy->changeState(Enemy::EStates::DEAD);
				}
		}
	}

	//Saving the game state
	for(int j = 0; j < this->NUMBER_OF_CHECKPOINTS; ++j){
		if(!this->checkpointsVisited[j] && this->player->getBoundingBox().x >= checkpointsX[j] 
				&& this->player->getBoundingBox().x <= checkpointsX[j] + 100 && this->player->getBoundingBox().y >= checkpointsY[j]
				&& this->player->getBoundingBox().y <= checkpointsY[j] + 200){
			this->checkpoints[j] = Game::instance().getResources().get("assets/images/checkpoint_visited.png");
			Game::instance().getSaves().saveLevel(2, this->player, this->enemies, Game::instance().currentSlot);
			this->checkpointsVisited[j] = true;
		}	
	}

	// Documents check
	for(auto document : this->documents){
		if(Collision::rectsCollided(this->player->getBoundingBox(), document->getBoundingBox())){
			document->shouldRender = true;
		}
		else {
			document->shouldRender = false;
		}
	}
}

void LevelTwo::render(){
	const int cameraX = this->camera->getClip().x;
	const int cameraY = this->camera->getClip().y;

	this->background->render(0, 0);

	for(int j = 0; j < this->NUMBER_OF_CHECKPOINTS; ++j){
		this->checkpoints[j]->render(this->checkpointsX[j] - cameraX, this->checkpointsY[j] - cameraY);
	}

	// Render the tiles in the TileMap.
	this->tileMap->render(cameraX, cameraY);

	this->playerHud->render();

	for(auto enemy : this->enemies){
		enemy->render(cameraX, cameraY);
	}

	// Render all the entities in the list.
	for(auto entity : this->entities){
        entity->render(cameraX, cameraY);
	}

	for (unsigned int i = 0; i < NUMBER_ITEMS; i++){
		if(this->image != nullptr && caughtItems[i] == false){
			
			this->image->Sprite::render((items[0][i]+60) - cameraX, ((items[1][i]) - cameraY));
		
		}
	}

	// Document text image
	for(auto document : this->documents){
		document->render(cameraX, cameraY);
		if(document->shouldRender){
			document->renderDocumentText();
		}
	}
}

