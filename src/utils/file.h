#ifndef GTK_FILE_VIEWER_UTILS_FILE_H
#define GTK_FILE_VIEWER_UTILS_FILE_H

#include "c_minilib_error.h"
#include <fcntl.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>

static inline cme_error_t list_dir(const char *path, uint32_t n,
                                   const char *files[]) {
  GError *err;
  GDir *dir = g_dir_open(path, 0, &err);

  for (int8_t i = 0; i < n; i++) {
    files[i] = g_dir_read_name(dir);
    if (!files[i]) {
      break;
    }
  }

  return 0;
}

#endif // GTK_FILE_VIEWER_UTILS_FILE_H
