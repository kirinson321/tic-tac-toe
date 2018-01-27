/*
 * Marcin Trajfacki, 301199
 * Projekt kółko i krzyżyk
*/

#include <gtk/gtk.h>
#include "tic_tac_toe.h"

GtkWidget *grid;
int size=4;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Kółko i krzyżyk");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 60);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    create_grid();

    // testing new functionalities here

    //debugger will be used to display debug messages;
    //should write a new function to change its message when a button is pressed

    //

    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}