/*
 * Display.h
 *
 *  Created on: Dec 9, 2014
 *      Author: inferno
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <iostream>
#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_timer.h>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "display/Render.h"

class Engine;

class Display {
public:
	Engine* engine;
	Render *render;

	bool exit;
	SDL_Thread *thread;

	SDL_Window* gWindow = NULL;
	SDL_GLContext gContext;

	Display(Engine* e);
	virtual ~Display();

	static int displayWrapper(void *ptr);
	int display();
	bool initSDL();
	bool initRender();
	void stop();
	void close();
};

#endif /* DISPLAY_H_ */
