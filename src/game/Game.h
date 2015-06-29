/*
 * Game.h
 *
 *  Created on: Jun 28, 2015
 *      Author: inferno
 */

#ifndef GAME_H_
#define GAME_H_

#include "game/GameData.h"

class Engine;

class Game {
public:
  Engine* engine;

  GameData* data;

  gls::Model* testUno;
  gls::Model* testDos;

  Game(Engine* e);
  virtual ~Game();

  void test();

  void step();
  std::vector<gls::Model*> getDraw();
};

#endif /* GAME_H_ */
