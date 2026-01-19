#include <gtk/gtk.h>
#include "dock.h"
#include "applauncher.h"
#include "background.h"
#include <stdio.h>


static void on_activate (GtkApplication *app) {
    // show_app_launcher(app); 
    show_dock_window();
    show_background_manager(app); 
}

int main (int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.lordryns.lapis",G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    return g_application_run(G_APPLICATION (app), argc, argv);

    return 0;
}
