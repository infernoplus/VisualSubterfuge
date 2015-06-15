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

#include "editor/tab/Tab.h"

class Engine;

class FileWidgetsCont {
public:
  GtkWidget* fo;
  GtkWidget* fs;
  GtkNotebook* nb;
  std::vector<tab::Tab*>* pg;
  FileWidgetsCont(GtkWidget* fs, GtkWidget* fo, GtkNotebook* nb, std::vector<tab::Tab*>* pg);
};

class Editor {
public:
  Engine* engine;
  //Thread
  bool tReady, tClosed;
  SDL_Thread *thread;
  //Main window
  GtkWidget *window;
  GtkWidget *vbox;
  GtkAccelGroup *accel_group = NULL;
  //Menubar
  GtkWidget *menubar;
  GtkWidget *filemenu;
  GtkWidget *file;
  GtkWidget *nu;
  GtkWidget *open;
  GtkWidget *save;
  GtkWidget *saveAs;
  GtkWidget *clos;
  GtkWidget *quit;
  GtkWidget *sep;
  GtkWidget *recompmenu;
  GtkWidget *recomp;
  GtkWidget *soft;
  GtkWidget *hard;
  //Tab container
  GtkWidget* notebook;
  std::vector<tab::Tab*>* pages;
  //File choosers
  GtkWidget *dialogOpen;
  GtkWidget *dialogSave;

  Editor(Engine* e);
  virtual ~Editor();

  void step();
  void stop();
  void close();
private:
  //Menu Functions
  void fileNew(FileWidgetsCont* fwc);
  void fileOpen(FileWidgetsCont* fwc);
  void fileSave(FileWidgetsCont* fwc);
  void fileSaveAs(FileWidgetsCont* fwc);
  void fileClose(FileWidgetsCont* fwc);

  //Util
  tab::Tab* getFocus(FileWidgetsCont* fwc);

  //Core
  static int editorWrapper(void *ptr);
  int create();
  void update(int x);
};

#endif /* EDITOR_H_ */
