/* 
 * GLSL Program loader
 * Author: pat
 *
 * Created on May 11, 2015, 2:49 PM
 */

#ifndef SHADER_HPP
#define	SHADER_HPP

#include <fstream>
#include <sstream>

#include <vector>
#include <string.h>

#include "display/texture/Texture.hpp"
#include "display/shader/Program.hpp"
#include "util/Tson.hpp"

#define uint unsigned int

namespace gls {
  class Shader {
  public:
    Program* program;
    Texture** textures; uint tSize;
    Shader(Program* program, Texture** textures, uint tSize) {
      this->program = program;
      this->textures = textures;
      this->tSize = tSize;
    }
  };
  
  Shader* openShader(const std::string file) {
    tsn::TsonObject* tson = tsn::openTson(file);
    
    gls::Program* program = gls::openProgram(tson->getValue("glsl")->getString());
    uint tSize = tson->getArray("textures")->size();
    Texture** textures = new Texture*[tSize];
    for(uint i=0;i<tSize;i++)
      textures[i] = gls::openTexture(tson->getArray("textures")->getString(i));
    Shader* shader = new Shader(program, textures, tSize);
    
    delete tson;
    
    return shader;
  }
}
#endif	/* SHADER_HPP */

