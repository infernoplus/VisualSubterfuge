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

    tab::TabModelEdit::TabModelEdit(std::string tab, std::string header) : Tab(tab, header) {
      file = header;
      build();
    }
    tab::TabModelEdit::~TabModelEdit() {

    }
    void tab::TabModelEdit::build() {
      openModel(file);
      GtkWidget* sbox;
      GtkWidget* layout;
      GtkWidget* hbox; GtkWidget* label;
      entry = new GtkWidget*[gSize];

      sbox = gtk_scrolled_window_new(NULL,NULL);
      gtk_scrolled_window_set_policy((GtkScrolledWindow*)sbox,GTK_POLICY_NEVER,GTK_POLICY_ALWAYS );
      gtk_widget_show(sbox);

      layout = gtk_layout_new(NULL,NULL);
      gtk_widget_show(layout);

      for(uint i=0;i<gSize;i++) {
        std::string ltext = "Shader #" + std::to_string(i);

        hbox = gtk_hbox_new(0,1);
        label = gtk_label_new(ltext.c_str());
        entry[i] = gtk_entry_new();
        gtk_entry_set_text((GtkEntry*)entry[i], shaders[i].c_str());
        gtk_widget_show(hbox); gtk_widget_show (label); gtk_widget_show(entry[i]);
        gtk_container_add (GTK_CONTAINER (hbox), label);
        gtk_container_add (GTK_CONTAINER (hbox), entry[i]);
        gtk_layout_put((GtkLayout*)layout, hbox, 0, i*35);
        gtk_layout_set_size((GtkLayout*)layout, 512,(i*35)+35);
      }

      gtk_container_add (GTK_CONTAINER(sbox), layout);
      gtk_container_add (GTK_CONTAINER (frame), sbox);

    }
    void tab::TabModelEdit::openModel(std::string in) {
      std::ifstream fin(in);
      if(fin.is_open()) {
        union { uint val; char bytes[sizeof(uint)]; } byteToUint;
        union { float val; char bytes[sizeof(float)]; } byteToFloat;
        //Read header
        for(uint i=0;!fin.eof()&&i<3;i++)
          header[i] = fin.get();
        header[3] = '\00';
        //Read total number of geometry groups
        for(uint i=0;!fin.eof()&&i<sizeof(uint);i++)
          fin.get(byteToUint.bytes[i]);
        gSize = byteToUint.val;

        //std::cout << "Header -- " << header << " | Geom Groups -- " << gSize << "\n";

        shaders = new std::string[gSize]; sSize = new uint[gSize];
        data = new float*[gSize]; dSize = new uint[gSize];
        indices = new uint*[gSize]; iSize = new uint[gSize];

        for(uint j=0;j<gSize;j++) {
          //Read size of shader name
          for(uint i=0;!fin.eof()&&i<sizeof(uint);i++)
            fin.get(byteToUint.bytes[i]);
          sSize[j] = byteToUint.val;
          //Read shader name for this geometry group
          std::stringstream ss;
          for(uint i=0;!fin.eof()&&i<sSize[j];i++) {
            char ch;
            fin.get(ch);
            ss << ch;
          }
          ss << '\00';
          shaders[j] = ss.str();
          //Read vertex data size
          for(uint i=0;!fin.eof()&&i<sizeof(uint);i++)
            fin.get(byteToUint.bytes[i]);
          dSize[j] = byteToUint.val;
          //Read vertex data
          data[j] = new float[dSize[j]];
          for(uint i=0;!fin.eof()&&i<dSize[j];i++) {
            for(uint j=0;!fin.eof()&&j<sizeof(float);j++)
              fin.get(byteToFloat.bytes[j]);
            data[j][i] = byteToFloat.val;
          }
          //Read indices data size
          for(uint i=0;!fin.eof()&&i<sizeof(uint);i++)
            fin.get(byteToUint.bytes[i]);
          iSize[j] = byteToUint.val;
          //Read indices data
          indices[j] = new uint[iSize[j]];
          for(uint i=0;!fin.eof()&&i<iSize[j];i++) {
            for(uint j=0;!fin.eof()&&j<sizeof(uint);j++)
              fin.get(byteToUint.bytes[j]);
            indices[j][i] = byteToUint.val;
          }
          //std::cout << "Read Group " << j << " - data: " << dSize[j] << " - indices: " << iSize[j] << " - shader: " << shaders[j] << "\n";
        }
      }
    }

    bool tab::TabModelEdit::canSave() { return true; }
    bool tab::TabModelEdit::canSaveAs() { return true; }

    void tab::TabModelEdit::save() {
      //Get shader names from UI
      for(uint i=0;i<gSize;i++) {
        shaders[i] = std::string(gtk_entry_get_text((GtkEntry*)entry[i]));
      }

      std::ofstream fout(file);

      //Write header
      fout << 'g'; fout << 'l'; fout << 's';

      //Types
      union { char bytes[sizeof(uint)]; uint val; } uintToByte;
      union { char bytes[sizeof(float)]; float val; } floatToByte;

      //Write number of geometry groups
      uintToByte.val = gSize;
      for(uint i=0;i<sizeof(uint);i++) {
        fout << uintToByte.bytes[i];
      }

      //Write back to file
      for(uint i=0;i<gSize;i++) {

        //Write shader length
        uintToByte.val = shaders[i].length();
        for(uint j=0;j<sizeof(uint);j++) {
          fout << uintToByte.bytes[j];
        }

        //Write shader
        for(uint j=0;j<shaders[i].length();j++) {
          fout << shaders[i].at(j);
        }

        //Write vertex data size
        uintToByte.val = dSize[i];
        for(uint j=0;j<sizeof(uint);j++) {
          fout << uintToByte.bytes[j];
        }

        //Write vertex data
        for(uint j=0;j<dSize[i];j++) {
          floatToByte.val = data[i][j];
          for(uint k=0;k<sizeof(float);k++) {
            fout << floatToByte.bytes[k];
          }
        }

        //Write indices size
        uintToByte.val = iSize[i];
        for(uint j=0;j<sizeof(uint);j++) {
          fout << uintToByte.bytes[j];
        }

        //Write indices
        for(uint j=0;j<iSize[i];j++) {
          uintToByte.val = indices[i][j];
          for(uint k=0;k<sizeof(uint);k++) {
            fout << uintToByte.bytes[k];
          }
        }
      }
      fout.close();
    }
    void tab::TabModelEdit::saveAs(std::string out) {
      //Get shader names from UI
      for(uint i=0;i<gSize;i++) {
        shaders[i] = std::string(gtk_entry_get_text((GtkEntry*)entry[i]));
      }

      std::ofstream fout(out);

      //Write header
      fout << 'g'; fout << 'l'; fout << 's';

      //Types
      union { char bytes[sizeof(uint)]; uint val; } uintToByte;
      union { char bytes[sizeof(float)]; float val; } floatToByte;

      //Write number of geometry groups
      uintToByte.val = gSize;
      for(uint i=0;i<sizeof(uint);i++) {
        fout << uintToByte.bytes[i];
      }

      //Write back to file
      for(uint i=0;i<gSize;i++) {

        //Write shader length
        uintToByte.val = shaders[i].length();
        for(uint j=0;j<sizeof(uint);j++) {
          fout << uintToByte.bytes[j];
        }

        //Write shader
        for(uint j=0;j<shaders[i].length();j++) {
          fout << shaders[i].at(j);
        }

        //Write vertex data size
        uintToByte.val = dSize[i];
        for(uint j=0;j<sizeof(uint);j++) {
          fout << uintToByte.bytes[j];
        }

        //Write vertex data
        for(uint j=0;j<dSize[i];j++) {
          floatToByte.val = data[i][j];
          for(uint k=0;k<sizeof(float);k++) {
            fout << floatToByte.bytes[k];
          }
        }

        //Write indices size
        uintToByte.val = iSize[i];
        for(uint j=0;j<sizeof(uint);j++) {
          fout << uintToByte.bytes[j];
        }

        //Write indices
        for(uint j=0;j<iSize[i];j++) {
          uintToByte.val = indices[i][j];
          for(uint k=0;k<sizeof(uint);k++) {
            fout << uintToByte.bytes[k];
          }
        }
      }
      fout.close();
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

  tab::Tab* tab::openTabModelEdit(std::string in) {
    int start = in.find_last_of('/'); //TODO: Windows compatibility/file acsess no-no.
    tab::TabModelEdit* tab = new tab::TabModelEdit(in.substr(start+1, in.length()-start-1), in);
    return tab;
  }

  tab::Tab* tab::openTabBasicNew() {
    tab::TabBasicNew* tab = new tab::TabBasicNew("new", "new file");
    return tab;
  }

