/*
 * Instance.h
 *
 *  Created on: Aug 9, 2015
 *      Author: inferno
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include "display/model/Model.h"
#include "util/coordinate/Vert3f.h"

class Instance {
public:
  gls::Model* model;
  Vert3f pos, rot, scl;

  Instance(gls::Model* model, Vert3f pos, Vert3f rot, Vert3f scl);
  virtual ~Instance();
};

#endif /* INSTANCE_H_ */
