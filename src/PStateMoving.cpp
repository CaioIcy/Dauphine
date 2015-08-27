#include "PStateMoving.h"
#include "Logger.h"
#include "Game.h"

#define THROW_STRENGTH 30
#define THROW_DISTANCE 400

void PStateMoving::enter(){
    this->box.x = 58;
    this->box.y = 72;
    this->box.w = 130;
    this->box.h = 160;

    this->player->getAnimation()->changeAnimation(4,2,9,false,0.7);

    Game::instance().getAudioHandler().addSoundEffect("assets/audio/FX_NADINE/RUNNING_NADINE_01.wav");
}

void PStateMoving::exit(){

}

void PStateMoving::handleInput(const std::array<bool, GameKeys::MAX> keyStates_){
    // Aerial
    if(!this->player->isGrounded){
        this->player->changeState(Player::PStates::AERIAL);
        return;     
    }

    // Jump
    if(keyStates_[GameKeys::SPACE] && this->player->isGrounded){
        this->player->jump();
        this->player->isGrounded = false;
        return;
    }

    if(keyStates_[GameKeys::ACTION]){
        // Game::instance().getAudioHandler().addSoundEffect("assets/audio/FX_NADINE/WOOSH_NADINE_03.wav");
        this->player->usePotion(THROW_STRENGTH, THROW_DISTANCE);
        return;
    }

    if(keyStates_[GameKeys::LATTACK]){
        this->player->changeState(Player::PStates::ATTACKMOVING);
        return;
    }

    // // Crouch
    // if(keyStates_[GameKeys::CROUCH]){
    //     this->player->changeState(Player::PStates::CROUCHING);
    //     return;
    // }

    this->player->move(keyStates_[GameKeys::LEFT], keyStates_[GameKeys::RIGHT]);

    if(keyStates_[GameKeys::ROLL]){
        this->player->changeState(Player::PStates::ROLLING);
        return;
    }

    // Idle
    if(this->player->vx < 1.0 && this->player->vx > (-1.0)){
        this->player->changeState(Player::PStates::IDLE);
        return;
    }

    // Attack
    if(keyStates_[GameKeys::LATTACK]){
        this->player->changeState(Player::PStates::ATTACK);
        return;
    }
}

PStateMoving::PStateMoving(Player* const player_) :
    StatePlayer(player_)
{

}
