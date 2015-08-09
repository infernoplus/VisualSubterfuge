/*
 * Instance.cpp
 *
 *  Created on: Aug 9, 2015
 *      Author: inferno
 */

#include "display/model/Instance.h"

Instance::Instance(gls::Model* model, Vert3f pos, Vert3f rot, Vert3f scl) {
  this->model = model;
  this->pos = pos; this->rot = rot; this->scl = scl;
}

Instance::~Instance() {
  // TODO Auto-generated destructor stub
}

