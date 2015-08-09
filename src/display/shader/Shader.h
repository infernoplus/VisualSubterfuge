/*
 * GLSL Program loader
 * Author: pat
 *
 * Created on May 11, 2015, 2:49 PM
 */

#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <sstream>

#include <vector>
#include <string.h>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "display/shader/Program.h"
#include "display/texture/Texture.h"
#include "util/Tson.h"
#include "util/coordinate/Vert3f.h"

class GameData;

namespace gls {
  class Shader {
  public:
    std::string path;
    Program* program;
    Texture** textures; uint tSize;
    Shader(std::string path, Program* program, Texture** textures, uint tSize);

    void bind(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::mat4 mvp, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl);
  };

  Shader* openShader(const std::string file, GameData* gd);
}
#endif  /* SHADER_H */

