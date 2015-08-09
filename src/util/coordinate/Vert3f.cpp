/*
 * Vert3f.cpp
 *
 *  Created on: Aug 9, 2015
 *      Author: inferno
 */

#include <util/coordinate/Vert3f.h>

#include <math.h>

Vert3f::Vert3f(float x, float y, float z) {
    this->x=x;
    this->y=y;
    this->z=z;
}

Vert3f::Vert3f() {
    x=0.0f;
    y=0.0f;
    z=0.0f;
}

Vert3f Vert3f::operator+(Vert3f b) {
    return Vert3f{x+b.x,y+b.y,z+b.z};
}
Vert3f Vert3f::operator-(Vert3f b) {
    return Vert3f{x-b.x,y-b.y,z-b.z};
}
Vert3f Vert3f::operator*(Vert3f b) {
    return Vert3f{x*b.x,y*b.y,z*b.z};
}
Vert3f Vert3f::operator*(float b) {
    return Vert3f{x*b,y*b,z*b};
}
Vert3f Vert3f::normalize() {
    float l = magnitude();
    return Vert3f{x/l,y/l,z/l};
}
Vert3f Vert3f::cubicNormalize() {
    float max = fabs(x) > fabs(y) ? (fabs(x) > fabs(z) ? fabs(x) : fabs(z)) : (fabs(y) > fabs(z) ? fabs(y) : fabs(z));
    max = 1.0f / max;
    return Vert3f{x*max,y*max,z*max};
}
float Vert3f::magnitude() {
    return sqrt((x*x)+(y*y)+(z*z));
}
float Vert3f::distance(Vert3f b) {
    Vert3f a = *this;
    return (a-b).magnitude();
}
Vert3f Vert3f::inverse() {
    return Vert3f{-x,-y,-z};
}

float Vert3f::fabs(float f) {
    if(f < 0)
        return f * -1.0f;
    return f;
}

