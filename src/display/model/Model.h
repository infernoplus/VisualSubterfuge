/*
 * GlsModel loader
 * Author: pat
 *
 * Created on May 11, 2015, 2:49 PM
 */

#ifndef MODEL_H
#define MODEL_H


#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <string.h>

#include "display/shader/Shader.h"

class GameData;

//Documentation may be needed.
namespace gls {
  class Model {
  public:
    //File path
    std::string path;
    //Raw data
    uint gSize;
    gls::Shader** shaders;
    float** data; uint* dSize;
    uint** indices; uint* iSize;
    //OpenGL bind data
    bool bound;
    GLuint* vbo;
    GLuint vba;

    Model(std::string path, float** data, uint* dSize, uint** indices, uint* iSize, gls::Shader** shaders, uint gSize);
    Model();

    void bindData();
  };

  Model* openModel(const std::string in, GameData* gd);
}

#endif  /* GLSMODEL_H */

