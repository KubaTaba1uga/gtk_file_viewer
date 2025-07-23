#include "c_minilib_error.h"
#include "frontend/frontend.h"
#include <asm-generic/errno.h>
#include <fontconfig/fontconfig.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  cme_error_t err;

  puts("Starting app...");

  int err_code = cme_init();
  if (err_code) {
    err = cme_error(EINPROGRESS, "Unable to init error lib");
    goto error_out;
  };

  frontend_t gui;
  err =
      frontend_create("taba1uga.GtkFileViewer", "File Viewer", 1200, 800, &gui);
  if (err) {
    goto error_out;
  }

  puts("Running app...");

  err = frontend_start(gui, argc, argv);
  if (err) {
    goto error_frontend_cleanup;
  }

  puts("Shutting down app...");

  frontend_destroy(&gui);

  return 0;

error_frontend_cleanup:
  frontend_destroy(&gui);
error_out : {
  char err_buf[2048];
  cme_error_dump_to_str(err, sizeof(err_buf), err_buf);
  puts(err_buf);
  return err->code;
}
}
