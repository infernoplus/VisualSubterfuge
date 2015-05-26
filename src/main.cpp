/* 
 * File:   main.cpp
 * Author: pat
 *
 * Created on April 1, 2015, 11:49 AM
 */

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string.h>
#include <thread>
#include <math.h>
#include <vector>

#include "util/Util.hpp"
#include "util/Random.hpp"

#include "display/model/Model.hpp"
#include "display/shader/Shader.hpp"
#include "display/shader/Program.hpp"
#include "display/texture/Texture.hpp"
#include "util/Tson.hpp"

using namespace std;
namespace sc = std::chrono;

void glInit(int argc, char** arv); void display(); long getTime(); 

int fps = 0;
int frames = 0;

gls::Model glsModel;

Camera camera;

int tick = 1;

bool bExit = false;

int main(int argc, char** argv) {
    std::cout << "\n";
    std::cout << "Initializing threaded renderer...\n";
    std::thread dspThrd (glInit, argc, argv);
    
    std::cout << "Starting simulation...\n";
    long now = getTime(); long last = getTime();

    while(!bExit) {
        now = getTime();
        if(now - last > tick) {
            fps = frames;
            last = getTime();
        }
    }
    
    std::cout << "\nEnding simulation...";
    dspThrd.join();

    return 0;
}

GLuint vbo;
GLuint vba;
        
const int winSize = 1024;
void glInit(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitContextVersion(3,3);
  glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);
  glutInitWindowSize(winSize, winSize);
  glutInitWindowPosition(25, 25);
  glutCreateWindow("Loading...");
  glewExperimental = GL_TRUE;
  glewInit();
  glViewport (0, 0, winSize, winSize);
  
  std::cout << "Loading model...\n";
  string in = "/home/inferno/out.gls";
  glsModel = gls::openModel(in);

  glGenVertexArrays(1, &vba);
  glBindVertexArray(vba);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, glsModel.dSize[0]*sizeof(float), glsModel.data[0], GL_STATIC_DRAW);
  
    while(!bExit) {
        string pre;
        pre.assign("Test Program - ");
        pre.append(std::to_string(fps));
        glutSetWindowTitle(pre.c_str());
        frames++;
        display();
    }
}

float r = 0.0f;
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
    glClearColor(0.33f, 0.33f, 0.33f, 1.0f); // Set background color to grey
    
    r += 0.0004f;
    GLuint prg = glsModel.shaders[0]->program->program;
    glUseProgram(prg); //TODO: using first shader and nothing else
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glDepthRange(0.1f,128.0f);
    glClearDepth(1.0f);
    
    GLuint uniformModel = glGetUniformLocation(prg, "model");
    GLuint uniformView = glGetUniformLocation(prg, "view");
    GLuint uniformProjection = glGetUniformLocation(prg, "projection");
    GLuint uniformMvp = glGetUniformLocation(prg, "mvp");
    
    glm::mat4 projection = glm::perspective(70.0f, 1.0f, 1.0f, 12000.0f);
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
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, glsModel.dSize[i]*sizeof(float), glsModel.data[i], GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
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
    }
    
    glDisable(GL_DEPTH_TEST);
    glUseProgram(0);

    glFlush();
}

long getTime() {
    auto time = sc::system_clock::now();
    auto since_epoch = time.time_since_epoch();
    auto millis = sc::duration_cast<sc::milliseconds>(since_epoch);
    return millis.count();
}
