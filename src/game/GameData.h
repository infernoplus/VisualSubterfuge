/*
 * GameData.h
 *
 *  Created on: Jun 28, 2015
 *      Author: inferno
 */

#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include "fstream"

#include "display/model/Model.h"
#include "display/shader/Shader.h"
#include "display/shader/Program.h"
#include "display/texture/Texture.h"

#define DATA "/data/"

class Engine;
class Game;

class GameData {
public:
  Game* game;

  //Game <Asset> cache
  std::vector<gls::Model*> models;
  std::vector<gls::Shader*> shaders;
  std::vector<gls::Program*> programs;
  std::vector<gls::Texture*> textures;

  bool rebind;

  GameData(Game* g);
  virtual ~GameData();

  //Get <Asset> methods
  gls::Model* getModel(std::string path);
  gls::Shader* getShader(std::string path);
  gls::Program* getProgram(std::string path);
  gls::Texture* getTexture(std::string path);

  void bindData();
};

#endif /* GAMEDATA_H_ */
