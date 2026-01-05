#include <stdio.h>
#include <gtk/gtk.h>
#include "settings.h"

void show_settings_app () {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider, "#wallpaper_mini {"
    "min-width: 200px;"
    "min-height: 90px;"
    "border-radius: 10px;"
     "}");


    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    GtkWidget *window = gtk_window_new(); 
    gtk_window_set_title(GTK_WINDOW (window), "Settings");  
    gtk_window_set_default_size(GTK_WINDOW (window), 700, 600);


    GtkWidget *parent_container = gtk_notebook_new();

    GtkWidget *wallpaper_label = gtk_label_new("Wallpaper");
    GtkWidget *wallpaper_tab = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget *change_wallpaper_label = gtk_label_new("Set Wallpaper"); 
    gtk_box_append(GTK_BOX (wallpaper_tab), change_wallpaper_label);

    GtkWidget *change_wallpaper_tab = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 7);
    gtk_box_append(GTK_BOX (wallpaper_tab), change_wallpaper_tab);

    for (int i=1; i < 3; i++) {
        char wallpaper_name[30];
        sprintf(wallpaper_name, "./wallpapers/%d.jpg", i);
   
        GtkWidget *wallpaper_mini = gtk_picture_new_for_filename(wallpaper_name);
        gtk_widget_set_name(wallpaper_mini, "wallpaper_mini");
        gtk_picture_set_content_fit(GTK_PICTURE(wallpaper_mini), GTK_CONTENT_FIT_COVER);
        gtk_box_append(GTK_BOX(change_wallpaper_tab), wallpaper_mini);
    }

    gtk_notebook_append_page(GTK_NOTEBOOK (parent_container), wallpaper_tab, wallpaper_label);

    gtk_window_set_child(GTK_WINDOW (window), parent_container);
    gtk_window_present(GTK_WINDOW (window));
}

