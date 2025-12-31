#include <gtk/gtk.h>
#include <gtk-layer-shell/gtk-layer-shell.h>
#include <stdio.h>
#include "event.h"
#include "applauncher.h"
#include "glib.h"
#include "gtk/gtkcssprovider.h"

static gboolean update_battery(GtkLabel *label) {
    int percent = read_battery();
    
    char buf[32];
    sprintf(buf, "%d%%", percent);
    gtk_label_set_text(label, buf);

    return TRUE;
}

static gboolean update_time(GtkLabel *label) {
   char res[20]; 

    read_time(res);
    gtk_label_set_text(label, res);
}

void show_dock_window (GtkApplication *app) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider, "#time {padding-top: 18px;  }");

    GdkDisplay *display = gdk_display_get_default(); 
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    GListModel *monitors = gdk_display_get_monitors(display); 

    GdkMonitor *monitor = GDK_MONITOR (g_list_model_get_item(monitors, 0));
    GdkRectangle geometry; 
    gdk_monitor_get_geometry(monitor, &geometry);

    int window_width = geometry.width;
    int window_height = 40;
    GtkWidget *window = gtk_application_window_new(app); 
    gtk_window_set_default_size(GTK_WINDOW (window), window_width, window_height);
    gtk_layer_init_for_window(GTK_WINDOW (window));
    gtk_layer_set_anchor(GTK_WINDOW (window), GTK_LAYER_SHELL_EDGE_BOTTOM, TRUE);
    gtk_layer_auto_exclusive_zone_enable(GTK_WINDOW (window));


    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_hexpand(container, TRUE);


    GtkWidget *app_launcher_btn = gtk_button_new_from_icon_name("open-menu-symbolic");
    g_signal_connect(app_launcher_btn, "clicked", G_CALLBACK (show_app_launcher), NULL);
    gtk_box_append(GTK_BOX (container), app_launcher_btn);

    GtkWidget *right_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_hexpand(right_container, TRUE);
    gtk_widget_set_halign(right_container, GTK_ALIGN_END);
    gtk_box_append(GTK_BOX (container), right_container);


    char c_time[20]; 
    read_time(c_time);
    GtkWidget *time_label = gtk_label_new(c_time);
    gtk_widget_set_name(time_label, "time");

    gtk_box_append(GTK_BOX (right_container), time_label);
    g_timeout_add_seconds(10, (GSourceFunc)update_time, time_label);
    

    GtkWidget *battery_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX (right_container), battery_box);

    char percent[10]; 
    sprintf(percent, "%d%%", read_battery());
    GtkWidget *battery_label = gtk_label_new(percent);
    gtk_box_append(GTK_BOX (battery_box), battery_label);
    g_timeout_add_seconds(10, (GSourceFunc)update_battery, battery_label);

    GtkWidget *battery_icon = gtk_image_new_from_icon_name("battery-full-symbolic");
    gtk_box_append(GTK_BOX (battery_box), battery_icon);


    GtkWidget *notification_btn = gtk_button_new_from_icon_name("computer-symbolic");
        gtk_box_append(GTK_BOX (right_container), notification_btn);



    gtk_window_set_child(GTK_WINDOW (window), container);
    gtk_window_present(GTK_WINDOW (window));
}

