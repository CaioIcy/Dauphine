#include "PStateIdle.h"
#include "Logger.h"
#include "Game.h"

#define THROW_STRENGTH 30
#define THROW_DISTANCE 400

void PStateIdle::enter(){
	
	this->box.x = 58;
	this->box.y = 72;
	this->box.w = 130;
	this->box.h = 160;

	// this->box.x = (int)this->player->getWidth() / 4 - 33;
	// this->box.y = (int)this->player->getHeight() / 3.5;
	// this->box.w = (int)this->player->getWidth() / 1.7;
	// this->box.h = (int)this->player->getHeight() / 3.5;

	this->player->getAnimation()->changeAnimation(0, 0, 26, false, 2.6);
	this->player->isGrounded = true;
}

void PStateIdle::exit(){

}

void PStateIdle::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	// Aerial
	if(!this->player->isGrounded){
		this->player->changeState(Player::PStates::AERIAL);
		return;
	}

	this->player->slowVx();

	// Jump
	if(keyStates_[GameKeys::SPACE]){
		this->player->jump();
		this->player->isGrounded = false;
		return;
	}

	// Attack
	if(keyStates_[GameKeys::LATTACK]){
		this->player->changeState(Player::PStates::ATTACK);
		return;
	}

    if(keyStates_[GameKeys::ACTION]){
    	// Game::instance().getAudioHandler().addSoundEffect("assets/audio/FX_NADINE/FX_AAAAAHH.wav");
        this->player->usePotion(THROW_STRENGTH, THROW_DISTANCE);
        return;
    }

	// // Crouch
	// if(keyStates_[GameKeys::CROUCH]){
	// 	this->player->changeState(Player::PStates::CROUCHING);
	// 	return;
	// }

	// Move
	if(keyStates_[GameKeys::LEFT] || keyStates_[GameKeys::RIGHT]){
		this->player->changeState(Player::PStates::MOVING);
		return;
	}

	// Roll
	if(keyStates_[GameKeys::ROLL]){
		this->player->changeState(Player::PStates::ROLLING);
		return;
	}

	// Aim
	if(keyStates_[GameKeys::AIM]){
		this->player->changeState(Player::PStates::AIMING);
		return;
	}

}

PStateIdle::PStateIdle(Player* const player_) :
	StatePlayer(player_)
{

}
