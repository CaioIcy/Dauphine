#include "BStateTeleport.h"
#include "Game.h"
#include "Collision.h"
#include "Logger.h"

double tptime = 0;
double pX = 0;
double pY = 0;
int powerCollisionWidth = 0;
int powerCollisionHeight = 0;
int offset = 33;
bool right;
int direction = 0;

void BStateTeleport::enter(){
	// Log(DEBUG) << "STATE TELEPORT BOSS";
	this->boss->power = Game::instance().getResources().get("assets/images/laser_sheet.png");
	this->boss->powerAnimation->changeWidthHeight(700, 340);
	this->boss->powerAnimation->changeAnimation(0, 0, 3, false, 0.5);
	this->boss->player->isVulnerable = true;
}

void BStateTeleport::exit(){
	this->boss->powerIsActivated = false;
	this->boss->player->isVulnerable = true;
	this->boss->powerAnimation->changeAnimation(0, 0, 1, false, 0);
	powerCollisionWidth = 0;
	powerCollisionHeight = 0;
	tptime = 0.0;
}

void BStateTeleport::update(const double dt_){
	tptime += dt_;
	
	if(tptime < 3){
		this->boss->vx =0;
		this->boss->vy =0;
	}
	else if(tptime >= 3 && tptime <= 3.05){
		this->boss->getAnimation()->changeAnimation(0, 0, 1, false, 0);
		this->boss->vx = 0;
		if(this->boss->player->isRight){
			this->boss->x = this->boss->player->x - 150 - 50;
			this->boss->y = this->boss->player->y;
		}
		else{
			this->boss->x = this->boss->player->x + 150 + 50;
			this->boss->y = this->boss->player->y;
		}
		this->boss->isRight = this->boss->player->isRight;
		pX = this->boss->x;
		pY = this->boss->y;
		if(!this->boss->isRight){
			this->boss->powerFlip = SDL_FLIP_HORIZONTAL;
			right = false;
		}
		else{
			this->boss->powerFlip = SDL_FLIP_NONE;
			right = false;
		}
	}
	else if(tptime > 3.05 && tptime < 4){
		this->boss->x = pX;
		this->boss->y = pY;
		if(right){
			this->boss->isRight = false;
			direction = 0;
		}
		else{
			this->boss->isRight = true;
			direction = 1;
		}
	}
	if(tptime >= 4 && tptime <= 5){
		if(this->boss->powerAnimation->getCurrentFrame() == 1){
			powerCollisionWidth = 101;
			powerCollisionHeight = 30;
		}
		else if(this->boss->powerAnimation->getCurrentFrame() == 2){
			powerCollisionWidth = 539;
			powerCollisionHeight = 117;
		}
		else{
			powerCollisionWidth = 665;
			powerCollisionHeight = 262;
		}
		if(this->boss->player->isRight){
			this->boss->powerX = pX;
			this->boss->powerY = pY;
		}
		else{
			this->boss->powerX = pX;
			this->boss->powerY = pY;
		}
		if(tptime >= 4.5){
			this->boss->powerAnimation->changeAnimation(2, 0, 1, false, 0);
			powerCollisionWidth = 665;
			powerCollisionHeight = 262;
		}
		this->boss->powerIsActivated = true;
		if(Collision::rectsCollided(this->boss->player->getBoundingBox(), {(int)this->boss->powerX - direction * 665, 
		(int)this->boss->powerY + offset, direction * 665, 262})){
			if(this->boss->player->isVulnerable){
				this->boss->player->life--;
				this->boss->player->isVulnerable = false;
			}
		}
	}
	else if(tptime > 5){
		this->boss->changeState(Boss::BStates::IDLE);
	}
}

BStateTeleport::BStateTeleport(Boss* const boss_) :
	StateBoss(boss_)
{

}
