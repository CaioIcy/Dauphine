#include "FadeScreen.h"
#include "Game.h"
#include "Logger.h"

FadeScreen::FadeScreen() :
	fadeImage(Game::instance().getResources().get("assets/images/black_screen.png")),
	fadeHandler(new FadeHandler(this->fadeImage))
{

}

FadeScreen::~FadeScreen() {
	if(this->fadeHandler != nullptr){
		delete this->fadeHandler;
		this->fadeHandler = nullptr;
	}
}

void FadeScreen::update(const double dt_){
	fadeHandler->update(dt_);
}

void FadeScreen::render(){
	if(this->fadeImage != nullptr){
		this->fadeImage->render(0, 0, nullptr, true);
	}
}

bool FadeScreen::isFaded(){
	bool faded = false;

	const int currentPercentage = this->fadeHandler->getCurrentPercentage();
	if(currentPercentage == 1.0){
		faded = true;
	}

	return faded;
}

void FadeScreen::fadeOut(const double percentage_, const double time_){
	this->fadeHandler->fadeOut(percentage_, time_);
}
void FadeScreen::fadeIn(const double percentage_, const double time_){
	this->fadeHandler->fadeIn(percentage_, time_);
}

