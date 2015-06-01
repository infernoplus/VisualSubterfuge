/*
 * Display.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: inferno
 */

#include <Engine.hpp>
#include <display/Display.h>

Display::Display(Engine* e) {
	engine = e;

	screenWidth = 1024; screenHeight = 768;

	tExit = false; tClosed = false;
    thread = SDL_CreateThread(displayWrapper, "DisplayThread", this);

    if (NULL == thread) {
        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
        return;
    }
}

Display::~Display() {
	// TODO Auto-generated destructor stub
}

int Display::displayWrapper(void *ptr) {
	Display* self = static_cast<Display*>(ptr);
	return self->display();
}

int Display::display() {
	if(!initRender())  { std::cout << "Failed to start renderer!\n"; engine->stop(); return 1; }
	if(!initSDL()) { std::cout << "Failed to start SDL!\n"; engine->stop(); return 1; }

	int width; int height;
	SDL_GetWindowSize(gWindow, &width, &height);

	while(!tExit) {
		//Render scene
		render->render();

		//Update screen
		SDL_GL_SwapWindow( gWindow );
		SDL_Delay(33); //TODO: what?
	}
	tClosed = true;
	return 0;
}

bool Display::initRender() {
  //Success flag
  bool success = true;
  render = new Render(this);
  return success;
}

bool Display::initSDL() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

		//Create window
		gWindow = SDL_CreateWindow( (engine->title + "  Engine").c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext( gWindow );
			if( gContext == NULL )
			{
				printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize GLEW
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if( glewError != GLEW_OK )
				{
					printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
				}

				//Use Vsync
				if( SDL_GL_SetSwapInterval( 1 ) < 0 )
				{
					printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
				}

				//Initialize renderer
				if( !render->init() )
				{
					printf( "Unable to initialize Renderer!\n" );
					success = false;
				}
			}
		}
	}

	return success;
}

void Display::stop() {
	//Stop run
	tExit = true;
}

void Display::close() {
	//Destroys renderer
	render->close();
	delete render;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
