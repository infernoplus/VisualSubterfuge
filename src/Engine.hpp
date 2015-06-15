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
#include "editor/Editor.h"
#include "util/Log.h"
#include "util/Meme.h"

class Engine {
public:
  bool exit;
  bool recompSoft, recompHard;

  Display* display;
  Input* input;
  Editor* editor;

  std::string title;

  Engine(int argc, char *argv[]) {
    exit = false; recompSoft = false; recompHard = false;
    title = rng::meme();

    cmd::log("Logging started...");
    display = new Display(this); cmd::log("Display started ...");
    input = new Input(this); cmd::log("Input started ...");
    editor = new Editor(this); cmd::log("Editor started ...");
    cmd::log("Engine running!");
  }
  virtual ~Engine() { }

  int run() {
    while(!exit) {
      if(recompHard) {
        recompHard = false;
        display->stop();
        for(int i=0;i<100&&!display->tClosed;i++)
          SDL_Delay(33);
        if(!display->tClosed)
          cmd::log("Something fucked up and recompile never managed to close the display. Throw an actual exception/error!"); //TODO: WHAT HE SAID!
        display->close();
        delete display;

        display = new Display(this); cmd::log("Display started ...");
      }
      input->step();
      editor->step();
      SDL_Delay(33);
    }
    close();
    return 0;
  }

  void stop() {
    exit = true;
  }
private:
  void close() {
    cmd::log("Stopping engine ...");
    exit = true;

    //Close editor and display threads...
    display->stop();
    editor->stop();
    while(!display->tClosed || !editor->tClosed) {
      SDL_Delay(100); //Wait until they are done closing...
    }

    cmd::log("Closing threads ...");

    editor->close();
    input->close();
    display->close();

    delete editor;
    delete input;
    delete display;

    cmd::log("Exiting ...");
  }
};

#endif /* ENGINE_HPP_ */
