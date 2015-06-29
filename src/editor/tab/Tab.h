/*
 * Tab.h
 *
 *  Created on: Jun 14, 2015
 *      Author: inferno
 */

#ifndef TAB_H_
#define TAB_H_

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include <sstream>
#include <fstream>

#include "util/Log.h"

namespace tab {
  class Tab {
  public:
    GtkWidget* frame; GtkWidget* label;
    Tab(std::string tab, std::string header);
    ~Tab();
    virtual bool canSave();
    virtual bool canSaveAs();
    virtual void save();
    virtual void saveAs(std::string out);
    virtual void close();
  };

  class TabWelcome : public Tab {
  public:
    GtkWidget* view; GtkTextBuffer* buffer; GtkTextIter iter;
    TabWelcome(std::string tab, std::string header);
    ~TabWelcome();
    virtual bool canSave();
    virtual bool canSaveAs();
    virtual void save();
    virtual void saveAs(std::string out);
  private:
    void build();
  };

  class TabBasicNew : public Tab {
  public:
    GtkWidget* view; GtkTextBuffer* buffer; GtkTextIter iter;
    std::string file; bool saved;
    TabBasicNew(std::string tab, std::string header);
    ~TabBasicNew();
    virtual bool canSave();
    virtual bool canSaveAs();
    virtual void save();
    virtual void saveAs(std::string out);
  private:
    void build();
  };

  class TabBasicEdit : public Tab {
  public:
    GtkWidget* view; GtkTextBuffer* buffer; GtkTextIter iter;
    std::string file;
    TabBasicEdit(std::string tab, std::string header);
    ~TabBasicEdit();
    virtual bool canSave();
    virtual bool canSaveAs();
    virtual void save();
    virtual void saveAs(std::string out);
  private:
    void build();
    std::string openFile(std::string in);
  };

  class TabModelEdit : public Tab {
  public:
    std::string file;

    char* header = new char[4];
    uint gSize;
    std::string* shaders; uint* sSize;
    float** data; uint* dSize;
    uint** indices; uint* iSize;

    TabModelEdit(std::string tab, std::string header);
    ~TabModelEdit();
    virtual bool canSave();
    virtual bool canSaveAs();
    virtual void save();
    virtual void saveAs(std::string out);
  private:
    void build();
    void openModel(std::string in);
  };

  Tab* openTabWelcome();

  Tab* openTabBasicEdit(std::string in);

  Tab* openTabModelEdit(std::string in);

  Tab* openTabBasicNew();
}

#endif /* TAB_H_ */
