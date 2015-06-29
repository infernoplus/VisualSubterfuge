//============================================================================
// Name        : SlowEngine
// Author      : Patrick Moriarty - Inferno
// Version     :
// Copyright   : Copyright Patrick Moriarty 2015 - Don't steal this nerds.
// Description : Flexible c++ game engine.
//============================================================================

#include "Engine.hpp"

#define uint unsigned int

int main(int argc, char *argv[]) {
	Engine e = Engine{argc, argv};
	int r  = e.run();
	return r;
}


//TODO: refactor includes, focus on including apis to the cpp. Stuff like log.h can be re-re-refactored lol.
//TODO: EXCEPTIONS

//TODO: gls is a populatd namespace aaaaaaaaaaaaaaaaaaaaaaa

//TODO: ADD SAVE TO MODEL EDITING

//TODO: IMPROVE EDITOR

//TODO: USE ACTUAL SHADERS IN FILE
