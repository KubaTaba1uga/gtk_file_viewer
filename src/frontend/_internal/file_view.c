#include "frontend/_internal/file_view.h"
#include "frontend/_internal/frontend.h"

cme_error_t FileView_create(struct Frontend *frontend, const char *file_path) {
  cme_error_t err;

  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign(main_box, GTK_ALIGN_START);
  gtk_widget_set_valign(main_box, GTK_ALIGN_START);
  gtk_widget_set_margin_top(main_box, 20);
  gtk_widget_set_margin_start(main_box, 20);

  gtk_window_set_child(GTK_WINDOW(frontend->main_window), main_box);

  GtkWidget *scrolled;

  (void)err;

  return 0;
}
