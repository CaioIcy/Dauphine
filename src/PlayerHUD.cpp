#include "PlayerHUD.h"
#include "Game.h"
#include "Util.h"
#include "Logger.h"

PlayerHUD::PlayerHUD(Player* const player_):
	player(player_),
	potionsLeft(new Text(200.0, 25.0, "assets/fonts/maturasc.ttf", 50, "Potions: x"))
{
	for(unsigned int i = 0; i < TOTAL_HUD; i++){
		this->playerHudSprites[i] = nullptr;
	}

	initializeSprites();

	for(int i = 0; i < TOTAL_HUD; i++){
		this->canRenderHud[i] = true;
	}

}

PlayerHUD::~PlayerHUD(){
	if(this->potionsLeft != nullptr){
		delete this->potionsLeft;
		this->potionsLeft = nullptr;
	}
}

void PlayerHUD::update(){
	if(this->player != nullptr){
		switch(this->player->life){
			case 2:
				this->canRenderHud[3] = false;
				break;
			case 1:
				this->canRenderHud[2] = false;
				break;
			case 0:
				this->canRenderHud[1] = false;
				break;
			default :
				break;
		}

		this->potionsLeft->changeText(("Potions: "+ Util::toString(this->player->potionsLeft)).c_str());

	}
}

void PlayerHUD::render(){
	for(int i = 0; i < TOTAL_HUD; i++){
		if(this->canRenderHud[i]){
			this->playerHudSprites[i]->render(0, 0);
		}
	}

	if(this->potionsLeft != nullptr){
		this->potionsLeft->render(0, 0);
	}
	else {
		Log(WARN) << "Potions left HUD text is null";
	}
}

void PlayerHUD::initializeSprites(){
	this->playerHudSprites[0] = Game::instance().getResources().get("assets/images/hud/health_0.png");
	this->playerHudSprites[1] = Game::instance().getResources().get("assets/images/hud/health_33.png");
	this->playerHudSprites[2] = Game::instance().getResources().get("assets/images/hud/health_66.png");
	this->playerHudSprites[3] = Game::instance().getResources().get("assets/images/hud/health_99.png");
	this->playerHudSprites[4] = Game::instance().getResources().get("assets/images/hud/hud_no_health.png");	
}
