/*
 * Render.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: inferno
 */

#include <Engine.hpp>
#include <display/Render.h>
#include <display/Display.h>

#include <dirent.h>

#include "display/model/Model.hpp"

Render::Render(Display* d) {
	display = d;
}

Render::~Render() {
	// TODO Auto-generated destructor stub
}

bool Render::init() {
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  initTestRender();

  return true;
}

gls::Model glsModel;
GLuint* vbo;
GLuint vba;

void Render::initTestRender() {
  cmd::log("Loading test model...");
  std::string in = "/home/inferno/out.gls";
  glsModel = gls::openModel(in);
  glGenVertexArrays(1, &vba);
  glBindVertexArray(vba);
  vbo = new GLuint[glsModel.gSize];
  glGenBuffers(glsModel.gSize, vbo);
  for(uint i=0;i<glsModel.gSize;i++) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
    glBufferData(GL_ARRAY_BUFFER, glsModel.dSize[i]*sizeof(float), glsModel.data[i], GL_STATIC_DRAW);
  }
  cmd::log("Done...");
}

float r = 0.0f;
void Render::doTestRender() {
  r += 0.0004f;
  GLuint prg = glsModel.shaders[0]->program->program;
  glUseProgram(prg); //TODO: using first shader and nothing else

  GLuint uniformModel = glGetUniformLocation(prg, "model");
  GLuint uniformView = glGetUniformLocation(prg, "view");
  GLuint uniformProjection = glGetUniformLocation(prg, "projection");
  GLuint uniformMvp = glGetUniformLocation(prg, "mvp");

  glm::mat4 projection = glm::perspective(70.0f, ((float)display->screenWidth)/((float)display->screenHeight), 2.0f, 16384.0f);
  glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

  glm::vec3 eye = glm::vec3(sin(r*0.33)*4096.0f,4096.0f,cos(r*0.33)*4096.0f);
  glm::vec3 center = glm::vec3(0.0f,0.0f,0.0f);
  glm::vec3 up = glm::vec3(0.0f,0.0f,1.0f);

  glm::mat4 view = glm::lookAt(eye, center, up);
  glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));

  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

  glm::mat4 mvp = projection * view * model;

  glUniformMatrix4fv(uniformMvp, 1, GL_FALSE, glm::value_ptr(mvp));

  glsModel.shaders[0]->textures[0]->bind(prg, 0);

  for(uint i=0;i<glsModel.gSize;i++) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_TRUE,
            36,
            (void*)0
    );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_TRUE,
            36,
            (void*)12
    );
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
            2,
            3,
            GL_FLOAT,
            GL_TRUE,
            36,
            (void*)24
    );

    glDrawElements(GL_TRIANGLES, glsModel.iSize[i], GL_UNSIGNED_INT, glsModel.indices[i]);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
  }

  glUseProgram(0);
}

void Render::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
  glClearColor(0.33f, 0.33f, 0.33f, 1.0f); // Set background color to grey

  doTestRender();

  glFlush();
}

void Render::close() {

}

//void Render::useShader(string name) {
//	for(int i=0;i<shaders.size();i++)
//		if(shaders.data()[i].name == name) {
//			shaders.data()[i].useShader();
//			return;
//		}
//}
//
//bool Render::initGL() {
//	//Success flag
//	bool success = true;
//
//  //Initialize clear color
//  glClearColor( 0.f, 0.f, 0.f, 1.f );
//
//  //VBO data
//  GLfloat vertexData[] =
//  {
//    -0.5f, -0.5f,
//     0.5f, -0.5f,
//     0.5f,  0.5f,
//    -0.5f,  0.5f
//  };
//
//  //IBO data
//  GLuint indexData[] = { 0, 1, 2, 3 };
//
//  //Create VBO
//  glGenBuffers( 1, &gVBO );
//  glBindBuffer( GL_ARRAY_BUFFER, gVBO );
//  glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );
//
//  //Create IBO
//  glGenBuffers( 1, &gIBO );
//  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
//  glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );
//
//	return success;
//}
//
////TODO: engine crashes without warn/error if it can't read shaders
//bool Render::compileShaders() {
//	//Get a list of all the shaders
//	vector<string> files = getShaderFilesLinux();
//
//	//Compile each shader and link it up
//	for(int i=0;i<files.size();i++) {
//		if(ends_with(files.data()[i], ".vert")) {
//			string vertFile = files.data()[i];
//			string fragFile = vertFile.substr(0,vertFile.length()-5) + ".frag";
//
//			display->engine->log->log("Compiling shaders " + vertFile + " and " + fragFile);
//
//			string vert = openShaderFileLinux("./data/glsl/" + vertFile);
//			string frag = openShaderFileLinux("./data/glsl/" + fragFile);
//
//			//std::cout << "out :: " << vert << " \n\n " << frag << "\n end \n";
//
//			int program = compileShader(vert, frag);
//			if(program == -1)
//				return false;
//
//			string name = vertFile.substr(0,vertFile.length()-5);
//			shaders.push_back(Shader{program,name});
//		}
//	}
//
//	return true;
//}
//
//vector<string> Render::getShaderFilesLinux() {
//	vector<string> files;
//
//	DIR *dir = opendir("./data/glsl");
//	struct dirent *read = NULL;
//
//	while(read = readdir(dir)) {
//		string file(read->d_name);
//		if(file != "." && file != ".." && (ends_with(file, ".frag") || ends_with(file, ".vert")))
//			files.push_back(file);
//	}
//
//	closedir(dir);
//
//	return files;
//}
//
//string Render::openShaderFileLinux(string file) {
//	std::ifstream in(file);
//	std::string contents((std::istreambuf_iterator<char>(in)),
//	    std::istreambuf_iterator<char>());
//	in.close();
//	return contents;
//}
//
//int Render::compileShader(string vert, string frag) {
//	//Success flag
//	bool success = true;
//
//	//Generate program
//	int gProgramID = glCreateProgram();
//
//	//Create vertex shader
//	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
//
//	//Get vert source
//	const char *vertSource = vert.c_str();
//
//	//Set vertex source
//	glShaderSource( vertexShader, 1, &vertSource, NULL );
//
//	//Compile vertex source
//	glCompileShader( vertexShader );
//
//	//Check vertex shader for errors
//	GLint vShaderCompiled = GL_FALSE;
//	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &vShaderCompiled );
//	if( vShaderCompiled != GL_TRUE )
//	{
//		printf( "Unable to compile vertex shader %d!\n", vertexShader );
//		printShaderLog( vertexShader );
//		success = false;
//	}
//	else
//	{
//		//Attach vertex shader to program
//		glAttachShader( gProgramID, vertexShader );
//
//
//		//Create fragment shader
//		GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
//
//		//Get fragment source
//		const char *fragSource = frag.c_str();
//
//		//Set fragment source
//		glShaderSource( fragmentShader, 1, &fragSource, NULL );
//
//		//Compile fragment source
//		glCompileShader( fragmentShader );
//
//		//Check fragment shader for errors
//		GLint fShaderCompiled = GL_FALSE;
//		glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled );
//		if( fShaderCompiled != GL_TRUE )
//		{
//			printf( "Unable to compile fragment shader %d!\n", fragmentShader );
//			printShaderLog( fragmentShader );
//			success = false;
//		}
//		else
//		{
//			//Attach fragment shader to program
//			glAttachShader( gProgramID, fragmentShader );
//
//
//			//Link program
//			glLinkProgram( gProgramID );
//
//			//Check for errors
//			GLint programSuccess = GL_TRUE;
//			glGetProgramiv( gProgramID, GL_LINK_STATUS, &programSuccess );
//			if( programSuccess != GL_TRUE )
//			{
//				printf( "Error linking program %d!\n", gProgramID );
//				printProgramLog( gProgramID );
//				success = false;
//			}
//		}
//	}
//	return success ? gProgramID : -1;
//}
//
//void Render::printShaderLog( GLuint shader )
//{
//	//Make sure name is shader
//	if( glIsShader( shader ) )
//	{
//		//Shader log length
//		int infoLogLength = 0;
//		int maxLength = infoLogLength;
//
//		//Get info string length
//		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );
//
//		//Allocate string
//		char* infoLog = new char[ maxLength ];
//
//		//Get info log
//		glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
//		if( infoLogLength > 0 )
//		{
//			//Print Log
//			printf( "%s\n", infoLog );
//		}
//
//		//Deallocate string
//		delete[] infoLog;
//	}
//	else
//	{
//		printf( "Name %d is not a shader\n", shader );
//	}
//}
//
//void Render::printProgramLog( GLuint program )
//{
//	//Make sure name is shader
//	if( glIsProgram( program ) )
//	{
//		//Program log length
//		int infoLogLength = 0;
//		int maxLength = infoLogLength;
//
//		//Get info string length
//		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );
//
//		//Allocate string
//		char* infoLog = new char[ maxLength ];
//
//		//Get info log
//		glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
//		if( infoLogLength > 0 )
//		{
//			//Print Log
//			printf( "%s\n", infoLog );
//		}
//
//		//Deallocate string
//		delete[] infoLog;
//	}
//	else
//	{
//		printf( "Name %d is not a program\n", program );
//	}
//}
//
//inline bool Render::ends_with(std::string const & value, std::string const & ending)
//{
//    if (ending.size() > value.size()) return false;
//    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
//}
