#include <errno.h>
#include <fontconfig/fontconfig.h>
#include <gtk/gtk.h>
#include <stdint.h>

#include "c_minilib_error.h"
#include "frontend/frontend.h"
#include "utils/memory.h"

struct Frontend {
  GtkApplication *app;
  const char *window_name;
  int32_t window_x;
  int32_t window_y;
};

static void gtk_main(GtkApplication *app, gpointer user_data) {
  frontend_t frontend = user_data;
  GtkWidget *window = NULL;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), frontend->window_name);
  gtk_window_set_default_size(GTK_WINDOW(window), frontend->window_x,
                              frontend->window_y);

  gtk_window_present(GTK_WINDOW(window));
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

cme_error_t frontend_start(frontend_t frontend) {
  cme_error_t err;

  int err_code = g_application_run(G_APPLICATION(frontend->app), 0, NULL);
  if (err_code) {
    err = cme_error(err_code, "Error occured in GTK app");
    goto error_out;
  }

  return 0;

error_out:
  return cme_return(err);
}
