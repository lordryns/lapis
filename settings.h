#ifndef LAPIS_SETTINGS_H
#define LAPIS_SETTINGS_H

#include <gtk/gtk.h>

struct shell_settings {
    GtkWidget *background_widget; 
};

extern struct shell_settings shell_settings;

void show_settings_app ();

#endif // !LAPIS_SETTINGS_H


