#include <gtk/gtk.h>
#include <gtk-layer-shell/gtk-layer-shell.h>
#include <stdio.h>


void show_background_manager (GtkApplication *app) {
    GtkCssProvider *provider = gtk_css_provider_new();

    GdkDisplay *display = gdk_display_get_default(); 
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    GListModel *monitors = gdk_display_get_monitors(display); 

    GdkMonitor *monitor = GDK_MONITOR (g_list_model_get_item(monitors, 0));
    GdkRectangle geometry; 
    gdk_monitor_get_geometry(monitor, &geometry);


    GtkWidget *window = gtk_application_window_new(app); 
    // gtk_window_set_default_size(GTK_WINDOW (window), 100, 100);
    gtk_layer_init_for_window(GTK_WINDOW (window));
    gtk_layer_set_layer(GTK_WINDOW (window), GTK_LAYER_SHELL_LAYER_BACKGROUND);
    
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, TRUE);

    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(container, TRUE);
    gtk_widget_set_vexpand(container, TRUE);

    GtkWidget *label = gtk_label_new("Hello World!");
    gtk_widget_set_halign(label, TRUE);
    gtk_widget_set_valign(label, TRUE);
    gtk_box_append(GTK_BOX (container), label);

    gtk_window_set_child(GTK_WINDOW (window), container);
    gtk_window_present(GTK_WINDOW (window));
}


