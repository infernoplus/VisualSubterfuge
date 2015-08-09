/*
 * Bsp.h
 *
 *  Created on: Aug 9, 2015
 *      Author: inferno
 */

#ifndef BSP_H_
#define BSP_H_

#include "util/Tson.h"
#include "display/model/Instance.h"

class Game;

class Bsp {
public:
  Game* game;

  std::string path;
  std::string name;

  tsn::TsonObject* data;

  std::vector<Instance*> geometry;

  Bsp(Game* game, std::string path);
  virtual ~Bsp();

  void build();

  std::vector<Instance*> getDraw();
};

#endif /* BSP_H_ */
