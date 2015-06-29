/*
 * GLSL Program loader
 * Author: pat
 *
 * Created on May 11, 2015, 2:49 PM
 */

#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <sstream>

#include <vector>
#include <string.h>

#include "display/shader/Program.h"
#include "display/texture/Texture.h"
#include "util/Tson.h"

class GameData;

namespace gls {
  class Shader {
  public:
    std::string path;
    Program* program;
    Texture** textures; uint tSize;
    Shader(std::string path, Program* program, Texture** textures, uint tSize);
  };

  Shader* openShader(const std::string file, GameData* gd);
}
#endif  /* SHADER_H */

