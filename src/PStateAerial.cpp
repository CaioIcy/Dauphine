#include "PStateAerial.h"
#include "Logger.h"
#include "Game.h"

void PStateAerial::enter(){
    this->box.x = 58;
    this->box.y = 72;
    this->box.w = 130;
    this->box.h = 145;

	this->player->getAnimation()->changeAnimation(4, 3, 14, false, 1.4);
	this->player->isGrounded = false;

    Game::instance().getAudioHandler().addSoundEffect("assets/audio/FX_NADINE/FALL_NADINE_01.wav");
}

void PStateAerial::exit(){
    this->player->isClimbing = false;
}

void PStateAerial::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){

	// Idle
    if(this->player->isGrounded){
    	this->player->changeState(Player::PStates::IDLE);
    	return;
    }

    if(keyStates_[GameKeys::LATTACK]){
        this->player->changeState(Player::PStates::ATTACKJUMPING);
        return;
    }

	// Gravity
	this->player->applyGravity();

	// Move (while on air)
    this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);
}

PStateAerial::PStateAerial(Player* const player_) :
	StatePlayer(player_)
{

}
