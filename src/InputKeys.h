#ifndef INCLUDE_INPUTKEYS_H
#define INCLUDE_INPUTKEYS_H

#include <cstdint>

enum GameKeys : uint8_t { 
	UP = 0,
	LEFT,
	RIGHT,
	DOWN,
	ROLL,
	
	SPACE,
	
	CROUCH,
	AIM,

	ACTION,
	LATTACK,
	NLATTACK,

	ITEMS,
	
	ESCAPE,
	MAX
};

#endif //INCLUDE_INPUTKEYS_H
