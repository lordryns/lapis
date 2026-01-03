#include <gtk/gtk.h>
#include "settings.h"

void show_settings_app () {
    GtkWidget *window = gtk_window_new(); 
    gtk_window_set_title(GTK_WINDOW (window), "Settings");  
    gtk_window_set_default_size(GTK_WINDOW (window), 700, 600);

    gtk_window_present(GTK_WINDOW (window));
}

