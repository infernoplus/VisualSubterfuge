/*
 * Editor.h
 *
 *  Created on: May 31, 2015
 *      Author: inferno
 */

#ifndef EDITOR_H_
#define EDITOR_H_

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_timer.h>

class Engine;

class Editor {
public:
  Engine* engine;

  bool tReady, tClosed;
  SDL_Thread *thread;

  GtkWidget *window;
  GtkWidget *vbox;

  GtkWidget *menubar;
  GtkWidget *filemenu;
  GtkWidget *file;
  GtkWidget *nu;
  GtkWidget *open;
  GtkWidget *quit;

  GtkWidget *sep;

  GtkAccelGroup *accel_group = NULL;

  Editor(Engine* e);
  virtual ~Editor();
  void step();
  void stop();
  void close();
private:
  static int editorWrapper(void *ptr);
  int create();
  void update(int x);
};

#endif /* EDITOR_H_ */
