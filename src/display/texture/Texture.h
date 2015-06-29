/*
 * PngTexture loader
 * Author: pat
 *
 * Created on May 11, 2015, 2:49 PM
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <string.h>

#include "util/Log.h"
#include "lodepng.h"

class GameData;

namespace gls {
  class Texture {
  public:
    //File path
    std::string path;
    //OpenGL bind data
    bool bound;
    GLuint texId;

    Texture(std::string path);
    Texture();
    void bindData();
    void bind(int program, int id);
  };

  Texture* openTexture(const std::string in, GameData* gd);
}
#endif  /* TEXTURE_H */

