#include "GStateContinue.h"
#include "LuaScript.h"
#include "Game.h"
#include "Util.h"
#include <string>

GStateContinue::GStateContinue() :
	background(nullptr),
	selector(nullptr),
	passedTime(0.0),
	currentSelection(Selection::SLOT_1),
	selectorXPosition(562),
	selectorYPosition {500,610,723}
{
	this->slot1 = new Text(615.0, 520.0, "assets/fonts/maturasc.ttf", 45, "Empty Slot");
	this->slot2 = new Text(615.0, 630.0, "assets/fonts/maturasc.ttf", 45, "Empty Slot");
	this->slot3 = new Text(615.0, 730.0, "assets/fonts/maturasc.ttf", 45, "Empty Slot");
}

GStateContinue::~GStateContinue(){
	if(this->slot1 != nullptr){
		delete this->slot1;
		this->slot1 = nullptr;
	}

	if(this->slot2 != nullptr){
		delete this->slot2;
		this->slot2 = nullptr;
	}

	if(this->slot3 != nullptr){
		delete this->slot3;
		this->slot3 = nullptr;
	}
}

void GStateContinue::load(){
	Log(DEBUG) << "Loading Continue Screen...";
	
	if(Game::instance().getSaves().isSaved(SLOT_1)){
		
		const int levelFromSave = Game::instance().getSaves().getSavedLevel(SLOT_1);

		const std::string currentLevel = "Level " + Util::toString(levelFromSave);
		
		if(levelFromSave == -1)
			this->slot1->changeText("Empty Slot");
		else
			this->slot1->changeText(currentLevel.c_str());
	}

	else{
		this->slot1->changeText("Empty Slot");
	}


	if(Game::instance().getSaves().isSaved(SLOT_2)){
		
		const int levelFromSave = Game::instance().getSaves().getSavedLevel(SLOT_2);

		const std::string currentLevel = "Level " + Util::toString(levelFromSave);
		
		if(levelFromSave == -1)
			this->slot2->changeText("Empty Slot");
		else
			this->slot2->changeText(currentLevel.c_str());
	}
	else{
		this->slot2->changeText("Empty Slot");
	}


	if(Game::instance().getSaves().isSaved(SLOT_3)){
		
		const int levelFromSave = Game::instance().getSaves().getSavedLevel(SLOT_3);

		const std::string currentLevel = "Level " + Util::toString(levelFromSave);
			
		if(levelFromSave == -1)
			this->slot3->changeText("Empty Slot");
		else
			this->slot3->changeText(currentLevel.c_str());
	}
	else{
		this->slot3->changeText("Empty Slot");
	}

	LuaScript luaMenu("lua/Continue.lua");
	const std::string pathBackground = luaMenu.unlua_get<std::string>("continue.images.background");
	const std::string pathSelector = luaMenu.unlua_get<std::string>("continue.images.selector");

	this->background = Game::instance().getResources().get(pathBackground);
    this->selector = Game::instance().getResources().get(pathSelector);

	this->selector->setWidth(410);
	this->selector->setHeight(102);

    this->currentSelection = Selection::SLOT_1;

    Game::instance().getFade().fadeOut(0, 0.002);
}

void GStateContinue::unload(){
	Log(DEBUG) << "\tUnloading menu...";
	cleanEntities();
}

void GStateContinue::update(const double dt_){
	this->passedTime += dt_;

	handleSelectorMenu();

	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();
	if(keyStates[GameKeys::ESCAPE] == true){
		Game::instance().setState(Game::GStates::MENU);
	}

}

void GStateContinue::render(){

	if(this->background != nullptr){
		this->background->render(0, 0, nullptr, true);

		this->selector->render(selectorXPosition, selectorYPosition[currentSelection], nullptr, false, 0.0, nullptr, SDL_FLIP_NONE);
	
		this->slot1->render(0, 0);
		this->slot2->render(0, 0);
		this->slot3->render(0, 0);
	}
	else{
		Log(WARN) << "No image set to display on the menu!";
	}
}

void GStateContinue::handleSelectorMenu(){
	std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

	const double selectorDelayTime = 0.2;

	if(keyStates[GameKeys::LATTACK] == true){
		if(this->passedTime >= selectorDelayTime){
			Game::instance().setState(Game::GStates::MENU);
		}
	}
	if(keyStates[GameKeys::DOWN] == true || keyStates[GameKeys::RIGHT] == true){
		if(this->passedTime >= selectorDelayTime){
			if(currentSelection < (Selection::TOTAL - 1)){
				currentSelection++;
			}
			else{
				currentSelection = Selection::SLOT_1;
			}
			this->passedTime = 0.0;
		}
	}
	else if(keyStates[GameKeys::UP] == true || keyStates[GameKeys::LEFT] == true){
		if(this->passedTime >= selectorDelayTime){
			if(currentSelection > Selection::SLOT_1){
				currentSelection--;
			}
			else{
				currentSelection = (Selection::TOTAL - 1);
			}
			this->passedTime = 0.0;
		}
	}
	else if(currentSelection == Selection::SLOT_1 && keyStates[GameKeys::SPACE] == true){
		Game::instance().currentSlot = SLOT_1;

		switch(Game::instance().getSaves().getSavedLevel(Selection::SLOT_1)){
			Game::instance().currentSlot = Selection::SLOT_1;
			case 1:
				Game::instance().transitionTo = Game::GStates::LEVEL_ONE;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 2:
				Game::instance().transitionTo = Game::GStates::LEVEL_TWO;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 3:
				Game::instance().transitionTo = Game::GStates::LEVEL_THREE;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 4:
				Game::instance().transitionTo = Game::GStates::LEVEL_FOUR;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 5:
				Game::instance().transitionTo = Game::GStates::LEVEL_FIVE;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 6:
				Game::instance().transitionTo = Game::GStates::LEVEL_BOSS;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			default:
				break;
		}

	}
	else if(currentSelection == Selection::SLOT_2 && keyStates[GameKeys::SPACE] == true){
		Game::instance().currentSlot = SLOT_2;

		switch(Game::instance().getSaves().getSavedLevel(Selection::SLOT_2)){
			Game::instance().currentSlot = Selection::SLOT_2;
			case 1:
				Game::instance().transitionTo = Game::GStates::LEVEL_ONE;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 2:
				Game::instance().transitionTo = Game::GStates::LEVEL_TWO;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 3:
				Game::instance().transitionTo = Game::GStates::LEVEL_THREE;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 4:
				Game::instance().transitionTo = Game::GStates::LEVEL_FOUR;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 5:
				//CHANGE THIS AFTER CREATING FIFTH LEVEL
				Game::instance().transitionTo = Game::GStates::LEVEL_FIVE;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 6:
				Game::instance().transitionTo = Game::GStates::LEVEL_BOSS;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			default:
				break;
		}

	}
	else if(currentSelection == Selection::SLOT_3 && keyStates[GameKeys::SPACE] == true){
		Game::instance().currentSlot = SLOT_3;

		switch(Game::instance().getSaves().getSavedLevel(Selection::SLOT_3)){
			Game::instance().currentSlot = Selection::SLOT_3;
			case 1:
				Game::instance().transitionTo = Game::GStates::LEVEL_ONE;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 2:
				Game::instance().transitionTo = Game::GStates::LEVEL_TWO;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 3:
				Game::instance().transitionTo = Game::GStates::LEVEL_THREE;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 4:
				Game::instance().transitionTo = Game::GStates::LEVEL_FOUR;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 5:
				//CHANGE THIS AFTER CREATING FIFTH LEVEL
				Game::instance().transitionTo = Game::GStates::LEVEL_FIVE;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			case 6:
				Game::instance().transitionTo = Game::GStates::LEVEL_BOSS;
				Game::instance().setState(Game::instance().transitionTo);
				break;
			default:
				break;
		}

	}

}
