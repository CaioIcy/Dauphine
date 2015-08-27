#include "BStateIcePrision.h"
#include "Logger.h"
#include "Sprite.h"
#include "Game.h"
#include "Collision.h"

double prisionTime = 0.0;

void BStateIcePrision::enter(){
	// Log(DEBUG) << "STATE ICE PRISION BOSS";
	this->boss->power = Game::instance().getResources().get("assets/images/ice_prision.png");
	this->boss->powerAnimation->changeWidthHeight(340,1020);
	this->boss->powerAnimation->changeAnimation(0, 0, 2, false, 0.5);
	this->boss->vx = 0;
	this->boss->vy = 0;
	this->boss->powerIsActivated = true;
	this->boss->powerX = this->boss->player->x - 30; 
	this->boss->powerY = this->boss->player->y - 750;
	this->boss->powerFlip = SDL_FLIP_NONE;
}

void BStateIcePrision::exit(){
	this->boss->powerIsActivated = false;
	this->boss->player->isVulnerable = true;
	this->boss->powerAnimation->changeAnimation(0, 0, 1, false, 0);
	prisionTime = 0.0;
	this->boss->player->canMove = true;
}

void BStateIcePrision::update(const double dt_){
	prisionTime += dt_;
	if(prisionTime > 1){
		this->boss->powerAnimation->changeAnimation(2, 0, 1, false, 0);
		if(Collision::rectsCollided(this->boss->player->getBoundingBox(),  {(int)this->boss->powerX, 
		(int)this->boss->powerY, 340,1020})){
			if(this->boss->player->isVulnerable){
				this->boss->player->canMove = false;
				this->boss->player->isVulnerable = false;
				this->boss->player->vx = 0;
				this->boss->player->vy = 0;
				this->boss->player->getAnimation()->changeAnimation(4, 8, 1, false, 0);
			}
		}
	}
	if(prisionTime > 4){
		this->boss->changeState(Boss::BStates::IDLE);
	}
}

BStateIcePrision::BStateIcePrision(Boss* const boss_) :
	StateBoss(boss_)
{

}
