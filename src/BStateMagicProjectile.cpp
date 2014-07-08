#include "BStateMagicProjectile.h"
#include "Logger.h"
#include "Sprite.h"
#include "Collision.h"
#include <cmath>

double projectileTime = 0.0;
double mpX = 0;
double mpY = 0;
double hypotenuse = 0;

void BStateMagicProjectile::enter(){
	Log(DEBUG) << "STATE MAGIC PROJECTILE BOSS";
	this->boss->power = new Sprite("res/images/projectile.png");
	this->boss->powerAnimation->changeWidthHeight(50,50);
	this->boss->powerAnimation->changeAnimation(0, 0, 4, false, 0.5);
	this->boss->vx = 0;
	this->boss->vy = 0;
	this->boss->powerX = this->boss->x + 50;
	this->boss->powerY = this->boss->y + 150;
	this->boss->powerIsActivated = true;
	/*
	this.xToFollow = player.x - this.x;
	this.yToFollow = player.y - this.y;
	this.hypotenuse = Math.sqrt( (this.xToFollow*this.xToFollow)+(this.yToFollow*this.yToFollow) );
	this.hypotenuse = (this.hypotenuse==0) ? 1 : this.hypotenuse;
	this.xToFollow /= this.hypotenuse;
	this.yToFollow /= this.hypotenuse;
	*/
	mpX = this->boss->player->getBoundingBox().x + 50 - this->boss->getBoundingBox().x;
	mpY = this->boss->player->getBoundingBox().y + 50 - this->boss->getBoundingBox().y;
	hypotenuse = sqrt((mpX*mpX)+(mpY*mpY));
	hypotenuse = (hypotenuse==0) ? 1 : hypotenuse;
	mpX /= hypotenuse;
	mpY /= hypotenuse;
}

void BStateMagicProjectile::exit(){
	this->boss->powerIsActivated = false;
	projectileTime = 0.0;
	mpX = 0;
	mpY = 0;
	hypotenuse = 0;
}

void BStateMagicProjectile::update(const double dt_){
	projectileTime += dt_;
	this->boss->powerX += mpX * 15;
	this->boss->powerY += mpY * 15;

	if(Collision::rectsCollided(this->boss->player->getBoundingBox(), {(int)this->boss->powerX, 
		(int)this->boss->powerY, 50, 50})){
			this->boss->player->life--;
			this->boss->changeState(Boss::BStates::IDLE);
	}
	if(projectileTime>3){
		this->boss->changeState(Boss::BStates::IDLE);
	}
}

BStateMagicProjectile::BStateMagicProjectile(Boss* const boss_) :
	StateBoss(boss_)
{

}
