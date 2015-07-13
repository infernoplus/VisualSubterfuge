/*
 * Engine.hpp
 *
 *  Created on: May 29, 2015
 *      Author: inferno
 */

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SDL2/SDL.h>

#include <unistd.h>
#include <limits.h>

#include "game/Game.h"
#include "display/Display.h"
#include "input/Input.h"
#include "editor/Editor.h"
#include "util/Log.h"
#include "util/Meme.h"

class Engine {
public:
  bool exit;
  bool recompSoft, recompHard;

  std::string title;
  std::string root; //Working directory

  Display* display;
  Input* input;
  Editor* editor;

  bool gameLoaded;
  Game* game;

  Engine(int argc, char *argv[]) {
    exit = false; recompSoft = false; recompHard = false; gameLoaded = false;
    title = rng::meme();

    cmd::log("Logging started for " + title + " ...");
    setRoot(); cmd::log("Working directory is '" + root + "' ...");
    display = new Display(this); cmd::log("Display started ...");
    input = new Input(this); cmd::log("Input started ...");
    editor = new Editor(this); cmd::log("Editor started ...");
    cmd::log("Engine running!");

    load(); cmd::log("Game loaded ...");
  }
  virtual ~Engine() { }

  void load() {
    game = new Game(this);
    gameLoaded = true;
  }

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

        display = new Display(this); cmd::log("Display restarted ...");
        load(); cmd::log("Game reloaded ...");
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
  //TODO: WINDOWS/MAC/FREEBSD COMPATIBILITY
  void setRoot() {
    /**Only works on linux START**/
    char buff[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
    if (len != -1) {
      buff[len] = '\0';
      root = std::string(buff);
      int end = root.find_last_of('/');
      root = root.substr(0,end);
    }
    else {
      //TODO: EXCEPTION!
    }
    /**Only works on linux END**/
  }
  void close() {
    cmd::log("Stopping engine ...");
    exit = true;

    //Close editor and display threads...
    display->stop();
    editor->stop();
    while(!display->tClosed || !editor->tClosed) {
      SDL_Delay(100); //Wait until they are done closing...
    }

    delete game;

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
