/*
 * Game.cpp
 *
 *  Created on: Jun 28, 2015
 *      Author: inferno
 */

#include <game/Game.h>
#include <Engine.hpp>

Game::Game(Engine* e, std::string path) {
  this->engine = e;
  data = new GameData(this);

  scenario = new Scenario(this, path);
  bsp = new Bsp(this, scenario->bspPath);
}

Game::~Game() {
  delete data;
}

void Game::step() {
  //Literally nothing atm
}

std::vector<Instance*> Game::getDraw() {
  //std::vector<gls::Model*> toDraw;
  return bsp->getDraw();
}
