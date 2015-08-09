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


//TODO: refactor includes

//TODO: EXCEPTIONS

//TODO: gls is a populatd namespace aaaaaaaaaaaaaaaaaaaaaaa

//TODO: IMPROVE EDITOR

//TODO: USE ACTUAL SHADERS IN FILE

//TODO: Shadow mapping implemenation

//TODO: Camera controls

//TODO: Improve shader -> program bindings

//TODO: Index program uniform bindings

//TODO: Create safe render order and inbetween frames

//TODO: Safe loading and unloading of map files

//TODO: Command line/console

//TODO: Proper deletion/unloading of files. Check for memory leaks.
