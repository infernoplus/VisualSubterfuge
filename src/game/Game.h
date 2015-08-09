/*
 * Game.h
 *
 *  Created on: Jun 28, 2015
 *      Author: inferno
 */

#ifndef GAME_H_
#define GAME_H_

#include "game/GameData.h"
#include "game/scenario/Scenario.h"
#include "game/bsp/Bsp.h"

class Engine;

class Game {
public:
  Engine* engine;

  GameData* data;

  Scenario* scenario;
  Bsp* bsp;

  Game(Engine* e, std::string path);
  virtual ~Game();

  void test();

  void step();
  std::vector<Instance*> getDraw();
};

#endif /* GAME_H_ */
