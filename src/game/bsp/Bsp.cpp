/*
 * Bsp.cpp
 *
 *  Created on: Aug 9, 2015
 *      Author: inferno
 */

#include <game/bsp/Bsp.h>
#include <game/Game.h>

Bsp::Bsp(Game* game, std::string path) {
  this->game = game;
  this->path = path;

  data = game->data->getTson(path);
  name = data->getValue("name")->getString();

  build();
}

Bsp::~Bsp() {
  // TODO Auto-generated destructor stub
}

void Bsp::build() {
  int size = data->getValue("geoms")->getInt();
  for(int i=0;i<size;i++) {
    std::stringstream ss; ss << "geom"; ss << i;
    tsn::TsonObject* geom = data->getObject(ss.str());

    tsn::TsonArrayItf* posDat = geom->getArray("pos");
    tsn::TsonArrayItf* rotDat = geom->getArray("rot");
    tsn::TsonArrayItf* sclDat = geom->getArray("scl");

    Vert3f pos = Vert3f(posDat->getFloat(0), posDat->getFloat(1), posDat->getFloat(2));
    Vert3f rot = Vert3f(rotDat->getFloat(0), rotDat->getFloat(1), rotDat->getFloat(2));
    Vert3f scl = Vert3f(sclDat->getFloat(0), sclDat->getFloat(1), sclDat->getFloat(2));

    Instance* inst = new Instance(game->data->getModel(geom->getValue("model")->getString()), pos, rot, scl);
    geometry.push_back(inst);
  }
}

std::vector<Instance*> Bsp::getDraw() {
  return geometry;
}
