/*
 * Render.h
 *
 *  Created on: Dec 9, 2014
 *      Author: inferno
 */

#ifndef RENDER_H_
#define RENDER_H_

#include <stdio.h>
#include <string>
#include <fstream>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <vector>
#include <string.h>

#include "display/model/Model.h"

class Engine;
class Display;
class Game;

class Render {
public:
	Display* display;

	GLuint gVBO = 0;
	GLuint gIBO = 0;

	Render(Display* d);
	virtual ~Render();

	bool init();

	void render();
	void close();

private:
	void initTestRender();
	void doTestRender();
//	void useShader(std::string);
//	bool compileShaders();
//	std::vector<std::string> getShaderFilesLinux();
//	std::string openShaderFileLinux(std::string file);
//	int compileShader(std::string vert, std::string frag);
//	void printProgramLog( GLuint program );
//	void printShaderLog( GLuint shader );
//	bool ends_with(std::string const & value, std::string const & ending);
};

#endif /* RENDER_H_ */
