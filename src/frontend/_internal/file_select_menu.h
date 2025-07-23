#ifndef GTK_FILE_VIEWER_FRONTEND_INT_FILE_SELECT_MENU_H
#define GTK_FILE_VIEWER_FRONTEND_INT_FILE_SELECT_MENU_H
#include <c_minilib_error.h>
#include <gtk/gtk.h>
#include <stdint.h>

/******************************************************************************
 *                           File Select Menu                                 *
 ******************************************************************************/
struct FileSelectMenu {
  GtkWidget *files_grid;
};

struct Frontend;
cme_error_t FileSelectMenu_create(struct Frontend *frontend,
                                  struct FileSelectMenu *out);
void FileSelectMenu_destroy(struct FileSelectMenu *out);

#endif // GTK_FILE_VIEWER_FRONTEND_INT_FILE_SELECT_MENU_H
