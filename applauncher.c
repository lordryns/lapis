#include "gtk/gtkcssprovider.h"
#include <gtk/gtk.h>
#include <gtk-layer-shell/gtk-layer-shell.h>
#include <stdio.h>


static GtkWidget *window = NULL; 

void show_app_launcher () {
    if (window != NULL) 
    {
        gtk_window_destroy(GTK_WINDOW (window));
        window = NULL;
        return;
    } 

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider, "#launcher {"
                                      "  border-radius: 15px;"
                                      "  padding: 20px;"
                                      "  box-shadow: 0 12px 25px rgba(0, 0, 0, 0.25);"
                                      "  border: 1px solid rgba(0,0,0,0.1);"                                  
                                      "}");

    GdkDisplay *display = gdk_display_get_default(); 
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    window = gtk_window_new();
    gtk_window_set_default_size(GTK_WINDOW (window), 700, 500);
    gtk_layer_init_for_window(GTK_WINDOW (window));
    gtk_layer_set_layer(GTK_WINDOW (window), GTK_LAYER_SHELL_LAYER_TOP);
    gtk_layer_set_anchor(GTK_WINDOW (window), GTK_LAYER_SHELL_EDGE_BOTTOM, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW (window), GTK_LAYER_SHELL_EDGE_LEFT, TRUE);
    gtk_layer_set_margin(GTK_WINDOW (window), GTK_LAYER_SHELL_EDGE_BOTTOM, 10);
    gtk_layer_set_margin(GTK_WINDOW (window), GTK_LAYER_SHELL_EDGE_LEFT, 10);
    gtk_widget_set_name(window, "launcher");

    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget *app_scrollable = gtk_scrolled_window_new(); 
    gtk_box_append(GTK_BOX (container), app_scrollable);

    GtkWidget *app_list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW (app_scrollable), app_list);
    GList *apps = g_app_info_get_all(); 
    for (GList *l = apps; l != NULL; l = l->next) {
        GAppInfo *app = l->data; 
        GtkWidget *app_btn = gtk_button_new_with_label(g_app_info_get_name(app));
        gtk_widget_set_hexpand(app_btn, TRUE);
        gtk_box_append(GTK_BOX (app_list), app_btn);
        // g_print("app = %s\npath = %s\n", g_app_info_get_name(app), g_app_info_get_executable(app));
    }
    g_list_free_full(apps, g_object_unref);

    GtkWidget *info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX (container), info_box); 

    GtkWidget *info_label = gtk_label_new("Good software starts with less");
    gtk_box_append(GTK_BOX (info_box), info_label);

    gtk_window_set_child(GTK_WINDOW (window), container);
    gtk_window_present(GTK_WINDOW (window));
}


