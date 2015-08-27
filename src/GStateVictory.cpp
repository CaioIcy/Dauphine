#include "GStateVictory.h"
#include "Game.h"
#include "Logger.h"

GStateVictory::GStateVictory() :
	victoryImage(nullptr),
	passedTime(0.0),
	lifeTime(0.0)
{

}

GStateVictory::~GStateVictory(){

}

void GStateVictory::load(){
	Log(DEBUG) << "Loading victory...";


    this->victoryImage = Game::instance().getResources().get("assets/images/victory.png");
	this->lifeTime = 5.0;

	// Changing the music.
	Game::instance().getAudioHandler().changeMusic("assets/audio/Tema_Victory_01.wav");
}

void GStateVictory::unload(){
	Log(DEBUG) << "\tUnloading victory...";
	cleanEntities();

	this->passedTime = 0.0;
	this->lifeTime = 0.0;

}

void GStateVictory::update(const double dt_){
	this->passedTime += dt_;

	if(this->passedTime >= this->lifeTime){
		Game::instance().setState(Game::GStates::CREDITS);
		return;
	}
}

void GStateVictory::render(){
	if(this->victoryImage != nullptr){
		this->victoryImage->render(0, 0, nullptr, true);
	}
	else{
		Log(WARN) << "No image set for the victory screen!";
	}
}
