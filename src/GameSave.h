#ifndef INCLUDE_GAMESAVE_H
#define INCLUDE_GAMESAVE_H

#include <fstream>
#include "Player.h"
#include "Enemy.h"

class GameSave {

	public:
		GameSave();

		void setSlot(int saveSelection);
		void createSave();
		void saveLevel(unsigned int level_, Player* player, std::vector <Enemy*> enemies, unsigned int slot_);
		int getSavedLevel(int continueSelection_);
		void getPlayerPosition(double& playerX_, double& playerY_, const int slot_);

		bool isEnemyDead(const int numEnemy_, const int slot_);

		bool isSaved(const int saveSlot_);

		std::string filePath;
		int saveSelection;
		unsigned int currentLevel;

		std::ofstream saveFile;
		std::ifstream continueFile;

		enum Selection : uint8_t {
			SLOT_1 = 0,
			SLOT_2,
			SLOT_3,
			TOTAL
		};

};

#endif //INCLUDE_GAMESAVE_H