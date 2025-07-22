#include <X11/Xlib.h>
#include <fontconfig/fontconfig.h>
#include <gdk/x11/gdkx.h>
#include <gtk/gtk.h>

GtkWidget *window = NULL;

static void activate(GtkApplication *app, gpointer user_data) {

  if (!window) {
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "File Viewer");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_window_present(GTK_WINDOW(window));
  }
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

#ifdef GDK_WINDOWING_X11
  GdkDisplay *gd = gdk_display_get_default();
  if (GDK_IS_X11_DISPLAY(gd)) {
    Display *xd = gdk_x11_display_get_xdisplay(gd);
    XCloseDisplay(xd);
  }
#endif

  /* then always do this */
  FcFini();

  return status;
}
