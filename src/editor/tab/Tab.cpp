/*
 * Tab.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: inferno
 */

#include <editor/tab/Tab.h>

   tab::Tab::Tab(std::string tab, std::string header) {
      label = gtk_label_new (tab.c_str());
      frame = gtk_frame_new (header.c_str());
      gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
      gtk_widget_set_usize (frame, 100, 75);
      gtk_widget_show (frame);
      gtk_widget_show (label);
    }
    tab::Tab::~Tab() {
      delete frame; delete label;
    }

    bool tab::Tab::canSave() { return false; }
    bool tab::Tab::canSaveAs() { return false; }

    void tab::Tab::save() {

    }
    void tab::Tab::saveAs(std::string out) {

    }
    void tab::Tab::close() {

    }

    /** ===================================================================================================================== **/
    /** ===================================================================================================================== **/


    tab::TabWelcome::TabWelcome(std::string tab, std::string header) : Tab(tab, header) {
      build();
    }
    tab::TabWelcome::~TabWelcome() {
      delete view; delete buffer;
    }
    void tab::TabWelcome::build() {
      view = gtk_text_view_new();
      gtk_text_view_set_editable(GTK_TEXT_VIEW(view), false);
      buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

      gtk_text_buffer_create_tag(buffer, "gap", "pixels_above_lines", 30, NULL);
      gtk_text_buffer_create_tag(buffer, "lmarg", "left_margin", 5, NULL);
      gtk_text_buffer_create_tag(buffer, "blue_fg", "foreground", "blue", NULL);
      gtk_text_buffer_create_tag(buffer, "gray_bg", "background", "lightgray", NULL);
      gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

      gtk_text_buffer_insert_with_tags_by_name(
          buffer,
          &iter,
          "\nWelcome to the VisualSubterfuge editor!\n\nOpen a tag to start editing.\nHit recompile to reload the gameworld.\nChanges that have been made will be applied on reload.\n",
          -1,
          "lmarg",
          NULL
      );
      gtk_widget_show (view);
      gtk_container_add (GTK_CONTAINER (frame), view);
    }

    bool tab::TabWelcome::canSave() { return false; }
    bool tab::TabWelcome::canSaveAs() { return false; }

    void tab::TabWelcome::save() {

    }
    void tab::TabWelcome::saveAs(std::string out) {

    }

    /** ===================================================================================================================== **/
    /** ===================================================================================================================== **/

    tab::TabBasicNew::TabBasicNew(std::string tab, std::string header) : Tab(tab, header) {
      saved = false;
      build();
    }
    tab::TabBasicNew::~TabBasicNew() {
      delete view; delete buffer;
    }
    void tab::TabBasicNew::build() {
      view = gtk_text_view_new();
      gtk_text_view_set_editable(GTK_TEXT_VIEW(view), true);
      buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

      gtk_text_buffer_create_tag(buffer, "gap", "pixels_above_lines", 30, NULL);
      gtk_text_buffer_create_tag(buffer, "lmarg", "left_margin", 5, NULL);
      gtk_text_buffer_create_tag(buffer, "blue_fg", "foreground", "blue", NULL);
      gtk_text_buffer_create_tag(buffer, "gray_bg", "background", "lightgray", NULL);
      gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

      gtk_text_buffer_insert_with_tags_by_name(
          buffer,
          &iter,
          "",
          -1,
          "lmarg",
          NULL
      );
      gtk_widget_show (view);
      gtk_container_add (GTK_CONTAINER (frame), view);
    }

    bool tab::TabBasicNew::canSave() { return saved; }
    bool tab::TabBasicNew::canSaveAs() { return true; }

    void tab::TabBasicNew::save() {
      if(saved) {
        std::ofstream of; //TODO: File writing no-no! Use a util!
        of.open(file.c_str());
        GtkTextIter start, end;
        gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
        gtk_text_buffer_get_iter_at_offset(buffer, &end, gtk_text_buffer_get_char_count(buffer));
        std::string data(gtk_text_buffer_get_text(buffer, &start, &end, true));
        of << data.c_str();
        of.close();
      }
    }
    void tab::TabBasicNew::saveAs(std::string out) {
      std::ofstream of; //TODO: File writing no-no! Use a util!
      of.open(out.c_str());
      GtkTextIter start, end;
      gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
      gtk_text_buffer_get_iter_at_offset(buffer, &end, gtk_text_buffer_get_char_count(buffer));
      std::string data(gtk_text_buffer_get_text(buffer, &start, &end, true));
      of << data.c_str();
      of.close();
      file = out;
      int st = file.find_last_of('/'); //TODO: Windows compatibility/file acsess no-no.
      gtk_label_set_text((GtkLabel*)label, file.substr(st+1, file.length()-st-1).c_str());
      gtk_frame_set_label((GtkFrame*)frame, file.c_str());
      saved = true;
    }

    /** ===================================================================================================================== **/
    /** ===================================================================================================================== **/

    tab::TabBasicEdit::TabBasicEdit(std::string tab, std::string header) : Tab(tab, header) {
      file = header;
      build();
    }
    tab::TabBasicEdit::~TabBasicEdit() {
      delete view; delete buffer;
    }
    void tab::TabBasicEdit::build() {
      view = gtk_text_view_new();
      gtk_text_view_set_editable(GTK_TEXT_VIEW(view), true);
      buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

      gtk_text_buffer_create_tag(buffer, "gap", "pixels_above_lines", 30, NULL);
      gtk_text_buffer_create_tag(buffer, "lmarg", "left_margin", 5, NULL);
      gtk_text_buffer_create_tag(buffer, "blue_fg", "foreground", "blue", NULL);
      gtk_text_buffer_create_tag(buffer, "gray_bg", "background", "lightgray", NULL);
      gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

      gtk_text_buffer_insert_with_tags_by_name(
          buffer,
          &iter,
          openFile(file).c_str(),
          -1,
          "lmarg",
          NULL
      );
      gtk_widget_show (view);
      gtk_container_add (GTK_CONTAINER (frame), view);
    }
    std::string tab::TabBasicEdit::openFile(std::string in) {
      std::ifstream t(in);
      std::stringstream buffer;

      buffer << t.rdbuf();

      t.close();
      return buffer.str();
    }

    bool tab::TabBasicEdit::canSave() { return true; }
    bool tab::TabBasicEdit::canSaveAs() { return true; }

    void tab::TabBasicEdit::save() {
      std::ofstream of; //TODO: File writing no-no! Use a util!
      of.open(file.c_str());
      GtkTextIter start, end;
      gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
      gtk_text_buffer_get_iter_at_offset(buffer, &end, gtk_text_buffer_get_char_count(buffer));
      std::string data(gtk_text_buffer_get_text(buffer, &start, &end, true));
      of << data.c_str();
      of.close();
    }
    void tab::TabBasicEdit::saveAs(std::string out) {
      std::ofstream of; //TODO: File writing no-no! Use a util!
      of.open(out.c_str());
      GtkTextIter start, end;
      gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
      gtk_text_buffer_get_iter_at_offset(buffer, &end, gtk_text_buffer_get_char_count(buffer));
      std::string data(gtk_text_buffer_get_text(buffer, &start, &end, true));
      of << data.c_str();
      of.close();
      file = out;
      int st = file.find_last_of('/'); //TODO: Windows compatibility/file acsess no-no.
      gtk_label_set_text((GtkLabel*)label, file.substr(st+1, file.length()-st-1).c_str());
      gtk_frame_set_label((GtkFrame*)frame, file.c_str());
    }

    /** ===================================================================================================================== **/
    /** ===================================================================================================================== **/

  tab::Tab* tab::openTabWelcome() {
    tab::TabWelcome* tab = new tab::TabWelcome("Welcome", "Visual Subterfuge Information");
    return tab;
  }

  tab::Tab* tab::openTabBasicEdit(std::string in) {
    int start = in.find_last_of('/'); //TODO: Windows compatibility/file acsess no-no.
    tab::TabBasicEdit* tab = new tab::TabBasicEdit(in.substr(start+1, in.length()-start-1), in);
    return tab;
  }

  tab::Tab* tab::openTabBasicNew() {
    tab::TabBasicNew* tab = new tab::TabBasicNew("new", "new file");
    return tab;
  }

