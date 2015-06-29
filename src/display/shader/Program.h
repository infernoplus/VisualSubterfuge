/*
 * GLSL Program loader
 * Author: pat
 *
 * Created on May 11, 2015, 2:49 PM
 */

#ifndef PROGRAM_H
#define PROGRAM_H

#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <string.h>

#include "display/texture/lodepng.h"

class GameData;

namespace gls {
  class Program {
  public:
    //File path
    std::string path;
    //OpenGL bind data
    bool bound;
    GLuint program;
    Program(std::string path);
    Program();

    void bindData();

  private:
    GLuint compileShader(std::string vert, std::string frag);
    void printShaderLog( GLuint shader );
    void printProgramLog( GLuint gProgramdId );
  };

  Program* openProgram(const std::string file, GameData* gd);
}
#endif  /* PROGRAM_H */

