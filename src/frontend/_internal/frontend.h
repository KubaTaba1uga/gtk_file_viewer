#ifndef GTK_FILE_VIEWER_FRONTEND_INT
#define GTK_FILE_VIEWER_FRONTEND_INT
#include <c_minilib_error.h>
#include <gtk/gtk.h>
#include <stdint.h>

#include "frontend/_internal/file_select_menu.h"
#include "frontend/_internal/file_view.h"

/******************************************************************************
 *                                Frontend                                    *
 ******************************************************************************/
struct Frontend {
  GtkApplication *app;
  GtkWidget *main_window;
  const char *window_name;
  int32_t window_x;
  int32_t window_y;

  struct FileSelectMenu file_select_menu;
  struct FileView file_view;
};

#endif // GTK_FILE_VIEWER_FRONTEND_INT
