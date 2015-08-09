/*
 * Render.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: inferno
 */

#include <display/Render.h>

#include <Engine.hpp>
#include <display/Display.h>
#include <display/model/Instance.h>
#include <display/model/Model.h>
#include <game/Game.h>
#include <game/GameData.h>

#include <dirent.h>

Render::Render(Display* d) {
	display = d;
}

Render::~Render() {
	// TODO Auto-generated destructor stub
}

bool Render::init() {
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  return true;
}

void Render::initTestRender() {
 //kill me
}

float r = 0.0f;
void Render::doTestRender() {
  //What are we rendering?
  if(!display->engine->gameLoaded) {
    cmd::log("## Warning - Tried to render a frame but there was no loaded gamestate!");
    return;
  }

  //Bind any new stuff
  display->engine->game->data->bindData();

  //Get what we need to render
  std::vector<Instance*> geometry = display->engine->game->getDraw();
  r += 0.0004f;


  glm::vec3 eye = glm::vec3(sin(r*0.33)*2048.0f,2048.0f,cos(r*0.33)*2048.0f);
  glm::vec3 center = glm::vec3(0.0f,0.0f,0.0f);
  glm::vec3 up = glm::vec3(0.0f,0.0f,1.0f);

  glm::mat4 projection = glm::perspective(70.0f, ((float)display->screenWidth)/((float)display->screenHeight), 2.0f, 16384.0f);
  glm::mat4 view = glm::lookAt(eye, center, up);
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
  glm::mat4 mvp = projection * view * model;

  //Render a thing
  for(uint i=0;i<geometry.size();i++) {
    glm::vec3 pos = glm::vec3(geometry[i]->pos.x, geometry[i]->pos.y, geometry[i]->pos.z);
    glm::vec3 rot = glm::vec3(geometry[i]->rot.x, geometry[i]->rot.y, geometry[i]->rot.z);
    glm::vec3 scl = glm::vec3(geometry[i]->scl.x, geometry[i]->scl.y, geometry[i]->scl.z);

    for(uint j=0;j<geometry[i]->model->gSize;j++) {

      geometry[i]->model->shaders[j]->bind(model, view, projection, mvp, pos, rot, scl);

      glBindBuffer(GL_ARRAY_BUFFER, geometry[i]->model->vbo[j]);

      glEnableVertexAttribArray(0);
      glVertexAttribPointer(
              0,
              3,
              GL_FLOAT,
              GL_TRUE,
              36,
              (void*)0
      );
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(
              1,
              3,
              GL_FLOAT,
              GL_TRUE,
              36,
              (void*)12
      );
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(
              2,
              3,
              GL_FLOAT,
              GL_TRUE,
              36,
              (void*)24
      );

      glDrawElements(GL_TRIANGLES, geometry[i]->model->iSize[j], GL_UNSIGNED_INT, geometry[i]->model->indices[j]);

      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
      glDisableVertexAttribArray(2);
    }
  }

  glUseProgram(0);
}

void Render::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
  glClearColor(0.33f, 0.33f, 0.33f, 1.0f); // Set background color to grey

  doTestRender();

  glFlush();
}

void Render::close() {

}
