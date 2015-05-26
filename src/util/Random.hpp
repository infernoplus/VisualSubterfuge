/* 
 * RNG
 * Author: pat
 *
 * Created on May 12, 2015, 11:27 AM
 */

#ifndef RANDOM_HPP
#define	RANDOM_HPP

namespace rng {
  int random(int max) {
          return floor(static_cast <float> (rand())/ static_cast <float> (RAND_MAX)*max);
  }

  float random(float max) {
          return static_cast <float> (rand())/ static_cast <float> (RAND_MAX)*max;
  }

  int random(int min, int max) {
          return min + floor(static_cast <float> (rand())/ static_cast <float> (RAND_MAX)*(max - min));
  }

  float random(float min, float max) {
          return min + (static_cast <float> (rand())/ static_cast <float> (RAND_MAX)*(max - min));
  }
}

#endif	/* RANDOM_HPP */

