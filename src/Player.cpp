#include "Player.h"
#include "Game.h"
#include "Logger.h"
#include "Configuration.h"
#include "LuaScript.h"
#include <cmath>
#include <cfloat>

#include "PStateIdle.h"
#include "PStateAerial.h"
#include "PStateMoving.h"
#include "PStateRolling.h"
#include "PStateCrouching.h"
#include "PStateAiming.h"
#include "PStateMovingCrouch.h"
#include "PStateAttack.h"
#include "PStateAttackMoving.h"
#include "PStateAttackJumping.h"
#include "PStateHit.h"
#include "PStateClimbing.h"
#include "PStateDead.h"

#include "Window.h"

#define ADD_STATE_EMPLACE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass(this))
#define ADD_STATE_INSERT(stateEnum, stateClass) this->statesMap.insert(std::make_pair<PStates, StatePlayer*>(stateEnum, new stateClass(this)));

Player::Player(const double x_, const double y_, const std::string& path_) :
    DynamicEntity(x_, y_, path_),
    potionsLeft(3),
    maxPotions(3),
    crosshair(new Crosshair(0.0, 0.0, "assets/images/alvo.png")),
    life(3),
    attackStrength(50),
    canAttack(true),
    currentItem(PItems::POTION),
    closestEnemyIsRight(true),
    isVulnerable(true),
    invulnerableTime(0),
    canMove(true),
    animation(nullptr),
    currentState(nullptr)
{
    initializeStates();

    LuaScript luaPlayer("lua/Player.lua");
    this->width = luaPlayer.unlua_get<int>("player.dimensions.width");
    this->height = luaPlayer.unlua_get<int>("player.dimensions.height");

    // Shouldn't be here?
    this->animation = new Animation(0, 3, this->width, this->height, 11, false);

    if(this->sprite != nullptr){
        this->currentState = this->statesMap.at(IDLE);
        this->currentState->enter();
    }
    else{
        Log(WARN) << "No sprite set for the player! Null sprite.";
    }

}

Player::~Player(){
    if(this->currentState != nullptr){
        this->currentState->exit();
        this->currentState = nullptr;
    }

    if(this->animation != nullptr){
        delete this->animation;
        this->animation = nullptr;
    }

    destroyStates();
}

void Player::update(const double dt_){
    std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

    if(this->canMove){
        this->currentState->handleInput(keyStates);
    }

    Game::instance().clearKeyFromInput(GameKeys::ACTION);

    scoutPosition(dt_);

    updateBoundingBox();

    const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
    handleCollision(detections);

    updatePosition(dt_);

    this->animation->update(this->animationClip, dt_);

    for(auto potion : this->potions){
        if(!potion->activated){
            // Delete potion.
        }
        potion->update(dt_);
    }

    if(!this->isVulnerable){
        this->invulnerableTime += dt_;
        if(this->invulnerableTime >= 1){
            this->invulnerableTime = 0;
            this->isVulnerable = true;
            this->canAttack = true;
        }
    }

    if(this->isClimbing && !isCurrentState(PStates::CLIMBING)){
        changeState(PStates::CLIMBING);
    }

}

void Player::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){
    if(detections_.at(CollisionSide::SOLID_TOP)){ 
        Log(DEBUG) << "COLLIDED_TOP";
        this->vy = 0.0;
    }
    if(detections_.at(CollisionSide::SOLID_BOTTOM)){
        if(isCurrentState(PStates::AERIAL) || isCurrentState(PStates::ATTACKJUMPING) 
            || isCurrentState(PStates::HITED)  || isCurrentState(PStates::CLIMBING) ||  
            isCurrentState(PStates::DEAD)){
            const double magic = 32.0;
            const double aerialToIdleCorrection = 8.0;

            this->nextY -= fmod(this->nextY, 64.0) - magic + aerialToIdleCorrection;
            this->vy = 0.0;
            if(!isCurrentState(PStates::DEAD)){
                changeState(PStates::IDLE);
            }
        }
    }
    else{
        if(!isCurrentState(PStates::AERIAL) && !isCurrentState(PStates::ATTACKJUMPING)
            && !isCurrentState(PStates::CLIMBING) && !isCurrentState(PStates::DEAD)){
            changeState(PStates::AERIAL);
        }
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

void Player::render(const double cameraX_, const double cameraY_){

    const double dx = this->x - cameraX_;
    const double dy = this->y - cameraY_;

    ///////////////////////////////////////////////////////////////////////////////////////////
    // // Actual.
    // SDL_Rect actualRect = {(int)dx, (int)dy, (int)this->width, (int)this->height};
    // SDL_SetRenderDrawColor( Window::getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    // SDL_RenderFillRect(Window::getRenderer(), &actualRect);

    // Bounding box.
    // SDL_Rect boundingBox2 = {(int)(this->boundingBox.x - cameraX_), (int)(this->boundingBox.y - cameraY_), (int)this->boundingBox.w, (int)this->boundingBox.h};
    // SDL_SetRenderDrawColor( Window::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    // SDL_RenderFillRect(Window::getRenderer(), &boundingBox2);
    /////////////////////////////////////////////////////////////////////////////////////

    if(this->sprite != nullptr){
        SDL_RendererFlip flip = getFlip();

        if(flip == SDL_FLIP_HORIZONTAL)
            this->sprite->render(dx - 100, dy, &this->animationClip, false, 0.0, nullptr, flip);
        else
            this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, flip);
    }

    if(this->crosshair != nullptr){
        this->crosshair->render(cameraX_, cameraY_);
    }

    for (auto potion : this->potions) {
        potion->render(cameraX_, cameraY_);
    }

}

void Player::usePotion(const int strength_, const int distance_){
    if(this->potionsLeft > 0){
        this->potionsLeft--;
        const double potionX = ((this->isRight) ? this->boundingBox.x + this->boundingBox.w : this->boundingBox.x);
        Potion* potion = new Potion(potionX , this->y, "assets/images/explosion_with_potion.png", strength_, this->vx, distance_, this->isRight);
        this->potions.push_back(potion);
    }
}

void Player::addPotions(const unsigned int quantity_){
    if(this->potionsLeft + quantity_ > this->maxPotions){
        this->potionsLeft = this->maxPotions;
    }
    else{
        this->potionsLeft += quantity_;
    }
}

void Player::initializeStates(){
    // Initialize all the states in Player here.
    ADD_STATE_INSERT(IDLE,         PStateIdle);
    ADD_STATE_INSERT(MOVING,       PStateMoving);
    ADD_STATE_INSERT(AERIAL,       PStateAerial);
    ADD_STATE_INSERT(ROLLING,      PStateRolling);
    ADD_STATE_INSERT(CROUCHING,    PStateCrouching);
    ADD_STATE_INSERT(AIMING,       PStateAiming);
    ADD_STATE_INSERT(MOVINGCROUCH, PStateMovingCrouch);
    ADD_STATE_INSERT(ATTACK,       PStateAttack);
    ADD_STATE_INSERT(ATTACKMOVING, PStateAttackMoving);
    ADD_STATE_INSERT(ATTACKJUMPING,PStateAttackJumping);
    ADD_STATE_INSERT(HITED,        PStateHit);
    ADD_STATE_INSERT(CLIMBING,     PStateClimbing);
    ADD_STATE_INSERT(DEAD,         PStateDead);
}

void Player::destroyStates(){
    // Delete all the states in Player here.
    std::map<PStates, StatePlayer*>::const_iterator it;
    for(it = this->statesMap.begin(); it != this->statesMap.end(); it++){
        delete it->second;
    }
}

void Player::changeState(const PStates state_){
    this->currentState->exit();
    this->currentState = this->statesMap.at(state_);
    this->currentState->enter();
}

Animation* Player::getAnimation(){
    return (this->animation);
}

bool Player::isCurrentState(const PStates state_){
    return (this->currentState == this->statesMap.at(state_));
}

void Player::updateBoundingBox(){
    this->boundingBox.x = (int) this->nextX + this->currentState->box.x;
    this->boundingBox.y = (int) this->nextY + this->currentState->box.y;
    this->boundingBox.w = this->currentState->box.w;
    this->boundingBox.h = this->currentState->box.h;
}

bool Player::isDead(){
    return (this->life <= 0);
}
