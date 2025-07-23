#include "frontend/_internal/file_select_menu.h"
#include "frontend/_internal/frontend.h"
cme_error_t FileSelectMenu_create(struct Frontend *frontend,
                                  struct FileSelectMenu *out) {

  GtkWidget *title_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(title_box, GTK_ALIGN_START);
  gtk_widget_set_valign(title_box, GTK_ALIGN_START);
  gtk_widget_set_margin_top(title_box, 20);
  gtk_widget_set_margin_start(title_box, 20);

  gtk_window_set_child(GTK_WINDOW(frontend->main_window), title_box);

  const char *str = "Current directory:";
  GtkWidget *title = gtk_label_new(str);
  gtk_widget_set_halign(title, GTK_ALIGN_START);
  gtk_widget_set_valign(title, GTK_ALIGN_START);

  gtk_box_append(GTK_BOX(title_box), title);

  out->files_grid = gtk_grid_new();
  gtk_widget_set_hexpand(out->files_grid, TRUE);
  gtk_widget_set_vexpand(out->files_grid, TRUE);
  gtk_widget_set_halign(out->files_grid, GTK_ALIGN_FILL);
  gtk_widget_set_valign(out->files_grid, GTK_ALIGN_FILL);
  gtk_widget_set_margin_top(out->files_grid, 10);
  gtk_widget_set_margin_start(out->files_grid, 20);

  gtk_box_append(GTK_BOX(title_box), out->files_grid);

  GtkWidget *entry_grid = gtk_grid_new();
  gtk_grid_attach(GTK_GRID(out->files_grid), entry_grid, 0, 0, 20, 20);

  GtkWidget *entry_label = gtk_label_new("Some file path");
  gtk_grid_attach(GTK_GRID(entry_grid), entry_label, 0, 0,
                  sizeof("Some file path"), 1);

  GtkWidget *entry_button = gtk_button_new_with_label("Open");
  gtk_widget_set_margin_start(entry_button, 10);
  gtk_grid_attach(GTK_GRID(entry_grid), entry_button, sizeof("Some file path"),
                  0, sizeof("Open"), 1);

  return 0;
}
