#include <gtk/gtk.h>
#include <gtk-layer-shell/gtk-layer-shell.h>
#include <stdio.h>


void show_app_launcher (GtkApplication *app) {
    GtkWidget *window = gtk_application_window_new(app); 
    gtk_layer_init_for_window(GTK_WINDOW (window));
    gtk_window_present(GTK_WINDOW (window));
}


