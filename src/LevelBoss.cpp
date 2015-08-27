#include "LevelBoss.h"
#include "Game.h"
#include "LuaScript.h"
#include "Logger.h"
#include "Enemy.h"
#include "Crosshair.h"
#include "TileMap.h"
#include "Collision.h"

LevelBoss::LevelBoss() :
	Level()
{

}

LevelBoss::~LevelBoss(){

}

void LevelBoss::load(){
	Log(DEBUG) << "Loading level boss...";

	Game::instance().getAudioHandler().changeMusic("assets/audio/Tema_Boss_02.wav");

	// Loading the tile/tilemap.
	this->tileMap = new TileMap("assets/maps/levelBoss.tmx");

	// Setting the level width/height.
	this->width = this->tileMap->getMapWidth();
	this->height = this->tileMap->getMapHeight();
	SDL_Rect bounds = {0, 0, (int)this->width, (int)this->height};
	this->quadTree = new QuadTree(0, bounds);

	this->background = Game::instance().getResources().get("assets/images/lv1_background.png");

	// Getting information from lua script.
	LuaScript luaLevel1("lua/Level1.lua");
	const std::string pathPlayerSpriteSheet = luaLevel1.unlua_get<std::string>(
		"level.player.spriteSheet");
	const std::string pathBackgroundAudio = luaLevel1.unlua_get<std::string>(
		"level.audio.background");
	const std::string pathEnemy = luaLevel1.unlua_get<std::string>("level.enemy");

	// Changing the music.
	Game::instance().getAudioHandler().changeMusic(pathBackgroundAudio);

	// Loading the player and the camera.
	Player* lPlayer = new Player(this->tileMap->getInitialX(), this->tileMap->getInitialY(), pathPlayerSpriteSheet);
	Camera* lCamera = new Camera(lPlayer); 

	this->playerHud = new PlayerHUD(lPlayer);

	Boss* lBoss = new Boss(1200, 684.0, "assets/images/boss_sheet.png", lPlayer);
	lBoss->getAnimation()->changeAnimation(0,0,1,false,0.0);
	
	// Test text.
	// Text* text = new Text(200.0, 900.0, "assets/fonts/KGFeeling22.ttf", 50, "dauphine");
	// addEntity(text);

	// Finally, setting the player, the boss and the camera.
	setPlayer(lPlayer);
	setBoss(lBoss);
	setCamera(lCamera);

	Game::instance().getFade().fadeOut(0, 0.002);
}

void LevelBoss::unload(){
	Log(DEBUG) << "\tUnloading level boss...";

	cleanEntities();
	clearEnemies();
	clearDocuments();
}

void LevelBoss::update(const double dt_){

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

	if(this->boss->x < this->player->x + 10 && this->boss->x > this->player->x - 10){
		this->boss->sawPlayer = true;
	}

	// Updating the HUD.
	this->playerHud->update();

	// Updating the boss.
	this->boss->update(dt_);

	// Updating the camera.
	this->camera->update();

	if(this->boss->life <= 0){
		this->player->reachedLevelEnd = true;
	}

	// Set next level if end is reached.
	if(this->player->reachedLevelEnd){
		Game::instance().setState(Game::GStates::VICTORY);
		return;
	}

	// Updating the potion/boss collision.
	for(auto potion : this->player->potions){
		if(Collision::rectsCollided(potion->getBoundingBox(), this->boss->getBoundingBox())){
			if(potion->activated){
				this->boss->life--;
				potion->activated = false;
			}
		}
	}

	// Updating the player attack/boss collision.
	if(Collision::rectsCollided(this->player->getBoundingBox(), this->boss->getBoundingBox())){
		if(this->player->isCurrentState(Player::PStates::ATTACK) || this->player->isCurrentState(Player::PStates::ATTACKMOVING)
			|| this->player->isCurrentState(Player::PStates::ATTACKJUMPING)){
			if(this->boss->hasShield && this->player->canAttack){
				this->boss->hasShield = false;
				this->player->canAttack = false;
			}
			else if(this->player->canAttack){
				this->boss->life -= 1;
				this->player->canAttack = false;
			}
		}
	}

	Log(DEBUG) << "Boss life: " << this->boss->life;

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

void LevelBoss::render(){
	const int cameraX = this->camera->getClip().x;
	const int cameraY = this->camera->getClip().y;

	this->background->render(0, 0);

	// Render the tiles in the TileMap.
	this->tileMap->render(cameraX, cameraY);

	this->playerHud->render();

	this->boss->render(cameraX, cameraY);

	// Render all the entities in the list.
	for(auto entity : this->entities){
        entity->render(cameraX, cameraY);
	}

	// Document text image
	for(auto document : this->documents){
		document->render(cameraX, cameraY);
		if(document->shouldRender){
			document->renderDocumentText();
		}
	}
}

