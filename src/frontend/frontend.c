#include <errno.h>
#include <fontconfig/fontconfig.h>
#include <gtk/gtk.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "c_minilib_error.h"
#include "frontend/frontend.h"
#include "utils/file.h"
#include "utils/memory.h"

struct Frontend {
  GtkApplication *app;
  GtkWidget *main_window;
  const char *window_name;
  int32_t window_x;
  int32_t window_y;
};
static void print_hello(GtkWidget *widget, gpointer data) {
  puts("Hello world");
  g_print("Hello World\n");
}

static void gtk_main(GtkApplication *app, gpointer user_data) {
  frontend_t frontend = user_data;
  GtkWidget *window;
  GtkWidget *grid;
  cme_error_t err;
  GtkWidget *box;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), frontend->window_name);
  gtk_window_set_default_size(GTK_WINDOW(window), frontend->window_x,
                              frontend->window_y);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_window_set_child(GTK_WINDOW(window), box);

  /* Here we construct the container that is going show file content. */
  grid = gtk_grid_new();
  /* Pack the container in the window */
  gtk_window_set_child(GTK_WINDOW(window), grid);

  const char *files[255];
  err = list_dir(".", 254, files);
  if (err) {
    goto error_out;
  }

  const char **file_path = files;
  int i = 0;
  while (*file_path) {
    /* GtkEntryBuffer *entr_buf = */
    /*     gtk_entry_buffer_new(*file_path, strlen(*file_path)); */
    /* GtkWidget *entry = gtk_entry_new_with_buffer(entr_buf); */
    /* gtk_grid_attach(GTK_GRID(grid), entry, 0, i++, 10, 1); */
    GtkWidget *entry_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_widget_set_halign(entry_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(entry_box, GTK_ALIGN_CENTER);
    GtkWidget *entry = gtk_label_new(*file_path);

    gtk_box_append(GTK_BOX(entry_box), entry);

    /* g_signal_connect(entry, "clicked", G_CALLBACK(print_hello), NULL); */

    GtkGesture *gesture = gtk_gesture_click_new();
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(gesture),
                                  GDK_BUTTON_PRIMARY);
    g_signal_connect(gesture, "pressed", G_CALLBACK(print_hello), NULL);
    gtk_widget_add_controller(entry_box, GTK_EVENT_CONTROLLER(gesture));

    gtk_grid_attach(GTK_GRID(grid), entry_box, 1, i++, 20, 5);

    i += 10;
    puts(*file_path);
    file_path++;
  }

  /* button = gtk_button_new_with_label("Hello World"); */
  /* g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL); */
  /* gtk_box_append(GTK_BOX(box), button); */

  gtk_window_present(GTK_WINDOW(window));

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
