/* 
 * File:   Util.hpp
 * Author: pat
 *
 * Created on February 6, 2015, 7:56 AM
 */

#ifndef UTIL_HPP
#define	UTIL_HPP

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <math.h>

class Color {
public: 
    float r;
    float g;
    float b;
public: 
    Color(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    Color() {
        r = 1.0f;
        g = 1.0f;
        b = 1.0f;
    }
public:
    void adjustIntensity(float min) {
        float max = r > g ? (r > b ? r : b) : (g > b ? g : b); //I'm probably a horrible person for writing this line of code.
        if(max < min) {
                float adj = min - max;
                r += adj; g += adj; b += adj;
        }
    }
};

class Line {
public:
    Vert3f a, b;
    float speed;
    Line(Vert3f a, Vert3f b, float speed) {
        this->a = a;
        this->b = b;
        this->speed = speed;
    }
    void draw() {
        glBegin(GL_LINES);
            glColor4f(speed/128.0f, speed/128.0f, speed/128.0f, 1.0f);
            glVertex3f(a.x, a.y, a.z);
            glVertex3f(b.x, b.y, b.z);
        glEnd();
    }
};

class Camera {
public:
    Vert3f pos;
    float i, j, k;
    float fov;
    Camera() {
        i = 0.0f;
        j = 0.0f;
        k = 0.0f;
        fov = 90.0f;
    }
    void setPosition(float x, float y, float z) {
        this->pos.x = x;
        this->pos.y = y;
        this->pos.z = z;
    }
    void setRotation(float i, float j) {
        this->i = i;
        this->j = j;
    }
    void setRotation(float i, float j, float k) {
        this->i = i;
        this->j = j;
        this->k = k;
    }
    void setFov(float fov) {
        this->fov = fov;
    }
    void applyCamera() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fov,1.0f,0.1f,10240000.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef (-pos.x, -pos.y, -pos.z);
        glRotatef(i, 0.0f, 0.0f, 1.0f);
        glRotatef(j, 1.0f, 0.0f, 0.0f);
        glRotatef(k, 0.0f, 1.0f, 0.0f);
    }
};

#endif	/* UTIL_HPP */

