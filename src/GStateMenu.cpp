#include "GStateMenu.h"
#include "LuaScript.h"
#include "Game.h"

#include <string>

GStateMenu::GStateMenu() :
	shouldIgnore(false),
	menuImage(nullptr),
	menuSelector(nullptr),
	attractModeBg(nullptr),
	attractMode(nullptr),
	passedTime(0.0),
	currentSelection(Selection::NEWGAME),
	selectorXPositionLeft {610, 635, 635, 645},
	selectorYPositionLeft {560, 625, 690, 755},
	selectorXPositionRight {880, 855, 855, 845},
	selectorYPositionRight {560, 625, 690, 755},
	attractHeightSize(600),
	attractChangeSpeed(1),
	attractClip{0, 0, 0, this->attractHeightSize},
	shwingAnimation(nullptr),
	shwingIsActivated(true),
	shwing(nullptr),
	shwingClip {0,0,0,0}
{

}

GStateMenu::~GStateMenu(){
	if(this->shwingAnimation != nullptr){
		delete this->shwingAnimation;
		this->shwingAnimation = nullptr;
	}
}

void GStateMenu::load(){
	Log(DEBUG) << "Loading menu...";

	// Changing the music.
	Game::instance().clearKeyFromInput(GameKeys::ESCAPE);

	Game::instance().getAudioHandler().changeMusic("assets/audio/menu.mid");

	LuaScript luaMenu("lua/Menu.lua");
	const std::string pathTitleScreen = luaMenu.unlua_get<std::string>("menu.images.titleScreen");
	const std::string pathCursor = luaMenu.unlua_get<std::string>("menu.images.cursor");

    this->menuImage = Game::instance().getResources().get(pathTitleScreen);
    this->menuSelector = Game::instance().getResources().get(pathCursor);
    this->attractModeBg = Game::instance().getResources().get("assets/images/title_background.png");
    this->attractMode = Game::instance().getResources().get("assets/images/attract.png");
    this->attractClip.w = this->attractMode->getWidth();
    this->shwingAnimation = new Animation(0, 0, 795, 360, 3, false);
    this->shwing = Game::instance().getResources().get("assets/images/shwing_sheet.png");
    this->shwingAnimation->ANIMATION_LIMIT = 2;

    Game::instance().getFade().fadeOut(0, 0.002);
}

void GStateMenu::unload(){
	Log(DEBUG) << "\tUnloading menu...";
	this->attractClip.y = 0;
	cleanEntities();
}

void GStateMenu::update(const double dt_){
	this->passedTime += dt_;

	handleSelectorMenu();

	this->shwingAnimation->update(this->shwingClip, dt_);	

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();
	if(keyStates[GameKeys::ESCAPE] == true){
		Game::instance().stop();
	}

	if(this->shwingIsActivated){
		 this->shwingAnimation->changeAnimation(0,0,12,false,2);
		 this->shwingIsActivated = false;
	}

}

void GStateMenu::render(){

	if(this->passedTime>10){
		this->attractModeBg->render(0, 0, nullptr, true);
		this->attractMode->render(0, 0, &this->attractClip, true);
		shouldIgnore = true;
		if(this->attractClip.y < (int)this->attractMode->getHeight() - this->attractHeightSize){
			this->attractClip.y += this->attractChangeSpeed;
		}
		else{
			//shwing->render(340,50,&this->shwingClip);
		}
		if(this->passedTime>75){
			this->passedTime = 0.0;
			this->attractClip.y = 0;
		}
	}
	else{
		if(this->menuImage != nullptr){
			this->menuImage->render(0, 0, nullptr, true);

			this->menuSelector->setWidth(50);

			this->menuSelector->render(selectorXPositionLeft[currentSelection],
				selectorYPositionLeft[currentSelection], nullptr, false, 0.0, nullptr, SDL_FLIP_NONE);

			this->menuSelector->render(selectorXPositionRight[currentSelection],
				selectorYPositionRight[currentSelection], nullptr, false, 0.0, nullptr, SDL_FLIP_HORIZONTAL);

		}
		else{
			Log(WARN) << "No image set to display on the menu!";
		}
	}

}

void GStateMenu::handleSelectorMenu(){
	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	const double selectorDelayTime = 0.2;

	if(keyStates[GameKeys::DOWN] == true || keyStates[GameKeys::RIGHT] == true){

		if(shouldIgnore){
			this->passedTime = 0.0;
			this->attractClip.y = 0;
			shouldIgnore = false;
			return;
		}

		if(this->passedTime >= selectorDelayTime){
			if(currentSelection < (Selection::TOTAL - 1)){
				currentSelection++;
			}
			else{
				currentSelection = Selection::NEWGAME;
			}
			
			this->passedTime = 0.0;
			this->attractClip.y = 0;
		}
	}
	else if(keyStates[GameKeys::UP] == true || keyStates[GameKeys::LEFT] == true){
		if(shouldIgnore){
			this->passedTime = 0.0;
			this->attractClip.y = 0;
			shouldIgnore = false;
			return;
		}

		if(this->passedTime >= selectorDelayTime){
			if(currentSelection > Selection::NEWGAME){
				currentSelection--;
			}
			else{
				currentSelection = (Selection::TOTAL - 1);
			}
			this->passedTime = 0.0;
			this->attractClip.y = 0;
		}
	}
	else if(currentSelection == Selection::NEWGAME && keyStates[GameKeys::SPACE] == true){
		if(shouldIgnore){
			this->passedTime = 0.0;
			this->attractClip.y = 0;
			shouldIgnore = false;
			return;
		}

		Game::instance().setState(Game::GStates::NEW_GAME);
		this->passedTime = 0.0;
		this->attractClip.y = 0;
	}

	else if(currentSelection == Selection::CONTINUE && keyStates[GameKeys::SPACE] == true){
		if(shouldIgnore){
			this->passedTime = 0.0;
			this->attractClip.y = 0;
			shouldIgnore = false;
			return;
		}

		Game::instance().setState(Game::GStates::CONTINUE);
		this->passedTime = 0.0;
		this->attractClip.y = 0;
	}

	else if(currentSelection == Selection::OPTIONS && keyStates[GameKeys::SPACE] == true){
		if(shouldIgnore){
			this->passedTime = 0.0;
			this->attractClip.y = 0;
			shouldIgnore = false;
			return;
		}

		Game::instance().setState(Game::GStates::OPTIONS);
		this->passedTime = 0.0;
		this->attractClip.y = 0;
	}

	else if(currentSelection == Selection::CREDITS && keyStates[GameKeys::SPACE] == true){
		if(shouldIgnore){
			this->passedTime = 0.0;
			this->attractClip.y = 0;
			shouldIgnore = false;
			return;
		}

		Game::instance().setState(Game::GStates::CREDITS);
		this->passedTime = 0.0;
		this->attractClip.y = 0;
	}
}
