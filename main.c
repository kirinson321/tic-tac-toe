/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/

#include <stdio.h>
#include <gtk/gtk.h>


int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *title;

    gtk_window_set_title(GTK_WINDOW(window), "Kółko i krzyżyk");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 60);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}