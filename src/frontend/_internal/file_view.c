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

  GtkWidget *scrolled = gtk_scrolled_window_new();
  gtk_widget_set_hexpand(scrolled, TRUE);
  gtk_widget_set_vexpand(scrolled, TRUE);
  gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrolled), 600);
  gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled),
                                             800);
  gtk_box_append(GTK_BOX(main_box), scrolled);

  GtkWidget *view = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
  gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(view), TRUE);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), view);

  char *contents;
  gsize length;
  GFile *file = g_file_new_for_path(file_path);
  if (g_file_load_contents(file, NULL, &contents, &length, NULL, NULL)) {
    GtkTextBuffer *buffer;

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_text_buffer_set_text(buffer, contents, length);
    g_free(contents);
  }

  (void)err;

  return 0;
}
