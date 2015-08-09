/*
 * GameData.h
 *
 *  Created on: Jun 28, 2015
 *      Author: inferno
 */

#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include "fstream"

#include "util/Tson.h"
#include "display/model/Model.h"
#include "display/shader/Shader.h"
#include "display/shader/Program.h"
#include "display/texture/Texture.h"
#include "util/coordinate/Vert3f.h"

#define DATA "/data/"

class Engine;
class Game;

class GameData {
public:
  Game* game;

  //Game <Asset> cache
  std::vector<tsn::TsonObject*> tsons;
  std::vector<gls::Model*> models;
  std::vector<gls::Shader*> shaders;
  std::vector<gls::Program*> programs;
  std::vector<gls::Texture*> textures;

  bool rebind;

  GameData(Game* g);
  virtual ~GameData();

  //Get <Asset> methods'
  tsn::TsonObject* getTson(std::string path);
  gls::Model* getModel(std::string path);
  gls::Shader* getShader(std::string path);
  gls::Program* getProgram(std::string path);
  gls::Texture* getTexture(std::string path);

  void bindData();
};

#endif /* GAMEDATA_H_ */
