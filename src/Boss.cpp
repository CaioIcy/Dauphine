#include "Boss.h"
#include "Logger.h"
#include "Game.h"
#include <cmath>

#include "BStateIdle.h"
#include "BStateAttack.h"
#include "BStateShield.h"
#include "BStateTeleport.h"
#include "BStateIcePrision.h"
#include "BStateMagicProjectile.h"

#include "Window.h"

#define ADD_STATE_EMPLACE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass(this))
#define ADD_STATE_INSERT(stateEnum, stateClass) this->statesMap.insert(std::make_pair<BStates, StateBoss*>(stateEnum, new stateClass(this)));

double timePasssed = 0;

Boss::Boss(const double x_, const double y_, const std::string& path_, Player* const player_) :
	DynamicEntity(x_, y_, path_),	
	potionsLeft(3),
	sawPlayer(false),
	potions(),
	life(8),
	hasShield(false),
	canWalk(true),
	player(player_),
	powerAnimation(nullptr),
	powerX(0.0),
	powerY(0.0),
	powerIsActivated(false),
	power(nullptr),
	powerClip{0,0,0,0},
	powerFlip(SDL_FLIP_NONE),
	shieldAnimation(nullptr),
	shield(nullptr),
	shieldClip{0,0,0,0},
	currentState(nullptr),
	animation(nullptr),
	statesMap(),
	dead(false)
{
	initializeStates();

	this->isRight = true;

	this->speed = 400.0;

	this->width = 360;
	this->height = 360;

	this->animation = new Animation(0, 0, this->width, this->height, 7, false);
	this->powerAnimation = new Animation(0, 0, 0, 0, 0, false);
	this->shieldAnimation = new Animation(0, 0, 340, 340, 6, false);
	this->shield = Game::instance().getResources().get("assets/images/shield.png");
	this->shieldAnimation->changeAnimation(0,0,3,false,1);
	this->currentState = this->statesMap.at(IDLE);
	this->currentState->enter();

	if(this->player == nullptr){
		Log(WARN) << "Passing a null player to the Boss.";
	}
}

Boss::~Boss(){
	if(this->animation != nullptr){
		delete this->animation;
		this->animation = nullptr;
	}
	
	if(this->powerAnimation != nullptr){
		delete this->powerAnimation;
		this->powerAnimation = nullptr;
	}

	if(this->shieldAnimation != nullptr){
		delete this->shieldAnimation;
		this->shieldAnimation = nullptr;
	}

	if(this->currentState != nullptr){
		this->currentState->exit();
	}

	this->player = nullptr;

	destroyStates();
}

void Boss::update(const double dt_){
	
	timePasssed += dt_;

	scoutPosition(dt_);

	this->animation->update(this->animationClip, dt_);
	this->powerAnimation->update(this->powerClip, dt_);
	this->shieldAnimation->update(this->shieldClip, dt_);

	updateBoundingBox();

	const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
	handleCollision(detections);

	updatePosition(dt_);

	this->currentState->update(dt_);

    for(auto potion : this->potions){
        if(!potion->activated){
            // Delete potion.
        }
        potion->update(dt_);
    }
}

void Boss::render(const double cameraX_, const double cameraY_){

	const double dx = this->x - cameraX_;
	const double dy = this->y - cameraY_;
	
	if(this->sprite != nullptr){
		SDL_RendererFlip flip = getFlip();

		if(flip == SDL_FLIP_HORIZONTAL){
			this->sprite->render(dx - 120, dy, &this->animationClip, false, 0.0, nullptr, flip);
		}
		else{
			this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, flip);
		}
	}
	
		// Shield render.
	if(this->hasShield){
		SDL_RendererFlip flip = getFlip();
		if(flip == SDL_FLIP_HORIZONTAL){
			this->shield->render(dx, dy, &this->shieldClip);
		}
		else{
			this->shield->render(dx -120, dy, &this->shieldClip);
		}
	}

	const double pdx = this->powerX - cameraX_;
	const double pdy = this->powerY - cameraY_;

	if(this->power != nullptr && this->powerIsActivated){
		
		if(this->powerFlip == SDL_FLIP_HORIZONTAL){
			this->power->render(pdx - this->powerClip.w, pdy, &this->powerClip, false, 0.0, nullptr, this->powerFlip);
		}
		else{
			this->power->render(pdx, pdy, &this->powerClip, false, 0.0, nullptr, this->powerFlip);
		}
	}

    for (auto potion : this->potions) {
        potion->render(cameraX_, cameraY_);
    }
}

void Boss::initializeStates(){
	// Initialize all the states in Boss here.
	ADD_STATE_INSERT(IDLE,				BStateIdle);
	ADD_STATE_INSERT(ATTACK,			BStateAttack);
	ADD_STATE_INSERT(SHIELD,			BStateShield);
	ADD_STATE_INSERT(TELEPORT,			BStateTeleport);
	ADD_STATE_INSERT(ICEPRISION,		BStateIcePrision);
	ADD_STATE_INSERT(MAGICPROJECTILE,	BStateMagicProjectile);
}

void Boss::destroyStates(){
	// Delete all the states in Boss here.
	std::map<BStates, StateBoss*>::const_iterator it;
	for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){
		delete it->second;
	}
}

void Boss::changeState(const BStates state_){
	this->currentState->exit();
	this->currentState = this->statesMap.at(state_);
	this->currentState->enter();
}

void Boss::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){
	if(detections_.at(CollisionSide::SOLID_TOP)){ 
		this->vy = 0.0;
	}
	if(detections_.at(CollisionSide::SOLID_BOTTOM)){		
			this->nextY -= fmod(this->nextY, 64.0) - 16.0;
			this->vy = 0.0;
	}
	if(detections_.at(CollisionSide::SOLID_LEFT)){
		this->nextX = this->x;
		this->vx = 0.0;
	}
	if(detections_.at(CollisionSide::SOLID_RIGHT)){
		this->nextX = this->x;
		this->vx = -0.001;
	}
}

void Boss::usePotion(const int strength_, const int distance_){
    if(this->potionsLeft > 0){
        this->potionsLeft--;
        const double potionX = ((this->isRight) ? this->boundingBox.x + this->boundingBox.w : this->boundingBox.x);
        Potion* potion = new Potion(potionX , this->y, "assets/images/potion.png", strength_, this->vx, distance_, this->isRight);
        this->potions.push_back(potion);
    }
}

Animation *Boss::getAnimation(){
	return (this->animation);
}

void Boss::setDead(bool isDead_){
	this->dead = isDead_;
}

bool Boss::isDead(){
	return this->dead;
}

void Boss::updateBoundingBox(){
	this->boundingBox.x = (int) this->x + 40;
	this->boundingBox.y = (int) this->y + 40;
	this->boundingBox.w = 150;
	this->boundingBox.h = 200;
}
