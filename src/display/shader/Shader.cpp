/*
 * GLSL Program loader
 * Author: pat
 *
 * Created on May 11, 2015, 2:49 PM
 */

#include <display/shader/Shader.h>

#include <game/GameData.h>

  gls::Shader::Shader(std::string path, Program* program, Texture** textures, uint tSize) {
    this->path = path;
    this->program = program;
    this->textures = textures;
    this->tSize = tSize;
  }

  gls::Shader* gls::openShader(const std::string path, GameData* gd) {
    tsn::TsonObject* tson = tsn::openTson(path);

    gls::Program* program = gd->getProgram(tson->getValue("glsl")->getString());
    uint tSize = tson->getArray("textures")->size();
    Texture** textures = new Texture*[tSize];
    for(uint i=0;i<tSize;i++)
      textures[i] = gd->getTexture(tson->getArray("textures")->getString(i));
    Shader* shader = new Shader(path, program, textures, tSize);

    delete tson;

    return shader;
  }

  void gls::Shader::bind(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::mat4 mvp, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl) {
       glUseProgram(program->program); //TODO: using first shader and nothing else

       GLuint uniformModel = glGetUniformLocation(program->program, "model"); //TODO: index this on program creation
       GLuint uniformView = glGetUniformLocation(program->program, "view");
       GLuint uniformProjection = glGetUniformLocation(program->program, "projection");
       GLuint uniformMvp = glGetUniformLocation(program->program, "mvp");
       GLuint uniformPos = glGetUniformLocation(program->program, "pos");
       GLuint uniformRot = glGetUniformLocation(program->program, "rot");
       GLuint uniformScl = glGetUniformLocation(program->program, "scl");

       glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
       glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
       glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
       glUniformMatrix4fv(uniformMvp, 1, GL_FALSE, glm::value_ptr(mvp));


       glUniform3f(uniformPos, pos.x, pos.y, pos.z);
       glUniform3f(uniformRot, rot.x, rot.y, rot.z);
       glUniform3f(uniformScl, scl.x, scl.y, scl.z);

       for(uint i=0;i<tSize;i++)
         textures[i]->bind(program->program, i);
 }

