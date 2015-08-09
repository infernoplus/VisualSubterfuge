/*
 * Editor.cpp
 *
 *  Created on: May 31, 2015
 *      Author: inferno
 */

#include <Engine.hpp>
#include <editor/Editor.h>

FileWidgetsCont::FileWidgetsCont(GtkWidget* fo, GtkWidget* fs, GtkNotebook* nb, std::vector<tab::Tab*>* pg) {
  this->fo = fo; this->fs = fs; this->nb = nb; this->pg = pg;
}

Editor::Editor(Engine* e) {
  engine = e;

  tReady = false; tClosed = false;
    thread = SDL_CreateThread(editorWrapper, "DisplayThread", this);

    if (NULL == thread) {
        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
        return;
    }

    for(int i=0;i<100&&!tReady;i++)
      SDL_Delay(33);
    if(!tReady)
      cmd::log("Something fucked up and the GTK window was never created. Throw an actual exception/error!"); //TODO: WHAT HE SAID!
}

Editor::~Editor() {

}

void Editor::step() {

}

int Editor::editorWrapper(void *ptr) {
  Editor* self = static_cast<Editor*>(ptr);
  return self->create();
}

int Editor::create() {
  gtk_init(0, new char**);
  /**Create main window**/
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
  gtk_window_set_default_size(GTK_WINDOW(window), 512, 768);
  gtk_window_set_title(GTK_WINDOW(window), (engine->title + "  Editor").c_str());

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);
  /**Create menu bar**/
  menubar = gtk_menu_bar_new();
  filemenu = gtk_menu_new();
  recompmenu = gtk_menu_new();

  accel_group = gtk_accel_group_new();
  gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

  file = gtk_menu_item_new_with_mnemonic("_File");
  recomp = gtk_menu_item_new_with_mnemonic("_Recompile");
  nu = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
  open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, NULL);
  save = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE, NULL);
  saveAs = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS, NULL);
  clos = gtk_image_menu_item_new_from_stock(GTK_STOCK_CLOSE, NULL);
  sep = gtk_separator_menu_item_new();
  quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group);
  soft = gtk_image_menu_item_new_with_label("Soft Recompile");
  hard = gtk_image_menu_item_new_with_label("Hard Recompile");

  gtk_widget_add_accelerator(quit, "activate", accel_group,
      GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(recomp), recompmenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), nu);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), saveAs);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), clos);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), sep);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
  gtk_menu_shell_append(GTK_MENU_SHELL(recompmenu), soft);
  gtk_menu_shell_append(GTK_MENU_SHELL(recompmenu), hard);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), recomp);
  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);

  /**Create welcome tab and container**/
  notebook = gtk_notebook_new ();
  gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
  pages = new std::vector<tab::Tab*>();

  tab::Tab* welcome = tab::openTabWelcome();
  gtk_notebook_append_page (GTK_NOTEBOOK (notebook), welcome->frame, welcome->label);
  pages->push_back(welcome);

  gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 3);
  /**Create file open and save menus**/
  dialogOpen = gtk_file_chooser_dialog_new ("Open File",
                (GtkWindow*)window,
                GTK_FILE_CHOOSER_ACTION_OPEN,
                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                NULL);
  dialogSave = gtk_file_chooser_dialog_new ("Save File",
                (GtkWindow*)window,
                GTK_FILE_CHOOSER_ACTION_SAVE,
                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                NULL);

  /**Menu item callbacks**/
  FileWidgetsCont* fwc = new FileWidgetsCont(dialogOpen, dialogSave, (GtkNotebook*)notebook, pages);
  g_signal_connect(G_OBJECT(nu), "activate", G_CALLBACK(&Editor::fileNew), fwc);
  g_signal_connect(G_OBJECT(open), "activate", G_CALLBACK(&Editor::fileOpen), fwc);
  g_signal_connect(G_OBJECT(save), "activate", G_CALLBACK(&Editor::fileSave), fwc);
  g_signal_connect(G_OBJECT(saveAs), "activate", G_CALLBACK(&Editor::fileSaveAs), fwc);
  g_signal_connect(G_OBJECT(clos), "activate", G_CALLBACK(&Editor::fileClose), fwc);

  g_signal_connect(G_OBJECT(soft), "activate", G_CALLBACK(&Editor::recompSoft), engine);
  g_signal_connect(G_OBJECT(hard), "activate", G_CALLBACK(&Editor::recompHard), engine);

  g_signal_connect (window, "delete_event", G_CALLBACK (&Editor::stop), NULL);
  g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(&Editor::stop), NULL);

  /**Finalize**/
  gtk_widget_show_all(window);
  tReady = true;
  gtk_main();

  tClosed = true;
  if(!engine->exit)
    engine->stop();

  return 0;
}

void Editor::fileNew(FileWidgetsCont* fwc) {
  tab::Tab* tab = tab::openTabBasicNew();
  gtk_notebook_append_page (fwc->nb, tab->frame, tab->label);
  fwc->pg->push_back(tab);
}

void Editor::fileOpen(FileWidgetsCont* fwc) {
  if (gtk_dialog_run (GTK_DIALOG (fwc->fo)) == GTK_RESPONSE_ACCEPT)
    {
      char *filename;
      filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (fwc->fo));

      std::string path = std::string(filename);
      int end = path.find_last_of('.');
      std::string type = path.substr(end, path.length());

      tab::Tab* tab;
      if(type == ".gls")
        tab = tab::openTabModelEdit(path);
      else
        tab = tab::openTabBasicEdit(path);

      gtk_notebook_append_page (fwc->nb, tab->frame, tab->label);
      fwc->pg->push_back(tab);
      g_free (filename);
    }
  gtk_widget_hide(fwc->fo);
}

void Editor::fileSave(FileWidgetsCont* fwc) {
  tab::Tab* tab = getFocus(fwc);
  if(tab == NULL)
    std::cout << "TODO:THROW EXCEPTION\n";
  else if(tab->canSave())
    tab->save();
  else if(tab->canSaveAs())
    fileSaveAs(fwc);
}

void Editor::fileSaveAs(FileWidgetsCont* fwc) {
  tab::Tab* tab = getFocus(fwc);
  if(tab == NULL)
    std::cout << "TODO:THROW EXCEPTION\n";
  else if(tab->canSaveAs()){
    if (gtk_dialog_run (GTK_DIALOG (fwc->fs)) == GTK_RESPONSE_ACCEPT)
      {
        char *filename;
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (fwc->fs));
        tab->saveAs(filename);
        g_free (filename);
      }
    gtk_widget_hide(fwc->fs);
  }
}

void Editor::fileClose(FileWidgetsCont* fwc) {
  tab::Tab* tab = getFocus(fwc);
  if(tab == NULL)
    std::cout << "TODO:THROW EXCEPTION\n";
  else {
    gtk_notebook_remove_page(fwc->nb, gtk_notebook_get_current_page(fwc->nb));
    tab->close();
  }
}

tab::Tab* Editor::getFocus(FileWidgetsCont* fwc) {
  int f = gtk_notebook_get_current_page(fwc->nb);
  for(uint i=0;i<fwc->pg->size();i++) {
    if(f == gtk_notebook_page_num(fwc->nb, fwc->pg->data()[i]->frame))
      return fwc->pg->data()[i];
  }
  return NULL;
}

void Editor::recompSoft(Engine* e) {
  e->recompSoft = true;
}

void Editor::recompHard(Engine* e) {
  e->recompHard = true;
}

void Editor::stop() {
  if(!tClosed)
    gtk_main_quit();
}

void Editor::close() {
  //TODO: Delete all pages/widgets. Memory no-nos
}

