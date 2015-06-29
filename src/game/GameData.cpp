/*
 * GameData.cpp
 *
 *  Created on: Jun 28, 2015
 *      Author: inferno
 */

#include <game/GameData.h>
#include <game/Game.h>
#include <Engine.hpp>

GameData::GameData(Game* g) {
  game = g;
}

GameData::~GameData() {
  //TODO: DELETE ALL CACHED DATA
}

gls::Model* GameData::getModel(std::string path) {
  std::string full = game->engine->root + DATA + path;
  for(uint i=0;i<models.size();i++) {
    if(models[i]->path == full)
      return models[i];
  }
  cmd::log("Loading model file '" + full + "' ...");
  gls::Model* m = gls::openModel(full, this);
  models.push_back(m);
  rebind = true;
  return m;
}

gls::Shader* GameData::getShader(std::string path) {
  std::string full = game->engine->root + DATA + path;
  for(uint i=0;i<shaders.size();i++) {
    if(shaders[i]->path == full)
      return shaders[i];
  }
  cmd::log("Loading shader file '" + full + "' ...");
  gls::Shader* s = gls::openShader(full, this);
  shaders.push_back(s);
  return s;
}

gls::Program* GameData::getProgram(std::string path) {
  std::string full = game->engine->root + DATA + path;
  for(uint i=0;i<programs.size();i++) {
    if(programs[i]->path == full)
      return programs[i];
  }
  cmd::log("Loading program file '" + full + "' ...");
  gls::Program* p = gls::openProgram(full, this);
  programs.push_back(p);
  rebind = true;
  return p;
}

gls::Texture* GameData::getTexture(std::string path) {
  std::string full = game->engine->root + DATA + path;
  for(uint i=0;i<textures.size();i++) {
    if(textures[i]->path == full)
      return textures[i];
  }
  cmd::log("Loading texture file '" + full + "' ...");
  gls::Texture* t = gls::openTexture(full, this);
  textures.push_back(t);
  rebind = true;
  return t;
}

void GameData::bindData() {
  if(!rebind)
    return;
  for(uint i=0;i<models.size();i++)
    models[i]->bindData();
  for(uint i=0;i<programs.size();i++)
    programs[i]->bindData();
  for(uint i=0;i<textures.size();i++)
    textures[i]->bindData();
  rebind = false;
}
