/*
 * Vert3f.h
 *
 *  Created on: Aug 9, 2015
 *      Author: inferno
 */

#ifndef VERT3F_H_
#define VERT3F_H_

#include <math.h>

class Vert3f {
public:
    float x, y, z;
public:
    Vert3f(float x, float y, float z);
    Vert3f();
public:
    Vert3f operator+(Vert3f b);
    Vert3f operator-(Vert3f b);
    Vert3f operator*(Vert3f b);
    Vert3f operator*(float b);
    Vert3f normalize();
    Vert3f cubicNormalize();
    float magnitude();
    float distance(Vert3f b);
    Vert3f inverse();
private:
    float fabs(float f);
};

#endif /* VERT3F_H_ */
