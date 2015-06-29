/*
 * GLSL Program loader
 * Author: pat
 *
 * Created on May 11, 2015, 2:49 PM
 */

#include <display/shader/Shader.h>

#include <game/GameData.h>

  gls::Shader::Shader(std::string path, Program* program, Texture** textures, uint tSize) {
    this->path = path;
    this->program = program;
    this->textures = textures;
    this->tSize = tSize;
  }

  gls::Shader* gls::openShader(const std::string path, GameData* gd) {
    tsn::TsonObject* tson = tsn::openTson(path);

    gls::Program* program = gd->getProgram(tson->getValue("glsl")->getString());
    uint tSize = tson->getArray("textures")->size();
    Texture** textures = new Texture*[tSize];
    for(uint i=0;i<tSize;i++)
      textures[i] = gd->getTexture(tson->getArray("textures")->getString(i));
    Shader* shader = new Shader(path, program, textures, tSize);

    delete tson;

    return shader;
  }

