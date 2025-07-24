#ifndef GTK_FILE_VIEWER_FRONTEND_INT_FILE_VIEW_H
#define GTK_FILE_VIEWER_FRONTEND_INT_FILE_VIEW_H
#include <c_minilib_error.h>
#include <gtk/gtk.h>
#include <stdint.h>

/******************************************************************************
 *                                File View                                   *
 ******************************************************************************/
struct FileView {
  GtkWidget *main_box;
};

struct Frontend;
cme_error_t FileView_create(struct Frontend *frontend, struct FileView *out);
/* void FileView_destroy(struct FileView *out); */

#endif // GTK_FILE_VIEWER_FRONTEND_INT_FILE_VIEW_H
