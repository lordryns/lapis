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
    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, 0);
    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_BOTTOM, 0);
    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, 0);
    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_RIGHT, 0);    

    gtk_layer_set_exclusive_zone(GTK_WINDOW(window), 0);

    gtk_layer_set_keyboard_mode(GTK_WINDOW(window),
        GTK_LAYER_SHELL_KEYBOARD_MODE_NONE);
    gtk_widget_set_focusable(window, FALSE);

    GtkWidget *main_overlay = gtk_overlay_new();

    gtk_widget_set_hexpand(main_overlay, TRUE);
    gtk_widget_set_vexpand(main_overlay, TRUE);
    gtk_widget_set_halign(main_overlay, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_overlay, GTK_ALIGN_FILL);
            
    GtkWidget *background_picture = gtk_picture_new_for_filename("./wallpapers/surfboard-sunset.jpg");
    gtk_picture_set_content_fit(GTK_PICTURE(background_picture),
                            GTK_CONTENT_FIT_COVER);

    gtk_widget_set_hexpand(background_picture, TRUE);
    gtk_widget_set_vexpand(background_picture, TRUE);
    gtk_widget_set_halign(background_picture, GTK_ALIGN_FILL);
    gtk_widget_set_valign(background_picture, GTK_ALIGN_FILL);

    gtk_overlay_add_overlay(GTK_OVERLAY (main_overlay), background_picture);

    gtk_window_set_child(GTK_WINDOW (window), main_overlay);
    gtk_window_present(GTK_WINDOW (window));
}


