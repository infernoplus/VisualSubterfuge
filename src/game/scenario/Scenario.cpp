/*
 * Scenario.cpp
 *
 *  Created on: Aug 9, 2015
 *      Author: inferno
 */

#include <game/scenario/Scenario.h>
#include <game/Game.h>

Scenario::Scenario(Game* game, std::string path) {
  this->game = game;
  this->path = path;

  data = game->data->getTson(path);
  name = data->getValue("name")->getString();
  bspPath = data->getValue("bsp")->getString();
}

Scenario::~Scenario() {
  // TODO Auto-generated destructor stub
}

