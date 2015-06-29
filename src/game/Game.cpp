/*
 * Game.cpp
 *
 *  Created on: Jun 28, 2015
 *      Author: inferno
 */

#include <game/Game.h>
#include <Engine.hpp>

Game::Game(Engine* e) {
  this->engine = e;
  data = new GameData(this);

  test();
}

Game::~Game() {
  delete data;
}


void Game::test() {
  testUno = data->getModel("basic.gls");
  testDos = data->getModel("basic.gls");
}


void Game::step() {
  //Literally nothing atm
}

std::vector<gls::Model*> Game::getDraw() {
  std::vector<gls::Model*> toDraw;
  toDraw.push_back(testUno); //toDraw.push_back(testDos);
  return toDraw;
}
