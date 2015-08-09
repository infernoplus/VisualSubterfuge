/*
 * Scenario.h
 *
 *  Created on: Aug 9, 2015
 *      Author: inferno
 */

#ifndef SCENARIO_H_
#define SCENARIO_H_

#include "util/Tson.h"

class Game;

class Scenario {
public:
  Game* game;

  std::string path;
  std::string name;

  std::string bspPath;

  tsn::TsonObject* data;

  Scenario(Game* game, std::string path);
  virtual ~Scenario();
};

#endif /* SCENARIO_H_ */
