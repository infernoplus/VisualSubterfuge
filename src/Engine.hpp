/*
 * Engine.hpp
 *
 *  Created on: May 29, 2015
 *      Author: inferno
 */

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SDL2/SDL.h>

#include "display/Display.h"
#include "input/Input.h"
#include "util/Log.h"

class Engine {
public:
  bool exit;

  Display* display;
  Input* input;

  Engine(int argc, char *argv[]) {
    exit = false;
    cmd::log("Logging started...");
    display = new Display(this); cmd::log("Display started...");
    input = new Input(this); cmd::log("Input started...");
    cmd::log("Engine running!");
  }
  virtual ~Engine() { }

  int run() {
    while(!exit) {
      input->step();
      SDL_Delay(33);
    }
    close();
    return 0;
  }

  void stop() {
    exit = true;
    display->stop();
    SDL_Delay(100); //Give display thread 1/10 a second to close before free memory
  }
private:
  void close() {
    cmd::log("Stopping engine!");

    display->close();
    input->close();

    delete display;
    delete input;
  }
};

#endif /* ENGINE_HPP_ */
