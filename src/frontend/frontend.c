#include <errno.h>
#include <fontconfig/fontconfig.h>
#include <gtk/gtk.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "c_minilib_error.h"
#include "frontend/_internal/file_select_menu.h"
#include "frontend/_internal/frontend.h"
#include "frontend/frontend.h"
#include "utils/file.h"
#include "utils/memory.h"

static void gtk_main(GtkApplication *app, gpointer user_data) {
  frontend_t frontend = user_data;
  cme_error_t err;
  GtkWidget *box;

  frontend->main_window = gtk_application_window_new(frontend->app);
  gtk_window_set_title(GTK_WINDOW(frontend->main_window),
                       frontend->window_name);
  gtk_window_set_default_size(GTK_WINDOW(frontend->main_window),
                              frontend->window_x, frontend->window_y);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_window_set_child(GTK_WINDOW(frontend->main_window), box);

  err = FileSelectMenu_create(frontend, &frontend->file_select_menu);
  if (err) {
    goto error_out;
  }

  gtk_window_present(GTK_WINDOW(frontend->main_window));

  return;

error_out:
  puts("ERROR");
}

cme_error_t frontend_create(const char *app_name, const char *window_name,
                            int32_t window_x, int32_t window_y,
                            frontend_t *out) {
  *out = my_malloc(sizeof(struct Frontend));

  *(*out) = (struct Frontend){
      .app = gtk_application_new(app_name, G_APPLICATION_DEFAULT_FLAGS),
      .window_name = window_name,
      .window_x = window_x,
      .window_y = window_y,
  };

  g_signal_connect((*out)->app, "activate", G_CALLBACK(gtk_main), *out);

  return 0;
}

void frontend_destroy(frontend_t *out) {
  if (!out || !*out) {
    return;
  }

  g_object_unref((*out)->app);
  free(*out);

  // Cleanup fontconfig
  FcFini();

  *out = NULL;
};

cme_error_t frontend_start(frontend_t frontend, int argc, char **argv) {
  cme_error_t err;

  int err_code = g_application_run(G_APPLICATION(frontend->app), argc, argv);
  if (err_code) {
    err = cme_error(err_code, "Error occured in GTK app");
    goto error_out;
  }

  return 0;

error_out:
  return cme_return(err);
}
