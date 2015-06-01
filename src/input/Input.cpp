/*
 * Input.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: inferno
 */

#include <Engine.hpp>
#include <input/Input.h>

Input::Input(Engine* e) {
	engine = e;
	//Enable text input
	SDL_StartTextInput();
}

Input::~Input() {
	// TODO Auto-generated destructor stub
}

void Input::step() {
	handleInput(e);
}

void Input::handleInput(SDL_Event e) {
	//Handle events on queue
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			engine->stop();
		}
		//Handle keypress with current mouse position
		else if( e.type == SDL_TEXTINPUT )
		{
			int x = 0, y = 0;
			SDL_GetMouseState( &x, &y );
			handleKeys( e.text.text[ 0 ], x, y );
		}
		else if(e.type == SDL_MOUSEMOTION) {
			handleMove(e.motion.x, e.motion.y);
		}
		else if( e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
			handleClick(e.button.button, e.type, e.button.x, e.button.y);
		}
	}

}

void Input::handleMove( int x, int y ) {

}

void Input::handleClick( unsigned char btn, int type, int x, int y ) {

}

void Input::handleKeys( unsigned char key, int x, int y )
{
	//Toggle quad
	if( key == 'q' )
	{
		engine->stop();
	}
}

void Input::close() {
	SDL_StopTextInput();
}
