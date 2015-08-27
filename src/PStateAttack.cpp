#include "PStateAttack.h"
#include "Logger.h"
#include "Game.h"

void PStateAttack::enter(){
	this->box.x = 58;
	this->box.y = 75;
	this->box.w = 140;
	this->box.h = 160;

	this->player->getAnimation()->changeAnimation(1, 7, 14, false, 0.466);

	Game::instance().getAudioHandler().addSoundEffect("assets/audio/FX_NADINE/WOOSH_NADINE_02.wav");
}

void PStateAttack::exit(){

	this->player->canAttack = true;

}

void PStateAttack::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
	((void)keyStates_); // Unused.

	if(this->player->getAnimation()->getCurrentFrame() == 14){
		this->player->changeState(Player::PStates::IDLE);
	}
}

PStateAttack::PStateAttack(Player* const player_) :
	StatePlayer(player_)
{

}
