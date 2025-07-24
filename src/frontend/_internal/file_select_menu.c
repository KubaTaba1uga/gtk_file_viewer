#include <gtk/gtk.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "c_minilib_error.h"
#include "frontend/_internal/file_select_menu.h"
#include "frontend/_internal/frontend.h"
#include "utils/file.h"

static void move_to_file_view(GtkWidget *widget, gpointer data) {
  puts("HIT");

  struct Frontend *frontend = data;

  FileView_create(frontend, &frontend->file_view);
  /* FileSelectMenu_destroy(local_menu); */
}

cme_error_t FileSelectMenu_create(struct Frontend *frontend,
                                  struct FileSelectMenu *out) {
  cme_error_t err;

  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(main_box, GTK_ALIGN_START);
  gtk_widget_set_valign(main_box, GTK_ALIGN_START);
  gtk_widget_set_margin_top(main_box, 20);
  gtk_widget_set_margin_start(main_box, 20);

  gtk_window_set_child(GTK_WINDOW(frontend->main_window), main_box);

  const char *str = "Current directory:";
  GtkWidget *title = gtk_label_new(str);
  gtk_widget_set_halign(title, GTK_ALIGN_START);
  gtk_widget_set_valign(title, GTK_ALIGN_START);

  gtk_box_append(GTK_BOX(main_box), title);

  GtkWidget *files_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_margin_top(files_box, 10);
  gtk_widget_set_margin_start(files_box, 20);

  gtk_box_append(GTK_BOX(main_box), files_box);

  const char *files[255];
  err = list_dir(".", 254, files);
  if (err) {
    goto error_out;
  }

  const char **file_path = files;
  uint32_t max = 0;
  for (; *file_path != NULL; file_path++) {
    size_t len = strlen(*file_path);
    if (len > max) {
      max = len;
    }
  }

  file_path = files;
  for (int i = 0; *file_path != NULL; i++, file_path++) {
    puts(*file_path);
    GtkWidget *file_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_widget_set_hexpand(file_box, TRUE);
    gtk_widget_set_halign(file_box, GTK_ALIGN_FILL);
    gtk_widget_set_margin_top(file_box, 10);
    gtk_box_append(GTK_BOX(files_box), file_box);

    GtkWidget *entry_label = gtk_label_new(*file_path);
    gtk_widget_set_hexpand(entry_label, TRUE);
    gtk_widget_set_halign(entry_label, GTK_ALIGN_FILL);
    gtk_box_append(GTK_BOX(file_box), entry_label);

    GtkWidget *entry_button = gtk_button_new_with_label("Open");
    gtk_widget_set_hexpand(entry_button, FALSE);
    gtk_widget_set_halign(entry_button, GTK_ALIGN_FILL);
    gtk_widget_set_margin_start(entry_button, 20);
    g_signal_connect(entry_button, "clicked", G_CALLBACK(move_to_file_view),
                     frontend);
    gtk_box_append(GTK_BOX(file_box), entry_button);

    (void)i;
  };

  out->main_box = main_box;

  return 0;

error_out:
  return cme_return(err);
}

void FileSelectMenu_destroy(struct FileSelectMenu *out) {
  if (out->main_box) {
    gtk_widget_unparent(GTK_WIDGET(out->main_box));
    out->main_box = NULL;
  }
}
