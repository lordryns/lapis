#include <gtk/gtk.h>
#include <gtk-layer-shell/gtk-layer-shell.h>
#include <stdio.h>
#include "applauncher.h"

void app_button_clicked (GtkButton *button, gpointer user_data) {
    const char *executable = (const char *)user_data; 
    g_print("running: %s\n", executable);
    g_spawn_command_line_async(executable, NULL);
    show_app_launcher();
}



static void
on_row_activated(GtkListBox *box, GtkListBoxRow *row, gpointer user_data)
{
    GtkWidget *button = gtk_list_box_row_get_child(row);
    gtk_widget_activate(button);
}

static GtkWidget *window = NULL; 
GList *apps;
void show_app_launcher () {
    if (window != NULL) 
    {
        gtk_window_destroy(GTK_WINDOW (window));
        window = NULL;
        g_list_free_full(apps, g_object_unref);
        return;
    } 

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider, "#launcher {"
                            "  border-radius: 15px;"
                            "  padding: 20px;"
                            "  box-shadow: 0 12px 25px rgba(0, 0, 0, 0.25);"
                            "  border: 1px solid rgba(0,0,0,0.1);"                                  
                            "}"
 
"#app-list { "
"background: transparent; "
"border-radius: 14px; "
"padding: 6px; "
"} "
"#app-list button { "
"all: unset; "
"padding: 10px 12px; "
"border-radius: 10px; "
"background: rgba(255,255,255,0.06); "
"transition: background 120ms ease, transform 120ms ease; "
"min-height: 38px; "
"color: inherit; "
"} "
"#app-list button:hover { "
"background: rgba(255,255,255,0.12); "
"} "
"#app-list button:active { "
"background: rgba(255,255,255,0.18); "
"transform: scale(0.99); "
"} "
"#app-list button:focus-visible { "
"outline: 2px solid rgba(120,160,255,0.8); "
"outline-offset: 2px; "
"} "
"#app-list row:selected button { "
"background: rgba(120,160,255,0.22); "
"} "
"#app-list image { "
"margin-right: 8px; "
"} "
"#app-list label { "
"font-size: 14px; "
"} "

);


    GdkDisplay *display = gdk_display_get_default(); 
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    window = gtk_window_new();
    gtk_window_set_default_size(GTK_WINDOW (window), 700, 500);
    gtk_layer_init_for_window(GTK_WINDOW (window));
    
    gtk_layer_set_keyboard_mode(GTK_WINDOW (window), GTK_LAYER_SHELL_KEYBOARD_MODE_ON_DEMAND);
    
    gtk_layer_set_layer(GTK_WINDOW (window), GTK_LAYER_SHELL_LAYER_TOP);
    gtk_layer_set_anchor(GTK_WINDOW (window), GTK_LAYER_SHELL_EDGE_BOTTOM, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW (window), GTK_LAYER_SHELL_EDGE_LEFT, TRUE);
    gtk_layer_set_margin(GTK_WINDOW (window), GTK_LAYER_SHELL_EDGE_BOTTOM, 10);
    gtk_layer_set_margin(GTK_WINDOW (window), GTK_LAYER_SHELL_EDGE_LEFT, 10);
    gtk_widget_set_name(window, "launcher");

    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    GtkWidget *app_scrollable = gtk_scrolled_window_new(); 
    gtk_box_append(GTK_BOX (container), app_scrollable);

    GtkWidget *app_list = gtk_list_box_new();
    gtk_widget_set_name(app_list, "app-list");
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW (app_scrollable), app_list);
    gtk_widget_set_hexpand(app_list, TRUE);
    g_signal_connect(app_list, "row-activated",
                 G_CALLBACK(on_row_activated), NULL);
    
    apps = g_app_info_get_all(); 
    for (GList *l = apps; l != NULL; l = l->next) {
        GtkWidget *app_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
        GAppInfo *app = l->data; 
        GtkWidget *app_btn = gtk_button_new();
        GtkWidget *icon = gtk_image_new_from_gicon(g_app_info_get_icon(app));

        gtk_box_append(GTK_BOX (app_box), icon); 

        GtkWidget *label = gtk_label_new(g_app_info_get_name(app)); 
        gtk_box_append(GTK_BOX (app_box), label); 
        
        gtk_button_set_child(GTK_BUTTON (app_btn), app_box);
        gtk_widget_set_hexpand(app_btn, TRUE);
        gtk_list_box_append(GTK_LIST_BOX (app_list), app_btn);
        const char *exec_name = g_app_info_get_executable(app);
        g_signal_connect(app_btn, "clicked", G_CALLBACK (app_button_clicked), (gpointer) exec_name);
        // g_print("app = %s\npath = %s\n", g_app_info_get_name(app), g_app_info_get_executable(app));
    }

    GtkWidget *info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX (container), info_box); 

    GtkWidget *info_label = gtk_label_new("Good software starts with less");
    gtk_box_append(GTK_BOX (info_box), info_label);

    gtk_window_set_child(GTK_WINDOW (window), container);
    gtk_window_present(GTK_WINDOW (window));
}


