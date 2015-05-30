/*
 * Input.h
 *
 *  Created on: Dec 8, 2014
 *      Author: inferno
 */

#ifndef INPUT_H_
#define INPUT_H_

#include <iostream>
#include <SDL2/SDL.h>

class Engine;

class Input {
public:
	Engine* engine;

	SDL_Event e;
	Input(Engine* e);
	virtual ~Input();

	void step();
	void handleInput(SDL_Event e);
	void handleMove( int x, int y );
	void handleClick( unsigned char btn, int type, int x, int y );
	void handleKeys( unsigned char key, int x, int y );

	void close();
};

#endif /* INPUT_H_ */
