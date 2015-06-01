/*
 * Editor.cpp
 *
 *  Created on: May 31, 2015
 *      Author: inferno
 */

#include <Engine.hpp>
#include <editor/Editor.h>

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

int frames = 0;
void Editor::step() {
  update(frames++);
}

int Editor::editorWrapper(void *ptr) {
  Editor* self = static_cast<Editor*>(ptr);
  return self->create();
}

int Editor::create() {
  gtk_init(0, new char**);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
  gtk_window_set_default_size(GTK_WINDOW(window), 512, 768);
  gtk_window_set_title(GTK_WINDOW(window), (engine->title + "  Engine").c_str());

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  menubar = gtk_menu_bar_new();
  filemenu = gtk_menu_new();

  accel_group = gtk_accel_group_new();
  gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

  file = gtk_menu_item_new_with_mnemonic("_File");
  nu = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
  open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, NULL);
  sep = gtk_separator_menu_item_new();
  quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group);

  gtk_widget_add_accelerator(quit, "activate", accel_group,
      GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), nu);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), sep);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);


  /**Test Start**/
  GtkWidget* notebook;
  notebook = gtk_notebook_new ();
  gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);

  GtkWidget* frame; GtkWidget* label; GtkWidget* view; GtkTextBuffer* buffer;

  for(int i=0;i<4;i++) {
    std::string icon = rng::meme();
    frame = gtk_frame_new ("The Holy Bible.txt");
    gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
    gtk_widget_set_usize (frame, 100, 75);
    gtk_widget_show (frame);

    view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    GtkTextIter iter;

    gtk_text_buffer_create_tag(buffer, "gap", "pixels_above_lines", 30, NULL);
    gtk_text_buffer_create_tag(buffer, "lmarg", "left_margin", 5, NULL);
    gtk_text_buffer_create_tag(buffer, "blue_fg", "foreground", "blue", NULL);
    gtk_text_buffer_create_tag(buffer, "gray_bg", "background", "lightgray", NULL);
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

    gtk_text_buffer_insert_with_tags_by_name(
        buffer,
        &iter,
        "What the fuck did you just fucking say about me, you little bitch?\nI’ll have you know I graduated top of my class in the Navy Seals, \nand I’ve been involved in numerous secret raids on Al-Quaeda, \nand I have over 300 confirmed kills.\nI am trained in gorilla warfare and I’m the top sniper in the \nentire US armed forces.\nYou are nothing to me but just another target.\nI will wipe you the fuck out with precision the likes of which \nhas never been seen before on this Earth, mark my fucking words.\nYou think you can get away with saying that shit to me over the Internet?\nThink again, fucker.\nAs we speak I am contacting my secret network of spies across the USA\nand your IP is being traced right now so you better prepare for the storm, maggot.\nThe storm that wipes out the pathetic little thing you call your life.\nYou’re fucking dead, kid.\nI can be anywhere, anytime, and I can kill you in over seven hundred ways,\nand that’s just with my bare hands.\nNot only am I extensively trained in unarmed combat, \nbut I have access to the entire arsenal of the United States Marine Corps\nand I will use it to its full extent to wipe your miserable ass off the face of the continent, you little shit.\nIf only you could have known what unholy retribution your little “clever” \ncomment was about to bring down upon you, \nmaybe you would have held your fucking tongue.\nBut you couldn’t, you didn’t, and now you’re paying the price, \nyou goddamn idiot.\nI will shit fury all over you and you will drown in it.\nYou’re fucking dead, kiddo.\n",
        -1,
        "lmarg",
        NULL
    );

    gtk_container_add (GTK_CONTAINER (frame), view);
    gtk_widget_show (label);

    label = gtk_label_new (icon.c_str());
    gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame, label);
  }

  gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 3);
  /**Test End**/

  g_signal_connect (window, "delete_event", G_CALLBACK (&Editor::stop), NULL);
  g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(&Editor::stop), NULL);

  gtk_widget_show_all(window);
  tReady = true;
  gtk_main();

  tClosed = true;
  if(!engine->exit)
    engine->stop();

  return 0;
}

void Editor::update(int x) {

}

void Editor::stop() {
  if(!tClosed)
    gtk_main_quit();
}

void Editor::close() {

}

